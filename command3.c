/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:05:46 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/22 19:26:42 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	create_filename(char *path, char *cmd, char *binary[2])
{
	if (!(binary[0] = (char *)ft_calloc(sizeof(char),
		(ft_strlen(cmd) + ft_strlen(path) + 2))))
		return ;
	binary[0] = ft_strcat(binary[0], path);
	binary[0] = ft_strcat(binary[0], "/");
	binary[0] = ft_strcat(binary[0], cmd);
}

char	*find_env(char *to_find)
{
	char	**env;
	char	**split;
	char	*to_find2;
	char	*var;

	env = g_shell.envp;
	if (!(to_find2 = (char *)ft_calloc(sizeof(char), ft_strlen(to_find) + 2)))
		return (NULL);
	ft_strcat(to_find2, to_find);
	ft_strcat(to_find2, "=");
	while (*env)
	{
		if (!ft_strncmp(*env, to_find2, ft_strlen(to_find2)))
		{
			split = ft_split(*env, '=');
			var = ft_strjoin(split[1], "");
			free_split(split);
			mfree(to_find2);
			return (var);
		}
		env++;
	}
	mfree(to_find2);
	return (NULL);
}

char	*find_relative_path(char *cmd)
{
	struct stat	buff;

	if (!stat(cmd, &buff))
		return (ft_strjoin(cmd, ""));
	else
		return (0);
}

char	*find_path(char *cmd)
{
	int			i;
	struct stat	buff;
	char		*binary[2];
	char		**paths;

	i = 0;
	if (!ft_strncmp("./", cmd, 2) || !ft_strncmp("/", cmd, 1))
		return (find_relative_path(cmd));
	binary[1] = find_env("PATH");
	if (!binary[1])
		return (NULL);
	paths = ft_split(binary[1], ':');
	while (paths[i])
	{
		create_filename(paths[i], cmd, binary);
		if (!stat(binary[0], &buff))
		{
			free_binary(binary[1], paths);
			return (binary[0]);
		}
		mfree(binary[0]);
		i++;
	}
	free_binary(binary[1], paths);
	return (NULL);
}
