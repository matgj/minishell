/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:25:04 by Mathis            #+#    #+#             */
/*   Updated: 2020/11/02 18:35:15 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

void	command_creation(t_cmds *cmds)
{
	int i;

	i = 0;
	cmds->path = NULL;
	cmds->input = 0;
	i = 0;
	g_shell.bad_redir = 0;
	if (!cmds->argv[i])
	{
		cmds->name = NULL;
		g_shell.bad_redir = 1;
	}
	else
		cmds->name = ft_strdup(cmds->argv[i]);
}

void	cmd_last_arg(t_cmds *cmds)
{
	int	i;

	if (!cmds->argc)
		return ;
	i = 0;
	while (cmds->argv[i] && (!ft_strncmp(cmds->argv[i], ">", 1) ||
		!ft_strcmp(cmds->argv[i], "<")))
		i += 2;
	if (!cmds->argv[i])
		cmds->name = NULL;
	else
		cmds->name = ft_strdup(cmds->argv[i]);
}

void	close_fds(t_cmds cmds)
{
	int i;

	i = 0;
	if (cmds.input != 0)
		close(cmds.input);
	while (cmds.output[i] != -1)
	{
		if (cmds.output[i] != STDOUT)
		{
			close(cmds.output[i]);
		}
		i++;
	}
}

void	free_binary(char *binary, char **paths)
{
	mfree(binary);
	free_split(paths);
}

void	plug_fd(t_cmds cmds)
{
	int i;

	i = 0;
	if (cmds.input != 0)
		dup2(cmds.input, 0);
	while (cmds.output[i] != -1)
	{
		if (cmds.output[i] != 1)
			dup2(cmds.output[i], 1);
		i++;
	}
}
