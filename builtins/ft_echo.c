#include "../minishell.h"

int		ft_echo(t_cmds cmds)
{	
	int 		i;
	int 		nflag;


	if (!cmds.argv[1])
		write(1, "\n", 1);
	else
	{
		nflag = (!ft_strcmp("-n", cmds.argv[1])) ? 1 : 0;
		i = (nflag == 1) ? 2 : 1;
		while (i < cmds.argc)
		{
			ft_putstr_fd(cmds.argv[i++], 1);
			(i == cmds.argc) ? 0 : write(1, " ", 1);
		}
		(nflag == 0) ? write(1, "\n", 1) : 0;
	}
	g_shell.status = 0;
	return (1);
}
