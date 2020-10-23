#include "../minishell.h"

/*
**	Cette fonction parcours le tableau d'arguments et vérifie qu'il n'y a pas d'erreur
*/

int 		check_error_unset(t_cmds cmds, int *flag)
{
	int 	i;

	i = 1;
	while (cmds.argv[i])
	{
		if ((!ft_isalpha(cmds.argv[i][0]) || !is_alnum(cmds, i, 0))
			&& is_error(&cmds.argv[i], flag, 0))
			return (0);
		i++;
	}
	return ((!(*flag)) ? 0 : 1);
}

/*
**	Cette fonction parcours le tableau d'arguments et compare chaque argument
** 	avec la variable en cours dans le tableau d'environnement existant.
** 	Si elle trouve une correspondance, elle renvoit une valeur au dessus de 0
** 	Sinon elle renvoit 0.
*/

int 	is_exist_unset(t_cmds cmds, int *i)
{
	int 	j;
	int 	x;
	int 	len;
	x = 1;
	len = 0;
	while (x < cmds.argc)
	{
		if (cmds.argv[x])
		{
			j = ft_strlen(cmds.argv[x]);
			if (!ft_strncmp(g_shell.envp[*i], cmds.argv[x], j))
			{
				cmds.argv[x] = NULL;
				return (x);
			}
		}
		x++;
	}
	return(0);
}

/*
**	Cette fonction malloc le nouveau tableau d'environnement de la taille du
**  tableau actuel moins les variables a supprimer via la commande unset.
** 	Elle parcours chaque variable du tableau d'environnement existant
** 	Elle appelle is_exist_unset pour vérifier si la variable en cours est égale
** 	a l'argument indiqué via la commande unset. 
**  Si oui, on ne la recopie pas dans le nouveau tableau, et on passe à la suivante.
**  Si non, la variable n'est donc pas a effacé et on peut la recopier dans le nouveau tableau.
** 	On passe ensuite à la suivante.
*/

char		**delete_env(t_cmds cmds, int *flag)
{
	char	**tmp;
	int		i;
	int 	is_same;
	int 	k;

	g_shell.env_len -= (*flag);
	if (!(tmp = (char **)ft_calloc((g_shell.env_len + 1), sizeof(char *))))
		return (NULL);
	k = 0;
	i = 0;
	while (g_shell.envp[i])
	{	
		is_same = is_exist_unset(cmds, &i);
		if (!is_same)
		{
			tmp[k] = ft_strdup(g_shell.envp[i]);
			k++;
		}
		i++;
	}
	tmp[k] = NULL;
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
			free_split(g_shell.envp);
			g_shell.envp = tmp;
		}
	}
	return (1);
}
