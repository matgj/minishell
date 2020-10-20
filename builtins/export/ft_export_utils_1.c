#include "../../minishell.h"

void 	what_to_compare(int *l, int *j, int *i, int *x)
{
		*l = 0;
		*j = 0;
		while (g_shell.envp[*i][*l])
		{
			if (g_shell.envp[*i][*l] != '=')
				(*j)++;
			if (g_shell.envp[*i][*l] == '=')
				break ;
			(*l)++;
		}
		(g_shell.envp[*i][*l] != '=') ? *j = *l : 0;
		*x = 1;
}

void 	is_exist(t_cmds cmds, int *flag)
{
	int 	i;
	int 	j;
	int 	x;
	int 	l;

	i = 0;
	while (g_shell.envp[i])
	{
		what_to_compare(&l, &j, &i, &x);
		while (x < cmds.argc)
		{
			if (cmds.argv[x])
			{
				if (!ft_strncmp(g_shell.envp[i], cmds.argv[x], j))
				{
					free(g_shell.envp[i]);
					g_shell.envp[i] = ft_strdup(cmds.argv[x]);
					*flag -= 1;
					cmds.argv[x] = NULL;
				}
			}
			x++;
		}
		i++;
	}
}

int 	before_after_egal(char *env, int j, int where, int *empty)
{
	int k;

	if (where == 'a')
	{
		while (env[j])
		{
			if (env[j] == '=')
			{
				*empty = 0;
				return (j);
			}
			j++;
			(*empty)++;
		}
		return (j);
	}
	else
	{
		k = j;
		while (env[j])
			j++;
	}
	return (j - k);
}

void		draw_env(char **env)
{
	int		i;
	int 	j;
	int 	len;
	int 	empty;

	i = 0;
	j = 0;
	while (env[i])
	{
		empty = 0;
		ft_putstr_fd("declare -x ", 1);
		j = before_after_egal(env[i], 0, 'a', &empty);
		put_env(env[i], 1, j);
		(empty) ? write(1, "\n", 1) : 0;
		if (!empty)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			len = j + 1;
			j = before_after_egal(env[i], j, 'b', &empty);
			put_env(env[i] + len, 1, j);
			ft_putstr_fd("\"\n", 1);
		}
		i++;
	}
}

void		sort_env(t_cmds cmds)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	tmp = g_shell.envp;
	while (tmp[i++])
	{
		j = i + 1;
		while (tmp[j++])
			if ((ft_strncmp(tmp[i], tmp[j], ft_strlen(tmp[j]))) > 0)
				ft_swap(&tmp[i], &tmp[j]);
	}
	draw_env(tmp);
	// free_strings(tmp);
}