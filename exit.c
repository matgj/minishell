/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:11 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 12:56:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(int status, int newline)
{
	ft_printf("exit");
	if (newline)
		ft_printf("\n");
	exit(status);
}

void			free_split(char **tabs)
{
	int i;

	i = 0;
	while (tabs[i])
		free(tabs[i++]);
	free(tabs);
}
