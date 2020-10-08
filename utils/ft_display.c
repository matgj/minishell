/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:33:13 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/08 15:59:36 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_printf g_printf;

void	ft_putchar(char c, int *res)
{
	write(g_printf.fd, &c, 1);
	(*res)++;
}

void	ft_putstr(char *src, int *res)
{
	int i;

	i = 0;
	while (src[i])
		ft_putchar(src[i++], res);
}
