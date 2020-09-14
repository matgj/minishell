#include "minishell.h"

void       test_cmd(t_cmds cmds)
{
    int l = 0;
    printf("cmds->name:%s\n",cmds.name); //affiche le contenu de name dans la struct cmds.
    printf("cmds->path:%s\n",cmds.path);
    printf("cmds->argc:%d\n",cmds.argc);
    while (cmds.argv[l])
   {
   // printf("cmds.argv\n");
       printf("cmds->argv[%i]:%s\n", l, cmds.argv[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
        l++;
   }
   
    printf("cmds->chevron:%i\n",cmds.chevron);
    printf("cmds->input:%i\n",cmds.input);
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

void    test_tab_cmds(t_cmds *cmds, int l)
{
   // int l = 0;
    int i = 0;
    while (cmds[l].name)
    {
        while (cmds[l].output[i] != -1)
     {
       // printf("cmds.argv\n");
         printf("cmds[%i]->ouput[%i]:%i\n", l, i, cmds[l].output[i]); //affiche le tab ouput dune commande
         i++;
      }   
     l++;
    }
}