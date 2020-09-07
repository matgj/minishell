#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new_elem;
	t_list	*temp;

	(void)del;
	temp = NULL;
	if (f == NULL || lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (!(new_elem = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		new_elem->content = f(lst->content);
		if (temp == NULL)
			first = new_elem;
		else
			temp->next = new_elem;
		new_elem->next = NULL;
		temp = new_elem;
		lst = lst->next;
	}
	return (first);
}
