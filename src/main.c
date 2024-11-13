/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:30:57 by victor            #+#    #+#             */
/*   Updated: 2024/11/13 22:38:06 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int main(int argc, char *argv[], char *env[])
{
    char *line;
    int exit_status = 0;

    if (argc > 1)
	{
        for (int i = 1; i < argc; i++)
		{
            if (strcmp(argv[i], "--debug") == 0)
			{
                printf("Modo de depuración habilitado.\n");
            }
			else if (strcmp(argv[i], "--version") == 0)
			{
                printf("Versión 1.0\n");
                return 0;
            }
        }
    }
    if (env != NULL)
	{
        for (int i = 0; env[i] != NULL; i++) {
            //printf("Variable de entorno: %s\n", env[i]);
        }
    }
    while (1) {
        line = readline("$ ");
        if (!line)
            break;
        add_history(line);
        char *expanded_line = exp_env_vars(line, exit_status);
        char *cmd_token = strtok(expanded_line, ";");
        while (cmd_token != NULL)
		{
            char *sub_token = strtok(cmd_token, "|");
            while (sub_token != NULL)
			{
                char *cmd = sub_token;
                if (ft_is_builtin(cmd))
				{
                    ft_execute(cmd, &exit_status);
                }
				else
				{
                    ft_command(cmd, &exit_status);
                }
                sub_token = strtok(NULL, "|");
            }
            cmd_token = strtok(NULL, ";");
        }
        free(expanded_line);
        free(line);
    }
    return 0;
}
