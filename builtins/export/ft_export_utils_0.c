#include "../../minishell.h"

/*
** Cette fonction est appelée au moment ou une variable correspond a une variable existante,
** dans le tableau d'environnement.
** Dans le cas ou elle est appelé par la fonction ft_export, elle permet de remplacer la variable 
** concernée par la nouvelle variable exportée.
** Dans le cas ou elle est appelé par la fonction ft_unset, elle supprime la variable sans la remplacer.
*/

//.............................
void		is_match(t_cmds cmds, int *i, int *x, int export)
{
	free(g_shell.envp[*i]);
	// ft_swap(g_shell.envp[*i], g_shell.envp[*i + 1]);
	// g_shell.envp[*i] = NULL;


	if (export)
	{
		g_shell.envp[*i] = NULL;
		if (!(g_shell.envp[*i] = ft_strdup(cmds.argv[*x])))
			return ;
		cmds.argv[*x] = NULL;
	}
}

/*
** Cette fonction permet de détecter si le nom de la variable exportée contient une erreur ou non.
** Elle vérigie la première lettre de la variable exportée.
** Elle est appelée dans la fonction check_error_export, fichier ft_export_utils_1.c.
*/

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	else
		return (0);
}

/*
** Cette fonction permet de détecter si le nom de la variable exportée contient une erreur ou non.
** Elle permet également de savoir si lors de l'export, une valeur lui est attribuée ou non.
** Elle est appelée dans la fonction check_error_export, fichier ft_export_utils_1.c.
*/

int		is_alnum(t_cmds cmds, int i, int export)
{
	int 	k;
	int 	c;

	k = 0;
	while (cmds.argv[i][k])
	{
		c = cmds.argv[i][k];
		if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z') || c == '_' || (c == '=' && export)))
			return (0);
		if (c == '=' && export)
			return (1);
		k++;
	}
	return (1);
}

/*
** Cette fonction permet de trier le tableau lors de l'appel de la commande "export" sans argument.
** Elle est appelé dans la fonction sort_env, fichier ft_export_utils_1.c.
*/

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

/*
** Cette fonction affiche le nom ou la valeur de la variable d'environnement. (Avant ou après le signe '=').
** Elle est utilisée dans le cas de l'appel de la commande "export" sans argument.
** Elle est appelée dans la fonction draw_env, fichier ft_export_utils_1.c.
*/

void	put_env(char *s, int fd, int len)
{
	if (!s)
		return ;
	write(fd, s, len);
}