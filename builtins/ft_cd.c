#include "../minishell.h"

void	no_dir_file(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("\n", 2);
	g_shell.status = 1;
}

static void		dup_strs(char **dst, char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(str1, str2);
	*dst = ft_strdup(tmp);
	free(tmp);
}

/*
** Permet de recréer une copie du tableau d'environnement tout en
** modifiant seulement le $PWD et le $OLDPWD.
*/

void	renew_paths(t_cmds cmds, char *oldpwd)
{
	char	**new_env;
	char	pwd[256];
	int		i;

	i = 0;
	if (!(new_env = (char **)ft_calloc(g_shell.env_len + 1, sizeof(char *))))
		return ;
	new_env[g_shell.env_len] = NULL;
	while (g_shell.envp[i])
	{
		if (!ft_strncmp("OLDPWD", g_shell.envp[i], 6))
			dup_strs(&new_env[i], "OLDPWD=", oldpwd);
		else if (!ft_strncmp("PWD", g_shell.envp[i], 3))
		{
			getcwd(pwd, 256);
			dup_strs(&new_env[i], "PWD=", pwd);
		}
		else
			new_env[i] = ft_strdup(g_shell.envp[i]);
		i++;
	}
	// free(g_shell.envp);     penser a free ici
	g_shell.envp = new_env;
}

int		ft_cd(t_cmds cmds)
{
	int		ret;
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = var_env("$PWD");
	cmds.path = var_env("$HOME");
	(!cmds.argv[1] || cmds.argv[1][0] == '~') ? chdir(cmds.path) : 0;
	if (cmds.argv[1] && cmds.argv[1][0] != '~')
	{
		if ((ret = chdir(cmds.argv[1])) == -1)
		{
			ft_putstr_fd("bash: cd: ", 1);
			no_dir_file(cmds.argv[1]);
			return (0);
		}
	}
	printf("1oldpath = [%s]\n", oldpwd);
	renew_paths(cmds, oldpwd);
	g_shell.status = 0;
	return (1);
}