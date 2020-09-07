#include "minishell.h"

void     test(t_cmds *cmds)
{
    int l = 0;
    while (cmds->arg[l])
    {
        printf("cmd->arg[%i]:%s\n", l, cmds->arg[l]); //affiche le contenu de ma struct arg
        l++;
    }
}

t_cmds    parse_cmd(char *cmds_pipe)
{
    char    **token; //partie 1 de la commande
    int     i;
    t_cmds   cmds;

    i = 0;
    token = ft_split(cmds_pipe,' '); //je split une commande separeees par pipe en tokens separees par espace
//    free(cmds_pipe);
    while (token[i])
            i++;
    if(!(cmds.arg = (char **)malloc(sizeof(char *) * i + 1 )))
        return (cmds);
    i = 0;
    while(token[i])
    {
         cmds.arg[i] = token[i];
         i++;
    }
    cmds.arg[i] = NULL;
    return (cmds);
}

t_cmds   *parse_pipe(char *cmds_semi)
{
    t_cmds   *cmds; //cmds a executer sans pipe ni semi
    char    **cmds_pipe; //cmds_semi pour ligne de commandes separees par des SEMICOLON (=> ;)
    int     cpt; 

    cpt = 0;
    cmds_pipe = ft_split(cmds_semi, '|'); // je split une ligne de commande separees par ; en commande separrees par pipe
   // free(cmds_semi);
    while(cmds_pipe[cpt]) // on compte le nombre de commande dans la ligne de commande pour malloc 
            cpt++;
    if(!(cmds = (t_cmds*)malloc(sizeof(t_cmds) * cpt + 1))) // pour chaque commande je cree une chaine cmd
         return (NULL);
    cpt = 0;
    while(cmds_pipe[cpt])
    {
        printf("cmds_pipes[%i]:%s\n", cpt, cmds_pipe[cpt]);
        cmds[cpt] = parse_cmd(cmds_pipe[cpt]);
        cpt++;
    }
    test(cmds);
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
    int     l; //ligne
    int     i;

    l = 0;
    cmds_semi = ft_split(line,';');
  //  free(line); //on peut free line car on a le contenu de line dans cmds_semi
    while (cmds_semi[l]) 
    {
        i = 0;
        printf("cmds_semi[%i]:%s\n",l, cmds_semi[l]);
        cmds_pipe = parse_pipe(*cmds_semi);
        while (cmds_pipe[i].cast)            // je parcours les tokens stockees dans la struct cmd sepaerees par la multitude de split
        {
            command_creation(*cmds_pipe);
          // printf("cmds_to_execute[%i]:%s\n",i, cmds_pipe[i].cmd);
            i++;
        }
        l++;
    }
}
