/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:40:02 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/08 12:50:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_flags_prec(const char *src, int *i, va_list arg_list, t_printf *conv)
{
	++(*i);
	if (src[*i] == '*' || (src[*i] >= '0' && src[*i] <= '9'))
	{
		if (src[*i] == '*')
		{
			conv->prec = (int)va_arg(arg_list, int);
			if (conv->prec < 0)
				conv->prec = -1;
			(*i)++;
		}
		else
			conv->prec = ft_atoi_mini(src, i);
	}
	else
		conv->prec = 0;
}

void	ft_flags_wid(const char *src, int *i, va_list arg_list, t_printf *conv)
{
	if (src[*i] == '*' || (src[*i] >= '0' && src[*i] <= '9'))
	{
		if (src[*i] == '*')
		{
			conv->wid = (int)va_arg(arg_list, int);
			if (conv->wid < 0)
			{
				conv->flag = '-';
				conv->wid = conv->wid * -1;
			}
			(*i)++;
		}
		else
			conv->wid = ft_atoi_mini(src, i);
	}
}

void	ft_flags_zero_minus(const char *src, int *i, t_printf *conv)
{
	while (src[*i] == '0' || src[*i] == '-')
	{
		conv->flag = src[*i];
		if (src[*i] == '-')
		{
			conv->flag = '-';
			break ;
		}
		(*i)++;
	}
	while (src[*i] == '0' || src[*i] == '-')
		(*i)++;
}
