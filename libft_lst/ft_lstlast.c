#include "libft.h"

t_list *ft_lstlast(t_list *lst)
{
	int size;
	int i;
	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	i = 0;
	while (i < size - 1)
	{	
		lst = lst->next;
		i++;
	}
	return (lst);
}
