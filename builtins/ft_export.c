#include "../minishell.h"

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
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
	i = 0;
	while (tmp[i])
		ft_putendl_fd(tmp[i++], 1);
	free_split(tmp);
}

int		ft_export(t_cmds cmds)
{
	// char	**tmp;

	// add_env(cmds);
	(!cmds.argv[1]) ? sort_env(cmds) : 0;


	// printf("var_env = [%s]\n", g_shell.var_env);
	// printf("argv[0] = [%s]\n", cmds.argv[0]);
	// printf("argv[1] = [%s]\n", cmds.argv[1]);
	// printf("argv[2] = [%s]\n", cmds.argv[2]);
	// printf("argc = [%d]\n", cmds.argc);
	g_shell.status = 0;
	return (1);
}






/*
** export sans argument : affiche env trié par ordre alphabétique
** export 
*/