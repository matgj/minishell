/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:54:18 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 16:27:55 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

void    double_quotes(char *c, int *q, int *dq)
{
    g_shell.dquotes = 1;
    if (!*q && !*dq)
    {
        *dq = 1;
        *c = REPLACED;
    }
    else if (!*q && *dq)
    {
        *dq = 0;
        *c = REPLACED;
    }
}

void    simple_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq)
    {
        *q = 1;
        *c = REPLACED;
    }
    else if (*q && !*dq)
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
    char *tab[3];
    
    tab[0] = ft_substr(line, 0, start);
    tab[1] = ft_substr(line, end, ft_strlen(line) - end);
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
            tab[2] = ft_strjoin(tab[0], tab[1]);
            free(tab[0]);
            tab[0] = ft_strjoin(tab[2], " ");
            free(tab[1]);
            free(tab[2]);
            l++;
         }
         free(line);
        return (tab[0]);
}

char    *var_env(char *line)
{
   int i;
   char **vars_env;
   char *to_find;
   char *dol;
   int j;
   char *new_line;
   char *new_var;
   
   i = 0;
   while (g_shell.envp[i])
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
            }
            j++;
        }
        i++;
        free(to_find);
        free(vars_env);
   }
    line = remove_empty_var(line); //supprimers les cases contenant des var denv vides
    return (line);
}