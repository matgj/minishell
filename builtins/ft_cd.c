/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a42 <a42@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:21:37 by a42               #+#    #+#             */
/*   Updated: 2020/11/03 21:21:38 by a42              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_cd(t_cmds cmds)
{
	char	*home;

	if (cmds.argc > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		env_status(1);
	}
	else if (cmds.argc == 1)
	{
		home = find_env("HOME");
		chdir(home);
		mfree(home);
		env_status(0);
	}
	else if (chdir(cmds.argv[1]) < 0)
	{
		ft_printf("minishell: cd: no such file or directory: %s\n",
			cmds.argv[1]);
		env_status(1);
	}
	else
		env_status(0);
	return (1);
}
