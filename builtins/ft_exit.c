/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:28:54 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/25 17:28:29 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_exit(char *arg)
{
	ft_printf("minishell: exit: %s: numeric argument required\n", arg);
	exit_shell(2, 1);
}

int	ft_exit(t_cmds cmds)
{
	int i;
	int done;

	if (cmds.argc == 1)
		exit_shell(g_shell.status, 1);
	else if (cmds.argc == 2)
	{
		i = -1;
		done = 1;
		while (cmds.argv[1][++i])
		{
			if ((cmds.argv[1][i] > '9' || cmds.argv[1][i] < '0')
				&& (cmds.argv[1][i] != '-' && cmds.argv[1][i] != '+'))
				done = 0;
		}
		if (done)
			exit_shell(ft_atoi(cmds.argv[1]),1);
		else
			ft_print_exit(cmds.argv[1]);
	}
	else
		ft_printf("minishell: exit: too many arguments\n");
	return (1);
}
