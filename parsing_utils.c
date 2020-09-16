#include "minishell.h"

//cette fonction permet de stocker les fds des nouveaux output
//ca va servir a gerer les pipes et >

void    ft_tab_output(int *tab_fds, int fd)
{
    int i;

    i = 0;
    while (tab_fds[i] != -1)
        i++;
    tab_fds[i] = fd;
}
