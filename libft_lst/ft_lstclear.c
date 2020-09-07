#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;
	t_list *next;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = next;
		}
	*lst = NULL;
	}
}
