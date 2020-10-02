/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:02 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/02 15:54:55 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	read_line(char **line)
{
	int 	ret;
	ret = get_next_line(1, line);
}

void prompt(void)
{
	fprintf(stderr, "\e[1m" "bash-42$ " "\e[0m"); //met en gras juste le dollar bash
}

int main (int argc, char **argv, char **envp)
{
	int i;
	t_shell shell;	
	(void)argc;
	(void)argv;
	char *line;
	int z;

	i = 0;
	g_shell.redir = 0;
	g_shell.dquotes = 0;
	g_shell.status = 0;
	g_shell.envp = env_import(envp);
	printf("\e[1;1H\e[2J\n"); //clean terminal
	while (1)
	{
		prompt();
		read_line(&line); //lire la ligne entree par l'utilisateur avec GNL
		parsing(line);   //separer la ligne en tableaux de commandes et de pipes
	}
	return (0);
}
