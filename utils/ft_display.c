/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:33:13 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/08 12:50:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar(char c, int *res)
{
	write(1, &c, 1);
	(*res)++;
}

void	ft_putstr(char *src, int *res)
{
	int i;

	i = 0;
	while (src[i])
		ft_putchar(src[i++], res);
}
