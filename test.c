/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:53 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 12:56:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void       test_cmd(t_cmds cmds)
{
    int l = 0;
    ft_printf("cmds->name:%s\n",cmds.name); //affiche le contenu de name dans la struct cmds.
    ft_printf("cmds->path:%s\n",cmds.path);
    ft_printf("cmds->argc:%d\n",cmds.argc);
   while (cmds.argv[l])
  {
      ft_printf("cmds->argv[%i]:%s\n", l, cmds.argv[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
       l++;
   }
   
    ft_printf("cmds->chevron:%i\n",cmds.chevron);
    ft_printf("cmds->input:%i\n",cmds.input);
    // l = 0;
    // while (cmds.output[l] != -1)
    // {
    //     ft_printf("cmds->ouput[%i]:%i\n", l, cmds.output[l]);
    //     l++;
    // }
}

void     test_env(t_cmds *cmds)
{
   int l = 0;
   while (g_shell.envp[l])
   {
       ft_printf("g_shell->envp[%i]:%s\n", l, g_shell.envp[l]); //affiche le contenu du pointeur sur tableau de pointeur de string contenant les tokens (arguments des execve et builtin)
       l++;
   }
}

// void    test_tab_cmds(t_cmds *cmds, int l)
// {
//    // int l = 0; 
//     int i = 0;
//     while (cmds[l].name)
//     {
//         while (cmds[l].output[i] != -1)
//      {
//        // ft_printf("cmds.argv\n");
//          ft_printf("cmds[%i]->ouput[%i]:%i\n", l, i, cmds[l].output[i]); //affiche le tab ouput dune commande
//          i++;
//       }   
//      l++;
//     }
// }