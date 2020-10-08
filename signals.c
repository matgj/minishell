/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:48:52 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 13:09:02 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

// Non-builtin commands started by Bash have signal handlers set to the values
// inherited by the shell from its parent.

//CtrlC sends SIGINT to the foreground process, Ctrl\ sends SIGQUIT. 
//The default handlers for both of them terminate the process, 
//but the handler for SIGQUIT will also create a core dump (unless core dumps are disabled).

void    signal_quit(int signal)
{
    if(g_shell.pid)
    {
        kill(g_shell.pid, signal);
        g_shell.status = 131;
        ft_printf("Quit: %d\n", g_shell.pid);
    }
}

void    signal_interrupt(int signal)
{
    ft_printf("\n");
    if (!g_shell.pid)
    {
           // fprintf(stderr, "\e[1m" "bash-42$ " "\e[0m");
           	write(2, "\e[1m" "bash-42$ " "\e[0m", 25);
            g_shell.status = 130;
    }
    else
        kill(g_shell.pid, signal);
}

void    signals(void)
{
    if(signal(SIGINT, &signal_interrupt) == SIG_ERR)
        ft_printf("Signal interrupt error\n");
    if(signal(SIGQUIT, &signal_quit) == SIG_ERR)
        ft_printf("Signal quit error\n");
}