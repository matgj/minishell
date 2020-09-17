#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	if (!(x = malloc(size * count)))
		return (0);
	ft_bzero(x, count);
	return (x);
}