/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:26:04 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/25 12:40:27 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_err_exec(t_cmds cmds)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmds.name, 2);
	ft_putstr_fd(" : command not found...", 2);
	ft_putstr_fd(" I guarantee you we look everywhere...", 2);
	ft_putstr_fd(" even under the sofa!\nMy grandma always says ", 2);
	ft_putstr_fd("three things in human life are important.", 2);
	ft_putstr_fd(" The first is to be kind. The second is to be kind.", 2);
	ft_putstr_fd(" And the third is to be kind.\n", 2);
	exit(127);
}
