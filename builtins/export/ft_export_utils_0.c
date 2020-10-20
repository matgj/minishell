#include "../../minishell.h"

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	else
		return (0);
}

int		is_alnum(t_cmds cmds, int i)
{
	int 	k;
	int 	c;

	k = 0;
	while (cmds.argv[i][k])
	{
		c = cmds.argv[i][k];
		if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z') || c == '_' || c == '='))
			return (0);
		if (c == '=')
			return (1);
		k++;
	}
	return (1);
}

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

void	put_env(char *s, int fd, int len)
{
	if (!s)
		return ;
	write(fd, s, len);
}