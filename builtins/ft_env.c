#include "../minishell.h"

int			ft_env(t_cmds cmds)
{
	int 	i;

	i = 0;
	while (g_shell.envp[i])
	{
		ft_putendl_fd(g_shell.envp[i], 1);
		i++;
	}
	env_status(0);
	return (1);
}
