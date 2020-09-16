#include "minishell.h"

int    command_type(t_cmds *cmds) //si cest une builtin fonction on doit la coder nous meme, donc on redirige vers lexecution de notre propre ft_builtin
{
    //  if (!strcmp(cmds.name,"echo"))
    //     ft_echo(cmds);
    //  else if(!strcmp(cmds.name,"cd"))
    //     ft_cd(cmds);
    //  else if(!strcmp(cmds.name,"pwd"))
    //     ft_pwd(cmds;
    //  else if(!strcmp(cmds.name,"export"))
    //     ft_export(cmds);
    //  else if(!strcmp(cmds.name,"unset"))
    //     ft_unset(cmds);
    //  else if(!strcmp(cmds.name,"env"))
    //     ft_env(cmds);
    //  else if(!strcmp(cmds.name,"exit"));
    //     ft_exit(cmds);
    //  else 
        return (0);
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
     i = 0;
    while (cmds->argv[i])
	  {
	  	if (cmds->argv[i][0] == 3)
	  	{
		  	free(cmds->argv[i]);
		  	cmds->argv[i] = ft_strdup("");
		  }
      i++;
  	}
}


//A common use of pipes is to send data to or receive data 
//from a program being run as a subprocess. 
//One way of doing this is by using a combination of 
//pipe (to create the pipe), fork (to create the subprocess),
//dup2 (to force the subprocess to use the pipe as its standard 
//input or output channel), and exec (to execute the new program). 

//fork()
   //Negative Value: creation of a child process was unsuccessful.
   //Zero: Returned to the newly created child process.
   //Positive value: Returned to parent or caller. The value contains process ID of newly created child process.


void    command_exec(t_cmds cmds)
{
    pid_t   pid;
    int     i;
    int     ret;

    i = 0;
  if (!command_type(&cmds)) //pour savoir si c une builtin ou pas
   { 
    if (cmds.input < 0) //si l'open de mon fichier a renvoye -1 cest qu il existe pas
      exit(127); //127 est revnoye par /bin/sh lorsquil ne trouve pas le fichier ou folder, permet de renvoyer "zsh: no such file or directory:"
    if ((pid = fork()) == -1)
      printf("fork error\n");
    else if (pid == 0) //je suis dans le child
      {  
         if (cmds.input != 0) //si jai un input dun autre fichier a prendre
          if(dup2(cmds.input, STDIN) == -1) //forcer le subprocess a utiliser le pipe en IN 
              printf("dup2 error input\n"); 
          while(cmds.output[i] != -1) //je parcours mon tableau de output avec les fd de chaque cmd separees par des redir
          {
            if (cmds.output[i] != -1)                
                if(dup2(cmds.output[i], STDOUT) == -1) //forcer le subprocess a utiliser le pipe en OUT, j
                   printf("dup2 error ouput\n"); 
            i++;
          }
        if (!ft_strcmp(cmds.name, "echo"))
           cmds.path = "/bin/echo"; //if no path return error no path
        else if (!ft_strcmp(cmds.name, "ls"))
             cmds.path = "/bin/ls"; 
        else if (!ft_strcmp(cmds.name, "wc"))
             cmds.path = "/usr/bin/wc"; 
        else if (!ft_strcmp(cmds.name, "cat"))
            cmds.path = "/bin/cat";
        else if (!ft_strcmp(cmds.name, "grep"))
            cmds.path = "/usr/bin/grep";
        char *env[]={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin:/Library/Frameworks/Python.framework",NULL};
        if ((ret = execve(cmds.path, cmds.argv, env)) == -1) // toujours bien mettre la path exacte /bin/ls en arg1 (filename)
               printf("execve error\n");                  //les fonctions exec remplacent le processus en cours avec un nouveau process
      }
      i = 0;
      if (cmds.input != 0)
        close(cmds.input);
      while (cmds.output[i] != -1) 
      {
        if (cmds.output[i] != -1)
         close(cmds.output[i]);
         i++;
      }
   }

   else 
      printf("builtin function \n");

    i = 0;
	 while (cmds.argv[i])
		 free(cmds.argv[i++]);
  	free(cmds.name);
	  free(cmds.argv);
	  free(cmds.path);
}

void    command_management(t_cmds *cmds)
{
    int ret;
    pid_t pid;

    if(!cmds->argc)
      return;
    command_creation(cmds); // pour initaliser name dans la struct cmd
    redirection(cmds);
   // test_cmd(*cmds);
  //  if (!command_type(cmds)) //pour savoir si cest une builtin fonction, si ca n'est pas une builtin on execute l'exe qu'on a dans path
  //          command_exec(cmds); //on execute le .exe qui se trouve dans la bonne path avec execve
}
