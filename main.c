/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:02 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/12 13:35:48 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int main (int argc, char **argv, char **envp)
{
	int i;
	t_shell shell;
	t_printf printf;
	(void)argc;
	(void)argv;
	char *line;
	int z;

	i = 0;
	g_shell.redir = 0;
	g_shell.dquotes = 0;
	g_shell.status = 0;
	g_shell.d = 0;
	g_shell.envp = env_import(envp);
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
