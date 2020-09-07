#include "minishell.h"

//copy dans un tab 2d toutes les variables d'environnement

char	**env_import(char **envp)
{
	char 	**tab;
	int 	i;

	i = 0;
	while((envp[i]) != NULL)
		i++;
	if(!(tab = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	i = 0;
	while ((envp[i] != NULL))
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}