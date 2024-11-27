/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:56:07 by victor            #+#    #+#             */
/*   Updated: 2024/11/27 18:33:26 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '|')
		{
			count++;
		}
		str++;
	}
	return (count + 1);
}

void	handle_pipe_error(void)
{
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	handle_fork_error(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}

void	close_pipe(int pipefd)
{
	if (pipefd != -1)
	{
		close(pipefd);
	}
}

void	exec_command(char **args)
{
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}
