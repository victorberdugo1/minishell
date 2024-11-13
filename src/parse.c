/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:18:35 by victor            #+#    #+#             */
/*   Updated: 2024/11/13 22:52:37 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*exp_env_vars(char *input, int exit_status)
{
	char	*expanded;
	char	*ptr;
	char	*env_var;
	int		i;

	expanded = malloc(strlen(input) + 1);
	ptr = input;
	i = 0;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			if (*ptr == '?')
			{
				sprintf(expanded + i, "%d", exit_status);
				i = strlen(expanded);
				ptr++;
			}
			else
			{
				env_var = getenv(ptr);
				if (env_var)
				{
					sprintf(expanded + i, "%s", env_var);
					i = strlen(expanded);
					while (*ptr && *ptr != ' ' && *ptr != '$')
						ptr++;
				}
				else
					ptr++;
			}
		}
		else
			expanded[i++] = *ptr++;
	}
	expanded[i] = '\0';
	return (expanded);
}

int	ft_is_builtin(char *cmd)
{
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 ||
			strcmp(cmd, "pwd1") == 0 || strcmp(cmd, "export") == 0 ||
			strcmp(cmd, "unset") == 0 || strcmp(cmd, "env") == 0 ||
			strcmp(cmd, "exit") == 0) {
		return 1;
	}
	return 0;
}

void ft_command(char *cmd, int *exit_status)
{
	pid_t	pid;
	char	*args[64];
	char	*token;
	int		i = 0;

	token = strtok(cmd, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, exit_status, 0);
		*exit_status = WEXITSTATUS(*exit_status);
	}
}

void	ft_execute(char *cmd, int *exit_status)
{
	if (strcmp(cmd, "cd") == 0)
	{
		char *path = strtok(NULL, " ");
		if (path == NULL || chdir(path) == -1)
		{
			perror("cd");
			*exit_status = 1;
		}
		else
		{
			*exit_status = 0;
		}
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		exit(*exit_status);
	}
	else if (strcmp(cmd, "echo") == 0)
	{
		char *arg = strtok(NULL, " ");
		while (arg != NULL)
		{
			write(STDOUT_FILENO, arg, strlen(arg));
			write(STDOUT_FILENO, " ", 1);
			arg = strtok(NULL, " ");
		}
		write(STDOUT_FILENO, "\n", 1);
		*exit_status = 0;
	}
	else if (strcmp(cmd, "pwd") == 0 || strcmp(cmd, "pwd1") == 0)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			write(STDOUT_FILENO, cwd, strlen(cwd));
			write(STDOUT_FILENO, "\n", 1);
			*exit_status = 0;
		} else {
			perror("pwd");
			*exit_status = 1;
		}
	} else if (strcmp(cmd, "export") == 0)
	{
		char *var = strtok(NULL, " ");
		if (var)
		{
			char *value = strtok(NULL, " ");
			if (value) {
				setenv(var, value, 1);
				*exit_status = 0;
			}
			else
			{
				fprintf(stderr, "export: invalid argument\n");
				*exit_status = 1;
			}
		}
	}
	else if (strcmp(cmd, "unset") == 0)
	{
		char *var = strtok(NULL, " ");
		if (var)
		{
			unsetenv(var);
			*exit_status = 0;
		}
		else
		{
			fprintf(stderr, "unset: invalid argument\n");
			*exit_status = 1;
		}
	}
	else if (strcmp(cmd, "env") == 0)
	{
		extern char **environ;
		for (int i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		*exit_status = 0;
	}
}
