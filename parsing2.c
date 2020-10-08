/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:50:01 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 12:56:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

//quel type de chevron on a ? pour savoir comment rediriger le resultat des commandes 
// >  0 redirec the output --stdin (0) (overwrite le fichier)
// <  1 redicec the input --stout (1);
// >> 2 redic the ouput stind with append (s'ajoute au fichier);
//pas de chevron = 3

void     which_chevron(t_cmds *cmds, char *argv) 
{
     if (!ft_strcmp(argv, ">"))
             cmds->chevron = 0;
     else if (!ft_strcmp(argv, "<"))
             cmds->chevron = 1;
     else if (!ft_strcmp(argv, ">>"))        
             cmds->chevron = 2;
     else
        cmds->chevron = 3;
}


//le resultat (output) de ma commande doit etre redirigee vers un fichier plutot que stout 
//(exemple wc -l doc.c > hello.txt cree le fichier hello et y ecrit le nombre de ligne de doc.c)
// le double chevron cest pareil mais ca s ajoute au contenu du fichier hello.txt si ca existe deja
//je cree donc un nouveau FD

void    redirec_output(t_cmds *cmds, char *argv)
{
    int fd;

    g_shell.redir = g_shell.redir + 1;
    if (cmds->chevron == 0)
    {
        if ((fd = open(argv, O_TRUNC | O_RDWR | O_CREAT, 0644)) < 0) //Using 0644 will create a file that is Read/Write for owner, and Read Only for everyone
            ft_printf("error creation open function redirec > output \n");
        else
            ft_tab_output(cmds->output, fd);
    }
    else if (cmds->chevron == 2)
    {
        if ((fd = open(argv, O_RDWR | O_CREAT | O_APPEND, 0644)) < 0)
            ft_printf("error creation open function redirec >> ouput \n");
        else   
             ft_tab_output(cmds->output, fd);
    }
}

//largument (input) de ma commande est modifie par <, cela devient le fichier de droite
//(wc -l < salut.txt va lister nb de ligne de salut.txt)
//je cree donc un nouveau FD

void    redirection(t_cmds *cmds)
{
    int i;
    int fd;

    i = 0;
    while (i < cmds->argc)
    {
        which_chevron(cmds, cmds->argv[i]);
        if (cmds->chevron < 3)
        {
            if (cmds->chevron == 1)
               {
                    //ft_printf("cmds->argv[i + 1]:%s\n", cmds->argv[i + 1]);
                    if ((fd = open(cmds->argv[i + 1], O_RDONLY)) < 0)
                      ft_printf("error open function redirec < input\n");
                    cmds->input = fd;
                }
             else 
                redirec_output(cmds, cmds->argv[i + 1]);
            free(cmds->argv[i]);         //je free les arg que je viens de traiter
            free(cmds->argv[i + 1]);
            cmds->argv[i] = NULL;           // je les fait pointer sur null pour pouvoir les retirer
            cmds->argv[i + 1] = NULL;
            i++;
        }
        i++;
    }
    //test_cmd(*cmds);
    command_clean(cmds); //ermet d'enlever les commande executees qui pointent sur NULL et de lier le tab d'arg a execute
 //   test_cmd(*cmds);
} 