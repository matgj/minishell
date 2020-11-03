/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a42 <a42@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:22:06 by a42               #+#    #+#             */
/*   Updated: 2020/11/03 21:22:32 by a42              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_echo(t_cmds cmds)
{
	int			i;
	int			nflag;

	if (!cmds.argv[1])
		write(1, "\n", 1);
	else
	{
		i = 0;
		nflag = 0;
		while (i < cmds.argc)
		{
			nflag += (!ft_strcmp("-n", cmds.argv[i])) ? 1 : 0;
			i++;
		}
		i = (nflag > 0) ? nflag + 1 : 1;
		while (i < cmds.argc)
		{
			ft_putstr_fd(cmds.argv[i++], 1);
			(i == cmds.argc) ? 0 : write(1, " ", 1);
		}
		(nflag == 0) ? write(1, "\n", 1) : 0;
	}
	env_status(0);
	return (1);
}
