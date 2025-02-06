/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:07:13 by victor            #+#    #+#             */
/*   Updated: 2025/02/06 13:38:13 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* Validates and extracts the key and value from a string.                    */
/* If the string contains '=', splits it into key and value.                  */
/* Removes quotes from the value if present. Returns 1 failure, 0 success.    */
/* ************************************************************************** */
int	validate_and_extract(char *arg, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (1);
	*key = ft_substr(arg, 0, equal_sign - arg);
	*value = ft_strdup(equal_sign + 1);
	if (!(*key) || !(*value))
	{
		free(*key);
		free(*value);
		return (1);
	}
	remove_q(value);
	return (0);
}

/* ************************************************************************** */
/* update_existing_var: Updates the value of an existing environment variable */
/* If the key is found, it replaces its value with the new one.               */
/* Returns 1 if the variable was updated, 0 if not found.                     */
/* ************************************************************************** */
int	update_existing_var(char **env, char *key, char *value)
{
	int		i;
	size_t	key_len;
	char	*new_value;
	char	*temp;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
		{
			new_value = ft_strjoin(key, "=");
			temp = ft_strjoin(new_value, value);
			free(new_value);
			free(env[i]);
			env[i] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/* add_new_var: Adds a new environment variable to the env array.             */
/* If the key doesn't exist, it creates a new entry with the key and value.   */
/* ************************************************************************** */
void	add_new_var(char **env, char *key, char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	while (env[i])
		i++;
	env[i] = ft_strjoin(key, "=");
	new_value = ft_strjoin(env[i], value);
	free(env[i]);
	env[i] = new_value;
	env[i + 1] = NULL;
}

/* ************************************************************************** */
/* assign_single_var: Assigns a value to a single environment variable.       */
/* If the key already exists, it updates the value. If not, it adds a new one.*/
/* Validates the key and extracts the key-value pair. Frees allocated memory. */
/* ************************************************************************** */
int	assign_single_var(char *arg, char **env)
{
	char	*key;
	char	*value;

	if (!check_key(arg))
		return (1);
	if (!ft_strchr(arg, '='))
		return (0);
	if (validate_and_extract(arg, &key, &value))
		return (1);
	if (!update_existing_var(env, key, value))
	{
		add_new_var(env, key, value);
	}
	setenv(key, value, 1);
	free(key);
	free(value);
	return (0);
}

/* ************************************************************************** */
/* Assigns variables from the export command to the env array.                */
/* Iterates through the arguments and uses assign_single_var handle each one  */
/* Returns 1 if any assignment fails, otherwise returns 0.                    */
/* ************************************************************************** */
int	assign_export_vars(char **av, char **env)
{
	int	i;
	int	result;

	i = 1;
	while (av[i])
	{
		result = assign_single_var(av[i], env);
		if (result)
			return (1);
		i++;
	}
	return (0);
}
