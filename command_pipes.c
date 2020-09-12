#include "minishell.h"

//lier les fd des commandes separees par des pipes
//syscall pipe
//dans pipe, fd[0] = read et fd[1] = write
//fork return 0 on success
//on fork pour avoir 2 process et faire le lien entre deux programmes
//parent receive data from child (data are sent when fd is close, so child close fd1 and parent fd0)
//toujours fermer le fd qu on utilise pas (si on est dans child on ferme fd[0] sinon on ferme fd[1])
//ensuite on duplique les fd dans le child sur les stin et stout pour
//quon puisse exec() les program avec les streams standards

void        command_plug(t_cmds *cmds)
{
    int   nb_cmds; //nb de commandes liees par des pipes
    int   fd[2];
    int   i;

    nb_cmds = 0;
    i = 0;
    while (cmds[nb_cmds].name != NULL)
            nb_cmds++;
    while(i < nb_cmds)
    {
        if (i != 0) // si je ne suis pas a la premiere commande
        {
            pipe(fd); //ouvre fd[0] = read et fd[1] = write, 
            ft_tab_output(cmds[i - 1].output, fd[1]); // l'output de la precedente commande write, je stock fd[1] de cote pour les fermer plus tard
           cmds[i].input = fd[0]; //mon input read
        }
        if (nb_cmds - i == 1) //si cest la derniere commande
        {
           ft_tab_output(cmds[i].output, 1);
        }
        ft_tab_output(cmds[i].output, -1);
        i++;
    } 
}