/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:11 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/24 10:52:12 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(g_shell.envp);
}