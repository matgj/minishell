#include "minishell.h"

void       test_cmd(t_cmds cmds)
{
    int l;

    l = 0;
    printf("cmd->name:%s\n",cmds.name); //affiche le contenu de name dans la struct cmds
    printf("cmd->path:%s\n",cmds.path);
    
   while (cmds.argv[l])
    {
        printf("cmd->argv[%i]:%s\n", l, cmds.argv[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
        l++;
    }
}

void     test_env(t_cmds *cmds)
{
   int l = 0;
   while (l < 10)
   {
       printf("cmd->envp[%i]:%s\n", l, g_shell.envp[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
       l++;
   }
}