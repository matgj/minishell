#include "../../minishell.h"

/*
**	Cette fonction permet de calculer le nombre de caractères avant le signe '=' de chaque variable
** 	dans le tableau d'environnement existant. Ce qui servira à comparer les noms des variables exportées 
** 	des noms des variables existantes.
** 	Si la variable existe dans le tableau d'environnement mais qu'elle ne posséde aucune valeur, il n'y 
** 	a donc pas de signe '='. La fonction renvoit alors le nombre total de caractères, qui correspondent donc
** 	au nom entier de la variable.
*/

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

/*
**	Cette fonction vérifie si la variable exportée existe déjà dans le tableau d'environnement. 
** 	Si elle trouve une correspondance, elle free la valeur correspondante dans le tableau existant 
**	pour ensuite mettre la nouvelle valeur. La variable flag est décrémentée puis mise à NULL
** 	car elle ne sera pas comptabilisée comme variable a rajouter au tableau.
*/

void 	is_exist(t_cmds cmds, int *flag, int export)
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

					is_match(cmds, &i, &x, export);
					(export) ? *flag -= 1 : 0;
				}
			}
			x++;
		}
		i++;
	}
}

/*
**	Cette fonction compte le nombre de caractères avant ou après le signe '=' 
**	Si on lui envoit en paramètre la lettre 'a' pour "after" elle comptera les caractères
**	du nom de la variable.
**	Si on lui envoit en paramètre la lettre 'b' pour "before" elle comptera les caractères
**	de la valeur de la variable.
*/

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

/*
**	Cette fonction récupère le tableau d'environnement trié au préalable par la fonction sort_env
**  et a pour but d'appliquer la mise en forme après avoir utilisé la commande "export" sans argument.
**	Avant chaque nom de variable elle affiche "declare -x".
**	Elle vérifie si la valeur de la variable est existante ou nulle.
**	Si nulle : pas de signe "=" à afficher et pas de double quotes entourant la valeur de la variable.
**	Si existante : affichage de la valeur de la variable entre double quotes.
*/

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

/*
**	Cette fonction récupère le tableau d'environnement et le trie.
*/

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
	// i = 0;
	// while (tmp[i++])
	// 	printf("tmp[%d] = %s\n", i, tmp[i]);
	// printf("\n\n");
	draw_env(tmp);
	// free_strings(tmp);
}