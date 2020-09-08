#include "minishell.h"

void     test_argv(t_cmds *cmds)
{
    int l = 0;
    while (cmds->argv[l])
    {
        printf("cmd->argv[%i]:%s\n", l, cmds->argv[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
        l++;
    }
}


void    test_name(t_cmds *cmds)
{
    int l = 0;
    while (cmds->argv[l])
    {
        printf("cmd->name:%s\n", cmds->name); //affiche le contenu de name dans la struct cmds
        l++;
    }

}