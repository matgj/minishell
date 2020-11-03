/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:48:52 by Mathis            #+#    #+#             */
/*   Updated: 2020/11/03 09:35:09 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;
extern t_printf g_printf;

void	signal_quit(int signal)
{
	if (g_shell.pid)
	{
		kill(g_shell.pid, signal);
		env_status(131);
		ft_printf("Quitter (core dumped)\n");
	}
	else
		ft_printf("\b\b  \b\b");
}

void	signal_interrupt(int signal)
{
	ft_printf("\b\b  \b\b");
	if (!g_shell.pid)
	{
		ft_printf("^C", 25);
		ft_printf("\n");
		ft_printf("\e[1m" "bash-42$ " "\e[0m", 25);
		env_status(130);
	}
	else
	{
		ft_printf("^C", 25);
		ft_printf("\n");
		kill(g_shell.pid, signal);
	}
}

void	signals(void)
{
	if (signal(SIGINT, &signal_interrupt) == SIG_ERR)
		ft_printf("Signal interrupt error\n");
	if (signal(SIGQUIT, &signal_quit) == SIG_ERR)
		ft_printf("Signal quit error\n");
}
