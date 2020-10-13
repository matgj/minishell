/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:54:18 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 18:05:56 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

char	*replace_env(char *to_find, char *line, int start, int end)
{
	char *new0;
	char *new1;
	char *new2;
	char *tab[3];

	tab[0] = ft_substr(line, 0, start);
	tab[1] = ft_substr(line, end, ft_strlen(line) - end);
	new0 = ft_strdup(tab[0]);
	new1 = ft_strjoin(new0, g_shell.var_env);
	new2 = ft_strjoin(new1, tab[1]);
	free(g_shell.var_env);
	free(tab[0]);
	free(tab[1]);
	free(new0);
	free(new1);
	return (new2);
}

char	*remove_empty_var(char *line)
{
	char	*new;
	char	**split_dol;
	int		l;
	int		c;
	char	*tab[3];

	l = 0;
	tab[0] = ft_strdup("");
	split_dol = ft_split(line, ' ');
	while (split_dol[l])
	{
		c = 0;
		while ((split_dol[l][c] != '$' ||
			!ft_alphanum(split_dol[l][c + 1])) && split_dol[l][c])
			c++;
		tab[1] = ft_substr(split_dol[l], 0, c);
		tab[2] = ft_strjoin(tab[0], tab[1]);
		free(tab[0]);
		tab[0] = ft_strjoin(tab[2], " ");
		free(tab[1]);
		free(tab[2]);
		l++;
	}
	free(line);
	return (tab[0]);
}

char	*var_env2(char *line, int j, char **to_find, char ***vars_env)
{
	char *new_line;

	if (!ft_strncmp((line + j), *to_find, ft_strlen(*to_find)))
	{
		ft_cpy_var(vars_env[0][1]);
		new_line = replace_env(*to_find, line, j, j + ft_strlen(*to_find));
		line = ft_strdup(new_line);
	}
	return (line);
}

char	*var_env(char *line)
{
	int		i;
	char	**vars_env;
	char	*to_find;
	char	*dol;
	int		j;

	i = -1;
	while (g_shell.envp[++i])
	{
		dol = dol_create();
		vars_env = ft_split(g_shell.envp[i], '=');
		to_find = ft_strjoin(dol, vars_env[0]);
		free(dol);
		j = -1;
		while (line[++j])
			line = var_env2(line, j, &to_find, &vars_env);
		free(to_find);
		free(vars_env);
	}
	line = remove_empty_var(line);
	return (line);
}
