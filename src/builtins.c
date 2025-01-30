/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:34:47 by victor            #+#    #+#             */
/*   Updated: 2025/01/30 20:17:37 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* Determines if the given command is a built-in shell command. It compares   */
/* the input string with a predefined list of built-in commands and returns   */
/* 1 if it's a built-in command, otherwise returns 0.                         */
/* ************************************************************************** */
int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/* Handles the execution of built-in shell commands like cd, exit, echo,      */
/* pwd, export, unset, and env. Based on the command, it performs the         */
/* appropriate action, such as changing the directory, printing the current   */
/* directory, setting/unsetting environment variables, or printing environment*/
/* variables. The exit status is updated accordingly for each command.        */
/* ************************************************************************** */
void ft_exec_builtin(char **cmd, int *exit_status, char **env)
{
    if (ft_strcmp(cmd[0], "cd") == 0)
        ft_execute_cd(cmd, env);
    else if (ft_strcmp(cmd[0], "echo") == 0)
        ft_execute_echo(exit_status);
    else if (ft_strcmp(cmd[0], "export") == 0)
        ft_execute_export(exit_status);
    else if (ft_strcmp(cmd[0], "unset") == 0)
        ft_execute_unset(exit_status);
    else if (ft_strcmp(cmd[0], "env") == 0)
        ft_execute_env(exit_status);
    else if (ft_strcmp(cmd[0], "pwd") == 0)
        ft_execute_pwd(exit_status);

    // Liberar memoria de cmd después de la ejecución
    for (int i = 0; cmd[i] != NULL; i++)
    {
        free(cmd[i]);  // Liberar cada string individualmente
    }
    free(cmd);  // Liberar el array de punteros
}

void ft_execute_cd(char **av, char **env)
{
   char *path;
    int result;
    char buf[PATH_MAX];
    char *tmp;
	(void)env;
    
	result = 0;
    if (!av[1])
    {
        path = getenv("HOME");
        if (!path)
        {
            printf("cd: HOME not set\n");
            return;
        }
    }
    else
    {
        path = av[1];
    }
    if (chdir(path) != 0)
    {
        perror("cd");
        result = 1;
    }
    if (!result)
    {
        tmp = getenv("PWD");
        if (tmp)
        {
            setenv("OLDPWD", tmp, 1);
        }
        if (getcwd(buf, sizeof(buf)) != NULL)
        {
            setenv("PWD", buf, 1);
        }
    }
}
