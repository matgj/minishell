/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:26 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 12:05:03 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_cmds cmds)
{
	int i;

	i = 0;
	while (cmds.argv[i])
			ft_printf("%s", cmds.argv[i++]); //juste un exemple
}

void    ft_cd(t_cmds cmds)
{
	ft_printf("code the cd here");
}
// void    ft_pwd(t_cmds cmds);
// void    ft_export(t_cmds cmds);
// void    ft_unset(t_cmds cmds);
// void    ft_env(t_cmds cmds);
void    ft_exit(t_cmds cmds)
{
	if (cmds.argc == 1)
		exit_shell(0, 0); //ces juste un exemple jimagine que cest pls complique que ca

}
