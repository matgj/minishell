/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:20:35 by a42               #+#    #+#             */
/*   Updated: 2020/11/03 22:50:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_env(t_cmds cmds)
{
	int		i;

	i = 0;
	while (g_shell.envp[i])
	{
		if (g_shell.envp[i][0] != '?')
			ft_putendl_fd(g_shell.envp[i], 1);
		i++;
	}
	env_status(0);
	return (1);
}
