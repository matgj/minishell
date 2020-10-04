/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:53:05 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/02 15:41:20 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cut_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * (ft_strlen(s) - i + 1))))
		return (0);
	i++;
	while (s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save;
	int			ret;

	*line = NULL;
	ret = 2;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_check_bn(save) && ret != 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[ret] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	*line = ft_cpy_line(save);
	save = cut_line(save);
	if (ret == 0)
	{
		return (0);
	}
	return (1);
}
