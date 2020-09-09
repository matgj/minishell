#include "minishell.h"


t_cmds    parse_cmd(char *cmds_pipe)
{
    char    **token; //partie 1 de la commande
    int     i;
    t_cmds   cmds;

    i = 0;
    token = ft_split(cmds_pipe,' '); //je split une commande separeees par pipe en tokens separees par espace
    free(cmds_pipe);
    while (token[i])
            i++;
    if(!(cmds.argv = (char **)malloc(sizeof(char *) * ARG_MAX + 1)))
        return (cmds);
    cmds.argc = i;
    i = 0;
    while(token[i])
    {
         cmds.argv[i] = token[i];
         printf("token:%s\n",token[i]);
         i++;
    } 
    free(token);
    cmds.argv[i] = NULL;
    command_management(cmds);
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
       printf("ligne separee par des pipes : cmds_pipes[%i]:%s\n", cpt, cmds_pipe[cpt]);
        cmds[cpt] = parse_cmd(cmds_pipe[cpt]);
        cpt++;
    }
    //free(cmds_pipe);
    //test_argv(cmds); //affiche le contenu des argv
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
    free(line); //on peut free line car on a le contenu de line dans cmds_semi
    while (cmds_semi[l]) 
    {
        i = 2;
        printf("ligne separee par des points virgules => cmds_semi[%i]:%s\n",l, cmds_semi[l]);
        cmds_pipe = parse_pipe(cmds_semi[l++]);
        //while (cmds_pipe[i].name)            // je parcours les tokens stockees dans la struct cmd sepaerees par la multitude de split
        //{
         //  execution;
           // command_management(*cmds_pipe); // passer le contenu et pas un pointeur sinon ca va pas etre independant à chaque cmd
           //printf("cmds_to_execute[%i]:%s\n",i, cmds_pipe[i].name);
          // i++;
        //};
    //  free(cmds_pipe);
    }
    free(cmds_semi);
}
