/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:54:18 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/27 17:46:16 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

//je remplace les doubles quotes par un caractere ascii neutre
// et lorsque je traiterai ma commande
//je remplacerai mon caractere par un espace  

void    double_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq) //ouverture des doubles quotes
    {
        *dq = 1;
        *c = REPLACED;
    }
    else if (!*q && *dq)         //fermetures des doubles quotes
    {
        *dq = 0;
        *c = REPLACED;
    }
}

void    simple_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq) //ouverture des simples quotes
    {
        *q = 1;
        *c = REPLACED;
    }
    else if (*q && !*dq) //fermetures des simples quotes
    {
        *q = 0;
        *c = REPLACED;
    }
}

char    *replace_env(char *to_find, char *line, int start, int end)
{
    char *new0;
    char *new1;
    char *new2;
    char *tab[2];
    
    tab[0] = ft_substr(line, 0, start);
    printf("tab[0]:%s\n", tab[0]);
    tab[1] = ft_substr(line, end, ft_strlen(line) - end);
    printf("tab[1]:%s\n", tab[0]);
    new0 = ft_strdup(tab[0]);
    new1 = ft_strjoin(new0, g_shell.var_env);
    new2 = ft_strjoin(new1, tab[1]);
    free(g_shell.var_env);
    free(tab[0]);
    free(tab[1]);
    free(new0);
    free(new1);
    return (new2);
}


void    ft_cpy_var(char *str)
{
    int i;

    i = 0;
    g_shell.var_env = ft_strdup(str);
}

//recuperer la var d env
//comparer avec la var que jai dans line
//si ca existe je remplace par le contenu de la var
// sinon je remplace par du blanc
char    *var_env(char *line)
{
   int i;
   char **vars_env; //va contenir le nom des var_denv
   char *to_find;
   char *dol;
   int j;
   char *new_line;
   char *new_var;
   
   i = 0;
   while (g_shell.envp[i]) //je parcours les lignes du tab
   {
        if(!(dol = (char*)malloc(sizeof(char)*2)))
            return (NULL);
        dol[0] = '$';
        dol[1] = '\0';
        vars_env = ft_split(g_shell.envp[i], '=');
        to_find = ft_strjoin(dol, vars_env[0]);
        free(dol);
        j = 0;
        while (line[j])
        {
            if(!ft_strncmp((line + j), to_find, ft_strlen(to_find)))
            {
              ft_cpy_var(vars_env[1]);
              new_line = replace_env(to_find, line, j, j + ft_strlen(to_find));
                line = ft_strdup(new_line);
            //  printf("---------new_line : %s\n", new_line);//
            }
            j++;
        }
        i++;
        free(to_find);
        free(vars_env);
   }
return (line);
 // printf("---------line : %s\n", new_line);//
}