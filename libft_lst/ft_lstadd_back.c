#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;
	if (!lst)
		return;
	if (*lst)
		tmp = *lst;
	else
		{
			*lst = new;
			return ;
		}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
