/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:16 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 16:22:23 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell g_shell;

char	**env_import(char **envp)
{
	char 	**tab;
	int 	i;

	i = 0;
	while((envp[i]))
		i++;
	if(!(tab = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	i = 0;
	while ((envp[i] != NULL))
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}