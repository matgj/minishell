/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:50:06 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 13:19:28 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c < 'Z'));
}

void	ft_cpy_var(char *str)
{
	int i;

	i = 0;
	g_shell.var_env = ft_strdup(str);
}

char	*dol_create(void)
{
	char *dol1;

	if (!(dol1 = (char *)mmalloc(sizeof(char) * 2)))
		return (NULL);
	dol1[0] = '$';
	dol1[1] = '\0';
	return (dol1);
}

void	ft_tab_output(int *tab_fds, int fd)
{
	int i;

	i = 0;
	while (tab_fds[i] != -1)
		i++;
	tab_fds[i] = fd;
}

void	print_syntax_err(char *line)
{
	ft_printf("syntax error near unexpected token bro. ");
	ft_printf("Remember, wherever there is a human being, ");
	ft_printf("there is an opportunity for a kindness.\n");
	env_status(2);
}
