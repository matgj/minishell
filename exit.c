#include "minishell.h"

int     exit_success(void)
{
    free_var();
    exit(EXIT_SUCCESS);
}

int     exit_failure(void)
{
    free_var();
    exit(EXIT_FAILURE);
}

void    free_var(void)
{
	free(g_cmds.envp);
}