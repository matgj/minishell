#include "minishell.h"

void       test_cmd(t_cmds cmds)
{
    int l = 0;
    printf("cmd->name:%s\n",cmds.name); //affiche le contenu de name dans la struct cmds.
    printf("cmd->path:%s\n",cmds.path);
    printf("cmd->argc:%d\n",cmds.argc);
    while (cmds.argv[l])
   {
   // printf("cmds.argv\n");
       printf("cmd->argv[%i]:%s\n", l, cmds.argv[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
        l++;
   }
    printf("cmd->chevron:%i\n",cmds.chevron);
    printf("cmd->input:%i\n",cmds.input);
   // printf("cmd->output:%i\n",cmds.input);
}

void     test_env(t_cmds *cmds)
{
   int l = 0;
   while (g_shell.envp[l])
   {
       printf("g_shell->envp[%i]:%s\n", l, g_shell.envp[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
       l++;
   }
}