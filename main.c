/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:02 by Mathis            #+#    #+#             */
/*   Updated: 2020/11/03 21:22:28 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char			*gnl(void)
{
	char		*buf;
	int			ret;
	int			pos;
	char		red[2];

	pos = 0;
	buf = (char *)mmalloc(4096);
	while (1)
	{
		if ((ret = read(0, red, 1)) == -1)
			return (NULL);
		if (ret == 0 && pos == 0)
		{
			write(2, "  \b\bexit\n", 9);
			free_all_malloc();
			exit(g_shell.status);
		}
		if (!ret)
			write(2, "  \b\b", 4);
		else if ((red[0] == '\n' || pos >= 4095) && !(buf[pos] = '\0'))
			return (buf);
		else
			buf[pos++] = red[0];
	}
}

int				main(int argc, char **argv, char **envp)
{
	int			i;
	t_shell		shell;
	t_printf	printf;
	char		*line;
	int			fd;

	i = 0;
	(void)argc;
	(void)argv;
	if (read(0, NULL, 0) == -1)
		return (0);
	g_shell.redir = 0;
	g_shell.dquotes = 0;
	g_shell.bad_redir = 0;
	g_shell.envp = env_import(envp);
	env_status(0);
	ft_printf("\e[1;1H\e[2J\n");
	while (1)
	{
		ft_printf("\e[1m" "bash-42$ " "\e[0m", 25);
		signals();
		line = gnl();
		parsing(line);
	}
	return (0);
}
