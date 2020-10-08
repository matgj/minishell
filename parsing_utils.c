/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:50:06 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 12:56:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
   // ft_printf("fd = %i\n", fd);
}
