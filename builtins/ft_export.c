#include "../../minishell.h"

// UTILS
int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	else
		return (0);
}

int		is_alnum(t_cmds cmds, int i)
{
	int 	k;
	int 	c;

	k = 0;
	while (cmds.argv[i][k])
	{
		c = cmds.argv[i][k];
		if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z') || c == '_' || c == '='))
			return (0);
		if (c == '=')
			return (1);
		k++;
	}
	return (1);
}

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

void	put_env(char *s, int fd, int len)
{
	if (!s)
		return ;
	write(fd, s, len);
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

//FONCTIONS PRINCIPALES EXPORT
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
