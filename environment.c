/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:52:16 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/24 10:52:17 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell g_shell;

//copy dans un tab 2d toutes les variables d'environnement

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

int		check_stat(char *path, int *err, int direct)
{
	int			ret;
	struct stat	buf;

	ret = stat(path, &buf);
	if (ret < 0) // the file doesn't exist - w different exit status depending on direct path or not
		*err = 127 + direct;
	else if (!(buf.st_mode & S_IXUSR)) // not an executable, permission denied
		*err = 126;
	else if (S_ISDIR(buf.st_mode)) // is a Directory
		*err = 125;
	else if (!(*err = 0))
		return (1);
	return (0);
}

 char    *command_path(t_cmds *cmds)
 {
	// test_env(cmds);
  return (NULL);
}