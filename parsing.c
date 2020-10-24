/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:39 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 11:51:25 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

t_cmds	parse_cmd(char *cmds_pipe)
{
	char	**token;
	int		i;
	t_cmds	cmds;

	i = 0;
	parse_token(&token, cmds_pipe);
	while (token[i])
		i++;
	if (!(cmds.argv = ft_calloc(i + 1, sizeof(char *))))
		return (cmds);
	cmds.argc = i;
	i = 0;
	while (token[i])
	{
		cmds.argv[i] = token[i];
		insert_actions(cmds.argv[i]);
		i++;
	}
	mfree(token);
	i = 0;
	while (i < ARG_MAX)
		cmds.output[i++] = -1;
	command_management(&cmds);
	//test_cmd(cmds);
	return (cmds);
}

t_cmds	*parse_pipe(char *cmds_semi)
{
	t_cmds	*cmds;
	char	**cmds_pipe;
	int		cpt;
	t_cmds	nul;

	cpt = 0;
	cmds_pipe = ft_split(cmds_semi, '|');
	mfree(cmds_semi);
	while (cmds_pipe[cpt])
		cpt++;
	if (!(cmds = ft_calloc(sizeof(t_cmds), cpt + 1)))
		return (NULL);
	cpt = -1;
	while (cmds_pipe[++cpt])
	{
		if (!empty(cmds_pipe[cpt]))
			cmds[cpt] = parse_cmd(cmds_pipe[cpt]);
		else
			mfree(cmds_pipe[cpt]);
	}
	mfree(cmds_pipe);
	nul.name = NULL;
	cmds[cpt] = nul;
	command_plug(cmds);
	return (cmds);
}

void	command_loop(t_cmds *cmds_pipe)
{
	int i;

	i = 0;
	while (cmds_pipe[i].name)
		command_exec(cmds_pipe[i++]);
	check_pid();
	mfree(cmds_pipe);
}

/*
**d'abord on decoupe la ligne lue par gnl en tableau de ligne de commandes,
**chaque ";" dans une ligne constitue une ligne de commande à
**executer independamment des autres
**ls -l | cat -e ; echo my name is $USER ==> cest comme si dabord on
**entrait ls -l dans le terminal et qu'on appuie sur ENTER
**puis qu'on entrait echo my name is $USER, ce sont deux
**commandes totalement distinctes
*/

void	parsing(char *line)
{
	char	**cmds_semi;
	char	*line_env;
	int		l;
	int		i;
	t_cmds	*cmds_pipe;

	l = 0;
	quotes(line);
	line_env = var_env(line);
	if (!syntax_error(line_env))
	{
		print_syntax_err(line);
		return ;
	}
	//mfree(line);
	cmds_semi = ft_split(line_env, ';');
	mfree(line_env);
	while (cmds_semi[l])
	{
		cmds_pipe = parse_pipe(cmds_semi[l++]);
		command_loop(cmds_pipe);
	}
	mfree(cmds_semi);
}

/*
**read line and manage ctrl d
*/

void	read_line(char **line)
{
	int		ret;
	char	buf[1];
	int		i;

	i = 1;
	ret = get_next_line(1, line);
	if (!ret && !ft_strlen(*line))
	{
		mfree(*line);
		exit_shell(g_shell.status, 1);
	}
	while (!ret)
	{
		ret = read(1, buf, 1);
	}
}
