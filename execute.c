#include "minishell.h"

void    execute(char **line)
{
    printf("line:%s\n", *line);
    g_shell.status = 1;
}