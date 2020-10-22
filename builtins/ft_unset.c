#include "../minishell.h"

int 		check_error_unset(t_cmds cmds, int *flag)
{
	int 	i;

	i = 1;
	while (cmds.argv[i])
	{
		if ((!ft_isalpha(cmds.argv[i][0]) || !is_alnum(cmds, i, 0))
			&& is_error(&cmds.argv[i], flag, 0))
			return (0);
		else if (cmds.argv[i])
			is_exist(cmds, flag, 0);
		i++;
	}
	return ((!(*flag)) ? 0 : 1);
}

//....................
// 
char		**delete_env(t_cmds cmds, int *flag)
{
	char	**tmp;
	int		i;
	int 	k;

	g_shell.env_len -= (*flag);
	if (!(tmp = (char **)ft_calloc((g_shell.env_len),
				sizeof(char *))))
		return (NULL);
	i = 0;
	while (g_shell.envp[i])
	{
		if (!(tmp[i] = ft_strdup(g_shell.envp[i])))
			return (NULL);
		// printf("envp[%d][%s]\n", i, g_shell.envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int			ft_unset(t_cmds cmds)
{
	char	**tmp;
	int 	flag;
	
	flag = cmds.argc - 1;
	if (!cmds.argv[1])
		return (1);
	else if (check_error_unset(cmds, &flag))
	{
		if (!(tmp = delete_env(cmds, &flag)))
			return (0);
		else
		{
			// free_split(g_shell.envp);
			g_shell.envp = tmp;
		}
	}
	return (1);
}
