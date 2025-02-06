/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:46:45 by victor            #+#    #+#             */
/*   Updated: 2025/02/06 13:31:10 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* get_env_arr: Duplicates the environment variable array.                    */
/* Allocates and copies env into a new array, returning a dynamically         */
/* allocated copy. If fails, frees allocated memory and returns NULL.         */
/* ************************************************************************** */
char	**get_env_arr(char **env)
{
	int		i;
	int		j;
	int		length;
	char	**raw_env;

	i = 0;
	length = 0;
	while (env[length])
		length++;
	raw_env = malloc(sizeof(char *) * (length + 1));
	if (!raw_env)
		return (NULL);
	while (env[i])
	{
		raw_env[i] = ft_strdup(env[i]);
		if (!raw_env[i])
		{
			j = -1;
			while (++j < i)
				free(raw_env[j]);
			return (free(raw_env), NULL);
		}
		i++;
	}
	return (raw_env[i] = NULL, raw_env);
}

/* ************************************************************************** */
/* print_exported_vars: Prints environment variables in 'declare -x' format.  */
/* ************************************************************************** */
int	print_exported_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/* check_key: Validates if arg is a valid environment variable name.          */
/* - Must start with a letter or '_'.                                         */
/* - Can only contain letters, digits, or '_'.                                */
/* - '=' is allowed but must appear at the end or separate key from value.    */
/* - Prints an error message if invalid.                                      */
/* ************************************************************************** */
bool	check_key(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("Not valid identifier\n", 2);
		return (false);
	}
	while (arg[i++])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '\0')
		{
			if (arg[i] != '=')
			{
				ft_putstr_fd("Not valid identifier\n", 2);
				return (false);
			}
			else
				break ;
		}
	}
	return (true);
}

/* ************************************************************************** */
/* remove_env_variable: Removes an environment variable from the env array.   */
/* Shifts all elements after the given index one position to the left.        */
/* ************************************************************************** */
void	remove_env_variable(int index, char **env)
{
	while (env[index])
	{
		env[index] = env[index + 1];
		index++;
	}
}
