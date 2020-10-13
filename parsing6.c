/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:52:10 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 18:22:56 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quotes(char *c, int *q, int *dq)
{
	g_shell.dquotes = 1;
	if (!*q && !*dq)
	{
		*dq = 1;
		*c = REPLACED;
	}
	else if (!*q && *dq)
	{
		*dq = 0;
		*c = REPLACED;
	}
}

void	simple_quotes(char *c, int *q, int *dq)
{
	if (!*q && !*dq)
	{
		*q = 1;
		*c = REPLACED;
	}
	else if (*q && !*dq)
	{
		*q = 0;
		*c = REPLACED;
	}
}
