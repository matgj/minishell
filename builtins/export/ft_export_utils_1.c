#include "../../minishell.h"

/*
** Cette fonction est appelée au moment ou une variable correspond a une variable existante,
** dans le tableau d'environnement.
** Dans le cas ou elle est appelé par la fonction ft_export, elle permet de remplacer la variable 
** concernée par la nouvelle variable exportée.
** Dans le cas ou elle est appelé par la fonction ft_unset, elle supprime la variable sans la remplacer.
*/

void			is_match(t_cmds cmds, int *i, int *x, int export)
{
	int 		envp;
	int			argv;

	if (export)
	{
		envp = before_egal(g_shell.envp[*i], 1);
		argv = before_egal(cmds.argv[*x], 1);
		if ((envp && argv) || (!envp && argv))
		{
			free(g_shell.envp[*i]);
			g_shell.envp[*i] = NULL;
			if (!(g_shell.envp[*i] = ft_strdup(cmds.argv[*x])))
				return ;
			cmds.argv[*x] = NULL;
		}
	}
}

/*
**	Cette fonction vérifie si la variable exportée existe déjà dans le tableau d'environnement. 
** 	Si elle trouve une correspondance, elle free la valeur correspondante dans le tableau existant 
**	pour ensuite mettre la nouvelle valeur. La variable flag est décrémentée puis mise à NULL
** 	car elle ne sera pas comptabilisée comme variable a rajouter/enlever au tableau.
*/

void 			is_exist(t_cmds cmds, int *flag, int export)
{
	int 		i;
	int 		j;
	int 		x;
	int 		count;

	(!export) ? count = *flag : 0;
	i = 0;
	while (g_shell.envp[i])
	{
		j = before_egal(g_shell.envp[i], 0);
		x = 1;
		while (x < cmds.argc)
		{
			if (cmds.argv[x] && !ft_strncmp(g_shell.envp[i], cmds.argv[x], j))
			{
				is_match(cmds, &i, &x, export);
				(export) ? *flag -= 1 : count--;
			}
			x++;
		}
		i++;
	}
	(!export) ? *flag -= count : 0;
}

/*
**	Cette fonction compte le nombre de caractères avant ou après le signe '=' 
**	Si on lui envoit en paramètre la lettre 'a' pour "after" elle comptera les caractères
**	du nom de la variable.
**	Si on lui envoit en paramètre la lettre 'b' pour "before" elle comptera les caractères
**	de la valeur de la variable.
*/

int 			before_after_egal(char *env, int j, int where, int *empty)
{
	int 		k;

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

/*
**	Cette fonction récupère le tableau d'environnement trié au préalable par la fonction sort_env
**  et a pour but d'appliquer la mise en forme après avoir utilisé la commande "export" sans argument.
**	Avant chaque nom de variable elle affiche "declare -x".
**	Elle vérifie si la valeur de la variable est existante ou nulle.
**	Si nulle : pas de signe "=" à afficher et pas de double quotes entourant la valeur de la variable.
**	Si existante : affichage de la valeur de la variable entre double quotes.
*/

void			draw_env(char **env)
{
	int			i;
	int 		j;
	int 		len;
	int 		empty;

	i = 1;
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

/*
**	Cette fonction récupère le tableau d'environnement et le trie.
*/

void			sort_env(t_cmds cmds)
{
	char		**tmp;
	int			i;
	int			j;

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
	// mfree(tmp);
}
