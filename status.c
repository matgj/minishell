/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:08:06 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 14:05:49 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pos_var_env(char *env_var)
{
	int		i;
	char	*to_find;

	i = 0;
	if (!(to_find = (char *)ft_calloc(sizeof(char), ft_strlen(env_var) + 2)))
		return (0);
	ft_strcat(to_find, env_var);
	ft_strcat(to_find, "=");
	while (g_shell.envp[i])
	{
		if (!ft_strncmp(g_shell.envp[i], to_find, ft_strlen(to_find)))
		{
			mfree(to_find);
			return (i);
		}
		++i;
	}
	mfree(to_find);
	return (-1);
}

void	delete_var_env(char *env_var)
{
	int		i;
	int		j;
	char	**new_envp;
	int		pos;

	i = 0;
	if ((pos = pos_var_env(env_var)) == -1)
		return ;
	while (g_shell.envp[i])
		i++;
	if (!(new_envp = (char **)ft_calloc(sizeof(char *), i + 1)))
		return ;
	i = 0;
	j = 0;
	while (g_shell.envp[i])
	{
		if (i != pos)
			new_envp[j++] = ft_strjoin(g_shell.envp[i], "");
		i++;
	}
	free_split(g_shell.envp);
	g_shell.envp = new_envp;
}

void	add_env_status(char *env_var)
{
	char	**envp;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(env_var, '=');
	delete_var_env(split[0]);
	free_split(split);
	while (g_shell.envp[i])
		i++;
	if (!(envp = (char **)ft_calloc(sizeof(char *), i + 2)))
		return ;
	i = 0;
	while (g_shell.envp[i])
	{
		envp[i] = ft_strjoin(g_shell.envp[i], "");
		i++;
	}
	envp[i] = ft_strjoin(env_var, "");
	free_split(g_shell.envp);
	g_shell.envp = envp;
}

void	env_status(int n)
{
	char	*status;
	char	*env_var;

	status = ft_itoa(n);
	g_shell.status = n;
	env_var = ft_strjoin("?=", status);
	add_env_status(env_var);
	mfree(env_var);
	mfree(status);
}
