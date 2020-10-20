#include "../../minishell.h"

int 	is_error(char **str, int *flag)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(*str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_shell.status = 1;
	*flag -= 1;
	*str = NULL;
	return (0);
}

int		check_error_export(t_cmds cmds, int *flag)
{
	int 	i;
	int 	k;

	i = 1;
	while (cmds.argv[i])
	{
		if ((!ft_isalpha(cmds.argv[i][0]) || !is_alnum(cmds, i))
			&& is_error(&cmds.argv[i], flag))
			return (0);
		else if (cmds.argv[i])
			is_exist(cmds, flag);
		i++;
	}
	return ((!(*flag)) ? 0 : 1);
}

char		**add_env(t_cmds cmds, int *flag)
{
	char	**tmp;
	int		i;
	int 	k;

	g_shell.env_len += (*flag);
	if (!(tmp = (char **)ft_calloc((g_shell.env_len + 1),
				sizeof(char *))))
		return (NULL);
	i = 0;
	while (g_shell.envp[i])
	{
		tmp[i] = ft_strdup(g_shell.envp[i]);
		i++;
	}
	k = 1;
	while (k < cmds.argc)
	{
		if (!cmds.argv[k])
			k++;
		tmp[i] = ft_strdup(cmds.argv[k]);
		i++;
		k++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int		ft_export(t_cmds cmds)
{
	char	**tmp;
	int 	flag;

	flag = 0;
	flag = cmds.argc - 1;


	if (!cmds.argv[1])
		sort_env(cmds);
	else if (check_error_export(cmds, &flag))
	{
		if (!(tmp = add_env(cmds, &flag)))
			return (0);
		else
		{
			free_split(g_shell.envp);
			g_shell.envp = tmp;

		}
	}
	return (1);
}
