/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:03:53 by victor            #+#    #+#             */
/*   Updated: 2025/02/06 13:00:50 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* Executes the 'echo' command by calling `exe_echo` with the provided args.  */
/* - Skips the first argument (cmd[0], which is "echo").                      */
/* - Sets the exit status returned by `exe_echo`.                             */
/* ************************************************************************** */
void	ft_execute_echo(char **cmd, int *exit_status)
{
	*exit_status = exe_echo(cmd + 1);
}

/* ************************************************************************** */
/* Executes the 'export' command:                                             */
/* - If no arguments, prints all exported variables.                          */
/* - Otherwise, assigns new variables using `assign_export_vars`.             */
/* - Prints an error if the syntax is invalid.                                */
/* ************************************************************************** */
void	ft_execute_export(char **cmd, char **env)
{
	int	result;

	if (!cmd[1])
	{
		print_exported_vars(env);
		return ;
	}
	result = assign_export_vars(cmd, env);
	if (result)
	{
		ft_putstr_fd("Error: invalid syntax for export\n", 2);
	}
}

/* ************************************************************************** */
/* ft_execute_env: Prints all environment variables.                          */
/* ************************************************************************** */
void	ft_execute_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return ;
}

/* ************************************************************************** */
/* Executes the 'pwd' command: prints the current working directory.          */
/* - Uses `getcwd` to retrieve the current directory.                         */
/* - Prints the directory to stdout or an error message if it fails.          */
/* - Sets the exit status to 0 on success, or 1 on failure.                   */
/* ************************************************************************** */
void	ft_execute_pwd(int *exit_status)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		*exit_status = 0;
	}
	else
	{
		perror("pwd");
		*exit_status = 1;
	}
}

/* ************************************************************************** */
/* ft_execute_unset: Removes specified environment variables.                 */
/* If no arguments are provided, prints an error and returns 1.               */
/* Otherwise, for each argument, searches for a matching key in env, frees    */
/* its memory, and removes the variable.                                      */
/* ************************************************************************** */
int	ft_execute_unset(char **av, char **env)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	if (!av[1])
		return (ft_printf("unset: not enough arguments\n"), 1);
	while (av[++i])
	{
		j = 0;
		while (env[j])
		{
			key = ft_substr(env[j], 0, ft_strchr(env[j], '=') - env[j]);
			if (ft_strcmp(av[i], key) == 0)
			{
				free(key);
				free(env[j]);
				remove_env_variable(j, env);
				break ;
			}
			free(key);
			j++;
		}
	}
	return (0);
}
