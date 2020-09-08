#include "minishell.h"

//t_cmds   command_type(t_cmds cmds)
//{
//   est-ce que ma fonction est builtin ?
//       si oui -> go utiliser les ft_echo ft_cd ft_pwd ft_export ft_unset ft_env ft_exit codes par nous meme, 
//   proto des builtins = void ft_cd(t_cmd cmd), et avec la struct cmd tu recuperes les args;
//       si non ->execve comme ci dessous, avec une fonction get_path qui recup la path exacte
// 
//}

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
    if(!cmds->argv[i])
        cmds->name = NULL;
    else
        cmds->name = ft_strdup(cmds->argv[i]); //je cree name dans la struct name
}

void    command_exec(t_cmds *cmds)
{
    pid_t   pid;

  if (!ft_strcmp(cmds->name,"ls"))
  {
   cmds->path = "/bin/ls";
    //cmds.envp = {"ls", "-l", NULL};
    char *env[]={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin:/Library/Frameworks/Python.framework",NULL};
  //  test_argv(&cmds);
  //   test_name(cmds);
   //  test_path(cmds);
   command_path(cmds);//
    if ((pid = fork()) == -1) //cd or exit called in child will not affect shells environment but only child, so we need to fork>
         printf("fork error\n");
    else if (pid == 0)
    {  
        if(execve(cmds->path, cmds->argv, env) == -1) // toujours bien mettre la path exacte /bin/ls en arg1 (filename)
             printf("execve error\n");                  //les fonctions exec remplacent le processus en cours avec un nouveau process
    }
  }
}

void    command_management(t_cmds cmds)
{
    int ret;
    pid_t pid;

    command_creation(&cmds); // pour initaliser name dans la struct cmd
    if (!command_type(&cmds)) //pour savoir si cest une builtin fonction, si ca n'est pas une builtin on execute l'exe qu'on a dans path
            command_exec(&cmds); //on execute le .exe qui se trouve dans la bonne path avec execve
     test_cmd(cmds);
  //  test_env(&cmds); //sors le des commentaires si tu veux vois ce que ca affiche
}
