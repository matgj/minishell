/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:20 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 13:19:37 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**lier les fd des commandes separees par des pipes
**syscall pipe
**dans pipe, fd[0] = read et fd[1] = write
**fork return 0 on success
**on fork pour avoir 2 process et faire le lien entre deux programmes
**parent receive data from child (data are sent when fd is close,
** so child close fd1 and parent fd0)
**toujours fermer le fd qu on utilise pas (si on est dans child on
**ferme fd[0] sinon on ferme fd[1])
**ensuite on duplique les fd dans le child sur les stin et stout pour
**quon puisse exec() les program avec les streams standards
*/

void	command_plug(t_cmds *cmds)
{
	int	nb_cmds;
	int	fd[2];
	int	i;

	nb_cmds = 0;
	i = 0;
	while (cmds[nb_cmds].name)
		nb_cmds++;
	while (i < nb_cmds)
	{
		if (i != 0)
		{
			pipe(fd);
			ft_tab_output(cmds[i - 1].output, fd[1]);
			cmds[i].input = fd[0];
		}
		if (i == nb_cmds - 1)
			ft_tab_output(cmds[i].output, 1);
		ft_tab_output(cmds[i].output, -1);
		i++;
	}
}

/*
**enlever de la structure cmds les arguments que jai deja parsé
**en creant un nouveau tab d arg sans les cases NULL
*/

void	command_clean(t_cmds *cmds)
{
	int		i;
	int		pos;
	char	**new_argv;

	i = -1;
	pos = 0;
	while (++i < cmds->argc)
	{
		if (cmds->argv[pos] != NULL)
			pos++;
	}
	new_argv = ft_calloc(pos + 1, sizeof(char*));
	i = -1;
	pos = 0;
	while (++i < cmds->argc)
	{
		if (cmds->argv[i])
		{
			new_argv[pos] = cmds->argv[i];
			pos++;
		}
	}
	new_argv[pos] = NULL;
	mfree(cmds->argv);
	cmds->argv = new_argv;
}

void	check_pid(void)
{
	if (g_shell.pid < 0)
		return ;
	while (wait(&g_shell.pid) > 0)
		(void)g_shell.pid;
	if (g_shell.pid == 2)
		env_status(130);
	else if (g_shell.pid == 3 || g_shell.pid == 131)
		env_status(131);
	else
		env_status(WEXITSTATUS(g_shell.pid));
	g_shell.pid = 0;
}
