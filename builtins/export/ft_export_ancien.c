#include "../../minishell.h"

/*
** Cette fonction affiche le nom et le message d'erreur dans le cas ou la variable exportée n'est pas correcte.
** Chaque variable fausse décrémente la variable flag qui servira pour la taille du malloc du nouveau tableau.
** Elle est appelée dans la fonction check_error_export.
*/

int 			is_error(char **str, int *flag, int export)
{
	ft_putstr_fd("bash: ", 2);
	(export) ? ft_putstr_fd("export: \'", 2) : ft_putstr_fd("unset: \'", 2);
	ft_putstr_fd(*str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	env_status(1);
	*flag -= 1;
	(export) ? *str = NULL : 0;
	return (0);
}

/*
** Cette fonction permet de récuperer le nombre de caractères á récuperer
** avant le signe '=' (s'il existe).
*/

int 			before_egal(char *argv, int egal)
{
	int 		i;
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			return ((!egal) ? i : 1);
		i++;
	}
	return ((!egal) ? i : 0);
}

/*
** Cette fonction permet de détecter les doublons d'arguments et de les supprimer.
** Elle permet également d'assigner la derniere valeur en cas d'export de la meme
** variable avec des valeurs differentes.
*/

void 			same_it_is(t_cmds cmds, int *flag)
{
	int 		i;
	int 		k;
	int 		len;
	int 		is_egal;

	i = 1;
	is_egal = 0;
	while (cmds.argv[i])
	{
		k = i + 1;
		while (cmds.argv[k])
		{
			len = before_egal(cmds.argv[i], 0);
			if (!ft_strncmp(cmds.argv[i], cmds.argv[k], len))
			{
				cmds.argv[i] = NULL;
				*flag -= 1;
				break ;
			}
			k++;
		}
		i++;
	}
}

/*
** Cette fonction vérifie que les variables exportées ne contiennent pas d'erreur.
** Première lettre doit obligatoirement être un tiret du bas "_" ou une lettre alphabétique majuscule ou minuscule.
** Aucun autre type de caractères dans le nom de la variable autres que lettre alphabétique ou tiret du bas "_".
** Si la/les variable(s) exportée(s) ne contienne(nt) aucune erreur, elle appelle la fonction is_exist pour
** vérifier si elle(s) existe(nt) déjà dans le tableau d'environnement.
** Elle retourne ensuite le nombre exacte de variables à ajouter au tableau existant.
** Elle est appelée dans la fonction ft_export.
*/

int				check_error_export(t_cmds cmds, int *flag)
{
	int 		i;

	i = 1;
	same_it_is(cmds, flag);
	while (!cmds.argv[i])
		i++;
	while (cmds.argv[i])
	{
		(!cmds.argv[i]) ? i++ : 0;
		if ((!ft_isalpha(cmds.argv[i][0]) || !is_alnum(cmds, i, 1))
			&& is_error(&cmds.argv[i], flag, 1))
			return (0);
		i++;
	}
	is_exist(cmds, flag, 1);
	return ((!(*flag)) ? 0 : 1);
}

/*
** Cette fonction malloc le nouveau tableau d'environnement avec la taille nécessaire à l'ajout des nouvelles
** variables exportées. Elle ajoute ensuite les variables existantes puis les nouvelles.
** Elle est appelée dans la fonction ft_export.
*/

char			**add_env(t_cmds cmds, int *flag)
{
	char		**tmp;
	int			i;
	int 		k;

	g_shell.env_len += (*flag);
	if (!(tmp = (char **)ft_calloc((g_shell.env_len),
				sizeof(char *))))
		return (NULL);
	i = 0;
	while (g_shell.envp[i])
	{
		if (!(tmp[i] = ft_strdup(g_shell.envp[i])))
			return (NULL);
		i++;
	}
	k = 1;
	while (k < cmds.argc)
	{
		if (!cmds.argv[k])
			k++;
		else if (!(tmp[i++] = ft_strdup(cmds.argv[k++])))
			return (NULL);
	}
	tmp[i] = NULL;
	return (tmp);
}

/*
** Cette fonction à pour but d'afficher le tableau d'environnement, d'y ajouter des variables, avec ou sans valeurs
** et de les trier.
*/

int				ft_export_ancien(t_cmds cmds)
{
	char		**tmp;
	int 		flag;

	flag = cmds.argc - 1;
	if (!cmds.argv[1])
		sort_env(cmds);
	else if (check_error_export(cmds, &flag))
	{
		if (!(tmp = add_env(cmds, &flag)))
			return (0);
		else
		{
			mfree(g_shell.envp);
			g_shell.envp = tmp;
		}
	}
	return (1);
}
