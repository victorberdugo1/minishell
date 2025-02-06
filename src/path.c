/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:15:41 by victor            #+#    #+#             */
/*   Updated: 2025/02/06 13:46:01 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* Searches for the file in the directories listed in PATH.                   */
/* Concatenates each path with the file and checks if it exists.              */
/* Returns the full path if found, or NULL if not found.                      */
/* ************************************************************************** */
char	*find_executable_path(char **paths, char *file)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, file);
		free(temp);
		if (access(path, F_OK | X_OK | R_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/* Frees all elements of an array of strings and then the array itself.       */
/* ************************************************************************** */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/* ************************************************************************** */
/* Retrieves the value of the PATH variable from the environment.             */
/* Returns the PATH value or NULL if not found.                               */
/* ************************************************************************** */
char	*get_path_from_env(char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	return (path);
}

/* ************************************************************************** */
/* Searches for a command in the current directory or the PATH.               */
/* Checks if the file is executable in the current directory or any PATH      */
/* Returns the full path to the executable or NULL if not found.              */
/* ************************************************************************** */
char	*find_command_in_path(char *file, char **env)
{
	char	**paths;
	char	*path;
	char	*current_dir_path;

	if (file[0] == '/' && access(file, F_OK | X_OK | R_OK) == 0)
	{
		path = ft_strdup(file);
		return (path);
	}
	current_dir_path = ft_strjoin("./", file);
	if (access(current_dir_path, F_OK | X_OK | R_OK) == 0)
	{
		path = ft_strdup(current_dir_path);
		free(current_dir_path);
		return (path);
	}
	free(current_dir_path);
	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	path = find_executable_path(paths, file);
	free_array(paths);
	return (path);
}
