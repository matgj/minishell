#include "../minishell.h"

int		ft_env(t_cmds cmds)
{
	int 	i;

	i = 0;
	while (g_shell.envp[i])
	{
		ft_putendl_fd(g_shell.envp[i], 1);
		i++;
	}
	g_shell.status = 0;
	return (1);
}



/*
** export sans argument : affiche env trié par ordre alphabétique avec delcare-x 
** export tata sans donner de valeur -> si apres j'ecris tata=66 -> 





Export > 
			No argument :
							- Trier le tableau 
							- Marquer declare -x : avant chaque variable
							- Mettre "" pour encadrer la valeur de la variable
							- Print env

			Argument 	:
							- Verifier arguments 
								. Si faux > afficher message erreur, supprimer du tableau d'arg et -1;
								. Si bon > 0

							- Verifier si existe deja
								. Si existant >
									Si sans valeur : mettre la nouvelle valeur et -1
									Si valeur : remplacer par la nouvelle et -1

*/