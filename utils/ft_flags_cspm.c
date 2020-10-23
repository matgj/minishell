/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_cspm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:27:48 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/22 17:04:58 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_space_s(t_printf *conv, char *str, int *res, int len)
{
	int i;

	i = 0;
	while (conv->wid - len > 0)
	{
		ft_putchar(' ', res);
		conv->wid--;
	}
	while (i < len)
		ft_putchar(str[i++], res);
}

void	ft_minus_s(t_printf *conv, char *str, int *res, int len)
{
	int i;

	i = 0;
	while (i < len)
		ft_putchar(str[i++], res);
	while (conv->wid - len > 0)
	{
		ft_putchar(' ', res);
		conv->wid--;
	}
}

void	ft_zero_s(t_printf *conv, char *str, int *res, int len)
{
	int i;

	i = 0;
	while (conv->wid - len > 0)
	{
		ft_putchar('0', res);
		conv->wid--;
	}
	while (i < len)
		ft_putchar(str[i++], res);
}

void	ft_flag_p_spaces(t_printf *conv, char *str, int *res, int len)
{
	if (conv->flag == '+' && *str == '0')
	{
		if (conv->flag == '+' && *str == '0' && conv->wid > 2
		&& conv->prec >= 0)
			len--;
		while (conv->wid > len + 2)
		{
			ft_putchar(' ', res);
			conv->wid--;
		}
		ft_putstr("0x", res);
		if (*str == '0' && conv->prec < 0)
			ft_putstr(str, res);
		else if (*str != '0' && conv->prec >= 0 && conv->flag == '+')
			ft_putstr(str, res);
	}
	else
	{
		while (conv->wid-- > len + 2)
			ft_putchar(' ', res);
		ft_putstr("0x", res);
		ft_putstr(str, res);
	}
	mfree(str);
	str = NULL;
}

void	ft_flag_p(t_printf *conv, char *str, int *res, int len)
{
	if (conv->flag == '-')
	{
		ft_putstr("0x", res);
		ft_minus_s(conv, str, res, len);
	}
	else if (conv->flag == '+' && *str == '0' && conv->prec == '0'
	&& conv->wid <= 2)
		ft_putstr("0x", res);
	else if (conv->flag == '0')
	{
		ft_putstr("0x", res);
		ft_zero_s(conv, str, res, len);
	}
	else
		ft_flag_p_spaces(conv, str, res, len);
}
