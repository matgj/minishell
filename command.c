/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:35 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 12:56:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

int    command_type(t_cmds *cmds) //si cest une builtin fonction on doit la coder nous meme, donc on redirige vers lexecution de notre propre ft_builtin
{
    //  if (!strcmp(cmds->name,"echo"))
    //     ft_echo(cmds);
    //  else if(!strcmp(cmds->name,"cd"))
    //     ft_cd(cmds);
    //  else if(!strcmp(cmds->name,"pwd"))
    //     ft_pwd(cmds;
    //  else if(!strcmp(cmds->name,"export"))
    //     ft_export(cmds);
    //  else if(!strcmp(cmds->name,"unset"))
    //     ft_unset(cmds);
    //  else if(!strcmp(cmds->name,"env"))
    //     ft_env(cmds);
    //  else if(!strcmp(cmds->name,"exit"));
    //     ft_exit(cmds);
    //  else 
        return (0);
}

void	cmd_last_arg(t_cmds *cmds)
{
	int	i;

	if (!cmds->argc)
		return ;
	i = 0;
	while (cmds->argv[i] && (!ft_strcmp(cmds->argv[i], ">") ||
		!ft_strcmp(cmds->argv[i], "<")))
		i += 2;
	if (!cmds->argv[i])
		cmds->name = NULL;
	else
		cmds->name = ft_strdup(cmds->argv[i]);
}

void    command_creation(t_cmds *cmds)
{
    int i;

    i = 0;
    cmds->path = NULL;
    cmds->input = 0;
    i = 0;
    if (!cmds->argv[i])
        cmds->name = NULL;
    else
        cmds->name = ft_strdup(cmds->argv[i]); //je cree name dans la struct name
}

//A common use of pipes is to send data to or receive data 
//from a program being run as a subprocess. 
//One way of doing this is by using a combination of 
//pipe (to create the pipe), fork (to create the subprocess),
//dup2 (to force the subprocess to use the pipe as its standard 
//input or output channel), and exec (to execute the new program). 

void   command_exec_child(t_cmds *cmds)
{ 
    int i;
    int ret;

    i = 0;
    if (cmds->input < 0) //si l'open de mon fichier a renvoye -1 cest qu il existe pas
       {
        exit(1); //127 est revnoye par /bin/sh lorsquil ne trouve pas le fichier ou folder, permet de renvoyer "zsh: no such file or directory:"
       }
    if (cmds->input != 0) //si jai un input dun autre fichier a prendre
    {
     if(dup2(cmds->input, STDIN) == -1) //forcer le subprocess a utiliser le pipe en IN 
         ft_printf("dup2 error input\n"); 
    }
     while(cmds->output[i] != -1) //je parcours mon tableau de output avec les fd de chaque cmd separees par des redir
     {
       if (cmds->output[i] != STDOUT) 
       {               
           if(dup2(cmds->output[i], STDOUT) == -1) //forcer le subprocess a utiliser le pipe en OUT, j
              ft_printf("dup2 error ouput\n"); 
       }
       i++;
     }
   if (!ft_strcmp(cmds->name, "echo"))
      cmds->path = "/bin/echo"; //if no path return error no path
   else if (!ft_strcmp(cmds->name, "ls"))
        cmds->path = "/bin/ls"; 
   else if (!ft_strcmp(cmds->name, "wc"))
        cmds->path = "/usr/bin/wc"; 
   else if (!ft_strcmp(cmds->name, "cat"))
       cmds->path = "/bin/cat";
   else if (!ft_strcmp(cmds->name, "grep"))
       cmds->path = "/usr/bin/grep";
   else if (!ft_strcmp(cmds->name, "sleep"))
      cmds->path = "/bin/sleep";
   char *env[]={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin:/Library/Frameworks/Python.framework",NULL};
   if ((ret = execve(cmds->path, cmds->argv, env)) == -1) // toujours bien mettre la path exacte /bin/ls en arg1 (filename),  //les fonctions exec remplacent le processus en cours avec un nouveau process
          {
            write(2, "minishell: ", 11);
		    	  write(2, cmds->name, ft_strlen(cmds->name));
		      	write(2, ": command not found\n", 20);
		      	exit(127);
          }
}

//fork()
   //Negative Value: creation of a child process was unsuccessful.
   //Zero: Returned to the newly created child process.
   //Positive value: Returned to parent or caller. The value contains process ID of newly created child process.


int   command_exec(t_cmds cmds)
{
    pid_t   pid;
    int     i;
    int     ret;

    i = 0;
    if (!command_type(&cmds)) //pour savoir si c une builtin ou pas
    { 
      if ((pid = fork()) == -1)
      {
        ft_printf("fork error\n");
        exit(127);
      }
      else if (pid == 0) //je suis dans le child
        command_exec_child(&cmds);
      else 
       g_shell.pid = pid;
   }

   i = 0;
  // ft_printf("cmds.input %i \n", cmds.input);
   if (cmds.input != 0)
    close(cmds.input);
    while (cmds.output[i] != -1) 
    {
     // ft_printf("cmds.output[%i] %i \n",i, cmds.output[i]);
      if (cmds.output[i] != STDOUT)
      {
        close(cmds.output[i]);
      }
      i++;
    }
  
  i = 0;
	while (cmds.argv[i])
	  free(cmds.argv[i++]);
   free(cmds.name);
	 free(cmds.argv);
	 free(cmds.path);
 return(g_shell.status == 0);
}

void    command_management(t_cmds *cmds)
{
    int ret;
    pid_t pid;
    int i;

    i = 0;
    if(!cmds->argc)
      return;
    command_creation(cmds); // pour initaliser name dans la struct cmd
    cmd_last_arg(cmds); //cas ou line commence avec un chevron, cmd est le dernier arg
    redirection(cmds);
    while(cmds->argv[i])
        i++;
    cmds->argc = i;
     
    // i = 0;
    // while (cmds->argv[i])
	  // {
	  // 	if (cmds->argv[i][0] == REPLACED)
	  // 	{
	  //      //ft_printf("hey\n");
    //      free(cmds->argv[i]);
    //      cmds->argv[i] = ft_strjoin("","");
		//   }
    //   i++;
  	// }
   // test_cmd(*cmds);
  //  if (!command_type(cmds)) //pour savoir si cest une builtin fonction, si ca n'est pas une builtin on execute l'exe qu'on a dans path
  //          command_exec(cmds); //on execute le .exe qui se trouve dans la bonne path avec execve
}