/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:39 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/27 17:44:27 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//je remplis ma struct cmd

t_cmds    parse_cmd(char *cmds_pipe) 
{
    char    **token; //partie 1 de la commande
    int     i;
    t_cmds   cmds;

    i = 0;
    token = ft_split(cmds_pipe,' '); //je split une commande separeees par pipe en tokens separees par espace
    free(cmds_pipe);
   // command_quotes(token);
    while (token[i])
            i++;
    if(!(cmds.argv = (char **)malloc(sizeof(char*) * i + 1)))
        return (cmds);
    cmds.argc = i;
    i = 0;
    while(token[i])
    {
         cmds.argv[i] = token[i];
         insert_actions(cmds.argv[i]);
         printf("token[%i]:%s\n",i, token[i]);
         i++;
    } 
    free(token);
    i = 0;
    while (i < ARG_MAX)
        cmds.output[i++] = -1;
    command_management(&cmds);
  //   test_cmd(cmds);
  //  test_tab_cmds(&cmds, i);
    //   if (!command_type(&cmds)) //pour savoir si cest une builtin fonction, si ca n'est pas une builtin on execute l'exe qu'on a dans path
    //        command_exec(cmds);
    return (cmds);
}

t_cmds   *parse_pipe(char *cmds_semi)
{
    t_cmds   *cmds; //cmds a executer sans pipe ni semi
    char    **cmds_pipe; //cmds_semi pour ligne de commandes separees par des SEMICOLON (=> ;)
    int     cpt; 
    t_cmds   nul;

    cpt = 0;
    cmds_pipe = ft_split(cmds_semi, '|'); // je split une ligne de commande separees par ; en commande separrees par pipe
    free(cmds_semi);
    while(cmds_pipe[cpt]) // on compte le nombre de commande dans la ligne de commande pour malloc 
            cpt++;
   // printf("nbre de cmd pipes:%i \n", cpt);
    if(!(cmds = ft_calloc(sizeof(t_cmds), cpt + 1)))// pour chaque commande separrees par des pipes je cree une struct cmd
        return (NULL); 
    cpt = 0;
    while(cmds_pipe[cpt])
    {
     //  printf("ligne separee par des pipes : cmds_pipes[%i]:%s\n", cpt, cmds_pipe[cpt]);
        cmds[cpt] = parse_cmd(cmds_pipe[cpt]);
        cpt++;
    }
    free(cmds_pipe);
    nul.name = NULL;
    cmds[cpt] = nul;
    command_plug(cmds);
    return (cmds);
}

//d'abord on decoupe la ligne lue par gnl en tableau de ligne de commandes, 
//chaque ";" dans une ligne constitue une ligne de commande à executer independamment des autres 
//ls -l | cat -e ; echo my name is $USER ==> cest comme si dabord on entrait ls -l dans le terminal et qu'on appuie sur ENTER
//puis qu'on entrait echo my name is $USER, ce sont deux commandes totalement distinctes

void    parsing(char *line)
{
    char    **cmds_semi; //cmds_semi pour ligne de commandes separees par des SEMICOLON (=> ;)
    t_cmds  *cmds_pipe; //cmds_pipe pour commandes separees par des PIPES (=> |)
    char    *line_env;
    int     l; //ligne
    int     i;

    l = 0;
    quotes(line); //analyse sil y a des '' "" ou \'
    line_env = var_env(line);//remplacer ce qui a apres un $ par la var d'env associée
    free(line);
    //printf("---------line : %s\n", line);
    cmds_semi = ft_split(line_env,';');
    free(line_env); //on peut free line car on a le contenu de line dans cmds_semi
    while (cmds_semi[l]) 
    {
        i = 0;
     //   printf("ligne separee par des points virgules => cmds_semi[%i]:%s\n",l, cmds_semi[l]);
        cmds_pipe = parse_pipe(cmds_semi[l++]);
        while (cmds_pipe[i].name)            // je parcours mon tableau de structure commande separees par des pipes
         { 
               command_exec(cmds_pipe[i]);
               i++;
            // test_tab_cmds(cmds_pipe, i);
            // command_exec(cmds_pipe[i]);
         }
    //command_exec2();
    free(cmds_pipe);
    }
    free(cmds_semi);
}
