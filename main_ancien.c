/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ancien.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:02 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/25 16:38:44 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_shell		shell;
	t_printf	printf;
	char		*line;
	int			fd;

	(void)argc;
	(void)argv;
	if (read(0, NULL, 0) == -1)
		return (0);
	if ((fd = dup(0)) == -1)
	 	return (0);
	close(fd);
	g_shell.redir = 0;
	g_shell.dquotes = 0;
	g_shell.envp = env_import(envp);
	env_status(0);
	// //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// (!g_shell.no_first_env) ? g_shell.envp = env_import(envp) : 0;
	// //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_printf("\e[1;1H\e[2J\n");
	printf.fd = 2;
	while (1)
	{
		ft_printf("\e[1m" "bash-42$ " "\e[0m", 25);
		signals();
		read_line(&line);
		parsing(line);
	}
	return (0);
}
