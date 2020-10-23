/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_diux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:20:12 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/22 17:04:58 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_zero_detail(t_printf *conv, char *src, int *res, int s_len)
{
	if (conv->wid > s_len && conv->prec < 0)
	{
		conv->flag == '0' ? ft_zero(conv, src, res, s_len)
			: ft_spaces(conv, src, res, s_len);
		if (conv->flag != '0')
			ft_putstr(src, res);
	}
	else if (conv->wid >= conv->prec && conv->wid >= 0)
	{
		ft_spaces(conv, src, res, s_len);
		ft_zero(conv, src, res, s_len);
	}
}

void	ft_flag_detail(t_printf *conv, int *res, char *src)
{
	int s_len;

	s_len = 0;
	while (src[s_len] != '\0')
		s_len++;
	if (conv->flag == '0' && conv->wid - conv->prec > s_len
		&& conv->prec != -1)
		conv->flag = '+';
	if (conv->prec > conv->wid || (conv->prec > s_len && conv->wid == -1))
		ft_zero(conv, src, res, s_len);
	else if ((conv->flag == '0' || conv->flag == '+') && conv->wid >= 0)
		ft_zero_detail(conv, src, res, s_len);
	else if (conv->flag == '-')
	{
		ft_zero(conv, src, res, s_len);
		ft_spaces(conv, src, res, s_len);
	}
	else
		ft_putstr(src, res);
	mfree(src);
	src = NULL;
}

void	ft_di(va_list arg_list, t_printf *conv, int *res, char *base_tab)
{
	char	*str;
	int		nb;

	nb = (int)va_arg(arg_list, int);
	str = ft_itoa_base(nb, 10, base_tab);
	ft_flag_detail(conv, res, str);
}

void	ft_u(va_list arg_list, t_printf *conv, int *res, char *base_tab)
{
	char			*str;
	unsigned int	nb;

	nb = (unsigned int)va_arg(arg_list, unsigned int);
	str = ft_itoa_base(nb, 10, base_tab);
	ft_flag_detail(conv, res, str);
}

void	ft_x(va_list arg_list, t_printf *conv, int *res, char *base_tab)
{
	char			*str;
	unsigned int	nb;

	nb = (unsigned int)va_arg(arg_list, unsigned int);
	str = ft_itoa_base(nb, 16, base_tab);
	ft_flag_detail(conv, res, str);
}
