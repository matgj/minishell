/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:35 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/24 12:27:38 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell g_shell;

int		builtin_type_parent(t_cmds cmds)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(cmds.name, "cd"))
		ret = ft_cd(cmds);
	else if (!ft_strcmp(cmds.name, "export"))
		ret = ft_export(cmds);
	else if (!ft_strcmp(cmds.name, "unset"))
		ret = ft_unset(cmds);
	else if (!ft_strcmp(cmds.name, "exit"))
	 	ret = ft_exit(cmds);
	return (ret);
}

int		builtin_type_child(t_cmds cmds)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(cmds.name,"echo"))
		ret = ft_echo(cmds);
	else if (!ft_strcmp(cmds.name,"pwd"))
		ret = ft_pwd(cmds);
	else if (!ft_strcmp(cmds.name,"env"))
		ret = ft_env(cmds);
	else
		return (0);
	exit(0);
	return (ret);
}

/*
**A common use of pipes is to send data to or receive data
**from a program being run as a subprocess.
**One way of doing this is by using a combination of
**pipe (to create the pipe), fork (to create the subprocess),
**dup2 (to force the subprocess to use the pipe as its standard
**input or output channel), and exec (to execute the new program).
*/

void   command_exec_child(t_cmds cmds)
{
	int i;
	int ret;
	i = 0;
	plug_fd(cmds);
	if (!builtin_type_child(cmds))
	{
		 if (cmds.input < 0)
		 	 exit(1);
		cmds.path = find_path(cmds.name);
		if (!cmds.path)
			ret = -1;
		if ((ret = execve(cmds.path, cmds.argv, g_shell.envp)) == -1)
			ft_print_err_exec(cmds);
	}
}

/*
**fork()
**Negative Value: creation of a child process was unsuccessful.
**Zero: Returned to the newly created child process.
**Positive value: Returned to parent or caller. The value
**contains process ID of newly created child process.
*/

int		command_exec(t_cmds cmds)
{
	pid_t	pid;
	int		i;
	int		ret;

	if (builtin_type_parent(cmds))
	{
		free_struct(cmds);
		g_shell.pid = -1;
		return (1);
	}
	if ((pid = fork()) == -1)
	{
		ft_putstr_fd("fork error\n,", 2);
		exit(127);
	}
	else if (pid == 0)
			command_exec_child(cmds);
	else
			g_shell.pid = pid;
	close_fds(cmds);
	free_struct(cmds);
	return (g_shell.status == 0);
}

void	command_management(t_cmds *cmds)
{
	int		ret;
	pid_t	pid;
	int		i;

	i = 0;
	if (!cmds->argc)
		return ;
	command_creation(cmds);
	cmd_last_arg(cmds);
	redirection(cmds);
	while (cmds->argv[i])
		i++;
	cmds->argc = i;
}
