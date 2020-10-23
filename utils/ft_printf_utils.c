/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:24:39 by magrosje          #+#    #+#             */
/*   Updated: 2020/10/22 17:04:41 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_atoi_mini(const char *src, int *i)
{
	unsigned int res;

	res = 0;
	while (src[*i] >= '0' && src[*i] <= '9')
	{
		res = res * 10 + src[*i] - '0';
		(*i)++;
	}
	return (res);
}

long int	ft_nblen(long int nb, int base)
{
	int i;

	i = 0;
	if (nb < 0)
		i++;
	while (nb != 0 && i++ < base)
		nb = nb / base;
	return (i);
}

static char	*ft_nb_zero(void)
{
	char *str;

	if (!(str = (char*)mmalloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char		*ft_itoa_base(long int nb, int base, char *base_tab)
{
	char		*str;
	int			len;
	long int	lnb;

	len = ft_nblen(nb, base);
	if (nb == 0)
		return (ft_nb_zero());
	else
	{
		lnb = nb;
		if (!(str = (char*)mmalloc(sizeof(char) * len)))
			return (NULL);
		if (nb < 0)
		{
			lnb = lnb * -1;
			str[0] = '-';
		}
		str[len] = '\0';
		while (len > 0 && lnb != 0)
		{
			str[--len] = base_tab[lnb % base];
			lnb = lnb / base;
		}
		return (str);
	}
}
