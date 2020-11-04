/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:42:24 by Mathis            #+#    #+#             */
/*   Updated: 2020/11/04 10:56:28 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		equal_sign(char *var)
{
	int i;

	i = 0;
	if (!ft_strlen(var))
		return (-1);
	while (var[i])
	{
		if (i == 0 && var[i] == '=')
			return (-1);
		if (var[i] == ' ')
			return (-1);
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}


void	ft_env_export(t_cmds cmds, int print)
{
	int i;

	i = 0;
	if (cmds.argc == 1)
	{
		while (g_shell.envp[i])
		{
			if (print)
				ft_printf("declare -x ");
			ft_printf("%s\n", g_shell.envp[i++]);
		}
		env_status(0);
	}
	else
	{
		ft_printf("env: %s: No such file or directory\n", cmds.argv[1]);
		exit(127);
	}
}

int		ft_export(t_cmds cmds)
{
	int i;
	int sign;
	int 		flag;

	flag = cmds.argc - 1;
	i = 1;
	if (cmds.argc == 1)
		ft_env_export(cmds, 1);
	else if (check_error_export(cmds, &flag))
	{
		while (i < cmds.argc)
		{
			if ((sign = equal_sign(cmds.argv[i])) == 1)
			{

				add_env_status(cmds.argv[i]);
				env_status(0);
			}
			else if (sign == -1)
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n",
						cmds.argv[i]);
				env_status(1);
			}
			else
				env_status(0);
			i++;
		}
	}
	return (1);
}
