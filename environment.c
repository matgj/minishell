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


// char	*get_next_path(char **env, char *command)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	while ((*env)[i] && (*env)[i] != '\n' && (*env)[i] != ':')
// 	{
// 		printf("env[%i]:%c\n",i,(*env)[i]);
// 		i++;
// 	}
// 	if(!(path = (char *)malloc(sizeof(char) * (i + ft_strlen(command) + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (**env && **env != '\n' && **env != ':')
// 		path[i++] = *((*env)++);
// 	if (**env == ':')
// 		(*env)++;
// 	path[i++] = '/';
// 	while (command && *command)
// 		path[i++] = *command++;
// 	path[i] = '\0';
// 	//printf("path:[%s]\n", path);
// 	return (path);
// }

// int		check_stat(char *path, int *err, int direct)
// {
// 	int			ret;
// 	struct stat	buf;

// 	ret = stat(path, &buf);
// 	if (ret < 0) // the file doesn't exist - w different exit status depending on direct path or not
// 		*err = 127 + direct;
// 	else if (!(buf.st_mode & S_IXUSR)) // not an executable, permission denied
// 		*err = 126;
// 	else if (S_ISDIR(buf.st_mode)) // is a Directory
// 		*err = 125;
// 	else if (!(*err = 0))
// 		return (1);
// 	return (0);
// }

 char    *command_path(t_cmds *cmds)
 {
//   int err;
// 	err = 0;
// 	test_env(cmds);
//     while (g_shell.envp && *g_shell.envp && (cmds->path = get_next_path(g_shell.envp, cmds->name)))
// {
// 		test_path(cmds);
// 		if (check_stat(cmds->path, &err, 1))
// 			return (cmds->path);
// 	//	printf("stat error:[%i]\n", err);
// 		free((void **)cmds->path);
// }
  return ("soon jaurai la path ici frero");
}