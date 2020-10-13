/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:36:01 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 20:52:45 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *str;

	if (!s)
		return (ft_strdup(""));
	if (ft_strlen(s) < start)
		len = 0;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_memmove((void *)str, &s[start], len);
	str[len] = '\0';
	return ((char *)str);
}
