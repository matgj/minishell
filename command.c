#include "minishell.h"

extern t_shell g_shell;


//t_cmds   command_finder(t_cmds cmds)
//{
 //   est-ce que ma fonction est builtin ?
 //       si oui -> go utiliser les ft_echo ft_cd ft_pwd ft_export ft_unset ft_env ft_exit codes par nous meme, 
// proto des builtins = void ft_cd(t_cmd cmd), et avec la struct cmd tu recuperes les args;
 //       si non ->execve comme ci dessous, avec une fonction get_path qui recup la path exacte
 // 
//}

void    command_creation(t_cmds cmds)
{
    int ret;
    pid_t pid;
    cmds.path = "/bin/ls";
    //cmds.arg[] = {"ls", "-l", NULL};
    if ((pid = fork()) == -1)
         printf("fork error\n");
    else if (pid == 0)
    {  
        if(execve(cmds.path, cmds.arg, g_shell.var_env) == -1) // toujours bien mettre la path exacte /bin/ls en arg1 (filename)
        printf("execve error\n");
    }
    
}