/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:11 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 13:08:04 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

void	exit_shell(int status, int newline)
{
//	free environnement;
	ft_printf("exit");
	if (newline)
		ft_printf("\n");
	free_all_malloc();
	exit(status);
}

void	free_split(char **tabs)
{
	int i;

	i = 0;
	while (tabs[i])
		mfree(tabs[i++]);
	mfree(tabs);
}

void	free_struct(t_cmds cmds)
{
	int i;

	i = 0;
	while (cmds.argv[i])
		mfree(cmds.argv[i++]);
	mfree(cmds.name);
	mfree(cmds.argv);
	mfree(cmds.path);
}
