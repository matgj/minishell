/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:43:28 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/08 12:50:33 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_define_type(va_list arg_list, t_printf *conv, int *res)
{
	if (conv->type == 'c')
		ft_c(arg_list, conv, res);
	else if (conv->type == 's')
		ft_s(arg_list, conv, res);
	else if (conv->type == 'd' || conv->type == 'i')
		ft_di(arg_list, conv, res, "0123456789");
	else if (conv->type == 'u')
		ft_u(arg_list, conv, res, "0123456789");
	else if (conv->type == 'x')
		ft_x(arg_list, conv, res, "0123456789abcdef");
	else if (conv->type == 'X')
		ft_x(arg_list, conv, res, "0123456789ABCDEF");
	else if (conv->type == 'p')
		ft_p(arg_list, conv, res, "0123456789abcdef");
	else if (conv->type == '%')
		ft_mod(conv, res);
}

int		ft_check_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == '%' || c == 'd'
	|| c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

void	ft_look_args(const char *src, int *i, va_list arg_list, t_printf *conv)
{
	conv->wid = -1;
	conv->flag = '+';
	conv->prec = -1;
	conv->type = -1;
	if (src[*i] == '0' || src[*i] == '-')
		ft_flags_zero_minus(src, i, conv);
	if ((src[*i] >= '0' && src[*i] <= '9') || src[*i] == '*')
		ft_flags_wid(src, i, arg_list, conv);
	if (src[*i] == '.')
		ft_flags_prec(src, i, arg_list, conv);
	if (ft_check_type(src[*i]) == 1)
	{
		conv->type = src[*i];
		(*i)++;
	}
}

int		ft_ret(va_list arg_list, t_printf *conv, int res)
{
	va_end(arg_list);
	free(conv);
	return (res);
}

int		ft_printf(const char *src, ...)
{
	va_list		arg_list;
	int			i;
	int			res;
	t_printf	*conv;

	va_start(arg_list, src);
	i = 0;
	res = 0;
	if (!(conv = (t_printf*)malloc(sizeof(t_printf))))
		return (-1);
	while (src[i] != 0)
	{
		while (src[i] != '%' && src[i] != '\0')
			ft_putchar(src[i++], &res);
		if (src[i] == '%')
		{
			i++;
			ft_look_args(src, &i, arg_list, conv);
			if (ft_check_type(conv->type) == 1)
				ft_define_type(arg_list, conv, &res);
			else
				break ;
		}
	}
	return (ft_ret(arg_list, conv, res));
}
