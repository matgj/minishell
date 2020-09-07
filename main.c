#include "minishell.h"
#include <stdio.h>

void	read_line(char **line)
{
	int 	ret;

  	ret = get_next_line(0, line);
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
	char **cmd;
//	t_cmds	*cmd;
	int ret;

	i = 0;
	line = NULL;
	g_shell.status = 0;
	g_shell.var_env = env_import(envp);

	char *test[] ={"ls",NULL};
	char *env[] ={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin",NULL};
	execve("ls", test, env);
	while(g_shell.status == 0)
	{ 
		printf("> ");
		read_line(&line); //lire la ligne entree par l'utilisateur avec GNL
		parsing(line);   //separer la ligne en tableaux de commandes et de pipes
		//execute(&line); 
	}
	exit_success();
//	free(line);
	return (0);
}
