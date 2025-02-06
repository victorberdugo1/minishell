/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:50:27 by victor            #+#    #+#             */
/*   Updated: 2025/02/06 13:25:54 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* is_special: returns true if s equals ">>", "<<", ">", "<", or "|"          */
/* ************************************************************************** */
bool	is_special(const char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<")
		|| !ft_strcmp(s, ">") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "|"))
		return (true);
	return (false);
}

/* ************************************************************************** */
/* Checks if a string consists only of 'n' characters after the first one.    */
/* - Starts checking from the second character (s[1]).                        */
/* - Returns true if all remaining characters are 'n', false otherwise.       */
/* ************************************************************************** */
static bool	all_is_n(const char *s)
{
	int	i;

	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (true);
	else
		return (false);
}

/* ************************************************************************** */
/* check_n: Checks for the '-n' flag and updates j if valid.                  */
/*                                                                            */
/* Skips arguments starting with "-n" if they consist only of 'n' characters. */
/* Returns true if at least one valid '-n' flag is found.                     */
/* ************************************************************************** */
static bool	check_n(char **av, int *j)
{
	bool	n;

	n = false;
	while (av[*j] && !strncmp(av[*j], "-n", 2))
	{
		if (*j == 0 && all_is_n(av[*j]))
		{
			n = true;
			(*j)++;
		}
		else if (all_is_n(av[*j]))
			(*j)++;
		else
			break ;
	}
	return (n);
}

/* ************************************************************************** */
/* exe_echo: Mimics the 'echo' command, handling '-n' flag and quotes.        */
/*                                                                            */
/* - If '-n' is present, suppresses the newline at the end.                   */
/* - Processes each argument to handle quotes correctly.                      */
/* - Prints arguments separated by spaces.                                    */
/* ************************************************************************** */
int	exe_echo(char **av)
{
	bool	n;
	int		j;
	char	*processed_arg;

	if (!av || !av[0])
		return (ft_printf("\n"), 0);
	j = 0;
	n = check_n(av, &j);
	while (av[j])
	{
		processed_arg = strdup(av[j]);
		if (!processed_arg)
			return (1);
		process_string(&processed_arg);
		ft_printf("%s", processed_arg);
		free(processed_arg);
		if (av[j + 1])
			ft_printf(" ");
		j++;
	}
	if (!n)
		ft_printf("\n");
	return (0);
}
