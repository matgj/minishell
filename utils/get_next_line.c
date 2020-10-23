/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:53:05 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/22 17:04:58 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell g_shell;

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
		mfree(s);
		return (0);
	}
	if (!(str = mmalloc(sizeof(char) * (ft_strlen(s) - i + 1))))
		return (0);
	i++;
	while (s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	mfree(s);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save;
	int			ret;

	*line = NULL;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = mmalloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_check_bn(save) && ret != 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			mfree(buf);
			return (-1);
		}
		buf[ret] = '\0';
		save = ft_strjoin(save, buf);
	}
	mfree(buf);
	*line = ft_cpy_line(save);
	save = cut_line(save);
	if (ret == 0)
		return (0);
	return (1);
}
