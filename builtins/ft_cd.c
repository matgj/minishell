#include "../minishell.h"

void	no_dir_file(char *str)
{
	// errno = 2;
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	// ft_putstr_fd(strerror(errno), 2);
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
		{
			dup_strs(&new_env[i], "OLDPWD=", oldpwd);
			printf("new_env[i] OLDPWD = [%s]\n", new_env[i]);
		}
		else if (!ft_strncmp("PWD", g_shell.envp[i], 3))
		{
			getcwd(pwd, 256);
			dup_strs(&new_env[i], "PWD=", pwd);
			printf("new_env[i] PWD = [%s]\n", new_env[i]);
		}
		else
			new_env[i] = ft_strdup(g_shell.envp[i]);
		i++;
	}
	// free_strings(g_shell.envp);
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
	// printf("[0] = [%s]\n", cmds.argv[0]);
	// printf("[1] = [%s]\n", cmds.argv[1]);
	// printf("1path = [%s]\n", cmds.path);
	printf("1oldpath = [%s]\n", oldpwd);
	// printf("1env_len = [%d]\n\n", g_shell.env_len);
	renew_paths(cmds, oldpwd);
	// printf("path = [%s]\n", cmds.path);
	printf("oldpath = [%s]\n", oldpwd);
	// printf("env_len = [%d]\n", g_shell.env_len);
	g_shell.status = 0;
	return (1);
}