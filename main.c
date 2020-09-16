#include "minishell.h"
#include <stdio.h>

void	read_line(char **line)
{
	int 	ret;

  	ret = get_next_line(1, line);
	//if (ret == 1)
	//	execute(line);
	//else
		//(EXIT_FAILURE); // faire une autre fonction qui free line
}


int main (int argc, char **argv, char **envp)
{
	int i;
	t_shell shell;	
	(void)argc;
	(void)argv;
	char *line;
	int ret;

	i = 0;
	line = NULL;
	g_shell.status = 0;
	g_shell.envp = env_import(envp);
	//printf("> ");
	while(g_shell.status == 0)
	{ 
		read_line(&line); //lire la ligne entree par l'utilisateur avec GNL
		parsing(line);   //separer la ligne en tableaux de commandes et de pipes
		//execute(&line); 
		//test_cmd(g_cmds);
	}
	exit_success();
//	free(line);
	return (0);
}
