/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:54:18 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/01 10:24:07 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

//je remplace les doubles quotes par un caractere ascii neutre
// et lorsque je traiterai ma commande
//je remplacerai mon caractere par un espace  

void    double_quotes(char *c, int *q, int *dq)
{
    g_shell.dquotes = 1;
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

//il laisse un $ devant ma var, changer par quoi je remplace quand jai un dollar?

char    *replace_env(char *to_find, char *line, int start, int end)
{
    char *new0;
    char *new1;
    char *new2;
    char *tab[3];
    
    tab[0] = ft_substr(line, 0, start);
  //  printf("tab[0]:%s\n", tab[0]);
    tab[1] = ft_substr(line, end, ft_strlen(line) - end);
  //  printf("tab[1]:%s\n", tab[1]);
  //  tab[2] = ft_strjoin("  ", tab[1]);
  //  printf("tab[2]:%s\n", tab[2]);
    new0 = ft_strdup(tab[0]);
 //   printf("new0:%s\n", new0);
   // printf("%s\n", g_shell.var_env);
    new1 = ft_strjoin(new0, g_shell.var_env);
   /// printf("new1:%s\n", new1);
    new2 = ft_strjoin(new1, tab[1]);
   // printf("new2%s\n", new2);
    free(g_shell.var_env);
    free(tab[0]);
    free(tab[1]);
    //free(tab[2]);
    free(new0);
 //   new0 =  ft_strjoin(new2, "    ");
   // printf("new0%s\n", new0);
    free(new1);
    return (new2);
}

int		ft_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c < 'Z'));
}

void    ft_cpy_var(char *str)
{
    int i;

    i = 0;
    g_shell.var_env = ft_strdup(str);
}

// char *env_dquotes(char *line)
// {
//     split_dol = ft_split(line, ' ');
//         while (split_dol[l])
//         {
//             c = 0;
//             while ((split_dol[l][c] != '$' || !ft_alphanum(split_dol[l][c + 1])) && split_dol[l][c])
//                 c++;
//             tab[1] = ft_substr(split_dol[l], 0, c);
//             printf("---------tab[1] : %s\n", tab[1]);//
//             tab[2] = ft_strjoin(tab[0], tab[1]);
//             printf("---------tab[2] : %s\n", tab[2]);//
//             free(tab[0]);
//             tab[0] = ft_strjoin(tab[2], " ");
//             printf("---------tab[0] : %s\n", tab[0]);//
//             free(tab[1]);
//             free(tab[2]);
//                 //je retire le bail
//             l++;
// }

//TODO:si mode guillemets "" active le split doit prendre en compte la premiere var"

char *remove_empty_var(char *line)
{
    char *new;
    char **split_dol;
    int l;
    int c;
    char *tab[3];
    
    l = 0;
    tab[0] = ft_strdup("");
        split_dol = ft_split(line, ' ');
        while (split_dol[l])
        {
            c = 0;
            while ((split_dol[l][c] != '$' || !ft_alphanum(split_dol[l][c + 1])) && split_dol[l][c])
                c++;
            tab[1] = ft_substr(split_dol[l], 0, c);
            // printf("---------tab[1] : %s\n", tab[1]);//
            tab[2] = ft_strjoin(tab[0], tab[1]);
            // printf("---------tab[2] : %s\n", tab[2]);//
            free(tab[0]);
            tab[0] = ft_strjoin(tab[2], " ");
            // printf("---------tab[0] : %s\n", tab[0]);//
            free(tab[1]);
            free(tab[2]);
                //je retire le bail
            l++;
        // }
    }
    free(line);
    return (tab[0]);
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
    line = remove_empty_var(line); //supprimers les cases contenant des var denv vides
   //  printf("---------line : %s\n", line);//
    return (line);
}