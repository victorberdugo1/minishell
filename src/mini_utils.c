/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:39:05 by victor            #+#    #+#             */
/*   Updated: 2024/11/27 19:43:27 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var(char *name, char *env[])
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	construct_prompt(char *prompt, char *env[])
{
	char	*username;
	char	*hostname;
	char	cwd[PATH_MAX];

	username = find_env_var("USER", env);
	hostname = find_env_var("HOSTNAME", env);
	if (!username)
		username = "user";
	if (!hostname)
		hostname = "localhost";
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		strcpy(prompt, "prompt_error$ ");
		return ;
	}
	ft_strcpy(prompt, username);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, hostname);
	ft_strcat(prompt, " - ");
	ft_strcat(prompt, cwd);
	ft_strcat(prompt, "$ ");
}

int	print_version(int argc, char *argv[])
{
	if (argc > 1 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("Versión 1.0\n");
		return (0);
	}
	return (1);
}

char	*handle_prompt(char *prompt, char *env[])
{
	construct_prompt(prompt, env);
	return (readline(prompt));
}

void	process_command(char *line, int *exit_status)
{
	char	*expanded_line;
	char	*cmd_token;

	expanded_line = exp_env_vars(line, *exit_status);
	cmd_token = ft_strtok(expanded_line, ";");
	while (cmd_token != NULL)
	{
		execute_pipeline(cmd_token, exit_status);
		cmd_token = ft_strtok(NULL, ";");
	}
	free(expanded_line);
}
