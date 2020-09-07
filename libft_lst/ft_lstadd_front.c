# include "libft.h"
void	ft_lstadd_front(t_list **aslt, t_list *new)
{
	if (!aslt)
		return ;
	if (aslt && new)
	{
		new->next = *aslt;
		*aslt = new;
	}
}
