/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:35 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 16:16:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

int    command_type(t_cmds *cmds)
{
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
        cmds->name = ft_strdup(cmds->argv[i]); 
}

/*
//A common use of pipes is to send data to or receive data 
//from a program being run as a subprocess. 
//One way of doing this is by using a combination of 
//pipe (to create the pipe), fork (to create the subprocess),
//dup2 (to force the subprocess to use the pipe as its standard 
//input or output channel), and exec (to execute the new program). 
*/

void   command_exec_child(t_cmds *cmds)
{ 
    int i;
    int ret;

    i = 0;
    if (cmds->input < 0)
       {
        exit(1);
       }
    if (cmds->input != 0) 
    {
     if(dup2(cmds->input, STDIN) == -1) 
         ft_printf("dup2 error input\n"); 
    }
     while(cmds->output[i] != -1) 
     {
       if (cmds->output[i] != STDOUT) 
       {               
           if(dup2(cmds->output[i], STDOUT) == -1)
              ft_printf("dup2 error ouput\n"); 
       }
       i++;
     }
   if (!ft_strcmp(cmds->name, "echo"))
      cmds->path = "/bin/echo";
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
   if ((ret = execve(cmds->path, cmds->argv, env)) == -1)
          {
            write(2, "minishell: ", 11);
		    	  write(2, cmds->name, ft_strlen(cmds->name));
		      	write(2, ": command not found\n", 20);
		      	exit(127);
          }
}
/*
//fork()
   //Negative Value: creation of a child process was unsuccessful.
   //Zero: Returned to the newly created child process.
   //Positive value: Returned to parent or caller. The value contains process ID of newly created child process.
*/

int   command_exec(t_cmds cmds)
{
    pid_t   pid;
    int     i;
    int     ret;

    i = 0;
    if (!command_type(&cmds))
    { 
      if ((pid = fork()) == -1)
      {
        ft_printf("fork error\n");
        exit(127);
      }
      else if (pid == 0)
        command_exec_child(&cmds);
      else 
       g_shell.pid = pid;
   }

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
    command_creation(cmds);
    cmd_last_arg(cmds);
    redirection(cmds);
    while(cmds->argv[i])
        i++;
    cmds->argc = i;
  
}