/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_cspm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:18:39 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/08 12:50:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_c(va_list arg_list, t_printf *conv, int *res)
{
	unsigned char	c;
	char			flag;

	c = (unsigned char)va_arg(arg_list, int);
	flag = (conv->flag == '0' ? '0' : ' ');
	if (conv->flag == '-')
		ft_putchar(c, res);
	while (conv->wid-- > 1)
		ft_putchar(flag, res);
	if (conv->flag != '-')
		ft_putchar(c, res);
}

void	ft_mod(t_printf *conv, int *res)
{
	char flag;

	flag = (conv->flag == '0' ? '0' : ' ');
	if (conv->flag == '-')
		ft_putchar('%', res);
	while (conv->wid-- > 1)
		ft_putchar(flag, res);
	if (conv->flag != '-')
		ft_putchar('%', res);
}

void	ft_s(va_list arg_list, t_printf *conv, int *res)
{
	char	*str;
	int		len;

	len = 0;
	str = (char *)va_arg(arg_list, char *);
	if (!str)
		str = "(null)";
	while (str[len] && (len < conv->prec || conv->prec == -1))
		len++;
	if (conv->flag == '-')
		ft_minus_s(conv, str, res, len);
	else if (conv->flag == '0')
		ft_zero_s(conv, str, res, len);
	else
		ft_space_s(conv, str, res, len);
}

void	ft_p(va_list arg_list, t_printf *conv, int *res, char *base_tab)
{
	char		*str;
	long int	nb;
	int			len;

	len = 0;
	nb = (long int)va_arg(arg_list, void *);
	str = ft_itoa_base(nb, 16, base_tab);
	if (conv->flag == '-')
		conv->wid = conv->wid - 2;
	while (str[len])
		len++;
	ft_flag_p(conv, str, res, len);
}
