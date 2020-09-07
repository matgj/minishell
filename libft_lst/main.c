#include "libft.h"

void	del(void *s)
{
	(void)s;
}

void	func(void *content)
{
	printf("f : %s\n", content);
}

int main(void)
{
	t_list *tmp;
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *last;
	t_list *new;
	t_list *hey;
	int i = 0;
	int size = 0;
	tmp = ft_lstnew("1");
	node1 = ft_lstnew("2");
	node2 = ft_lstnew("3");
	tmp->next = node1;
	node1->next = node2;
	node3 = ft_lstnew("4");
	ft_lstadd_front(&tmp, node3);
	printf("size = %i\n", size = ft_lstsize(node3));	
	last = ft_lstlast(node3);
	printf("last = %s\n", last->content);
	new = ft_lstnew("new");
	ft_lstadd_back(&node3, new);
	//ft_lstclear(&node3, del);
	ft_lstiter(node3,&func);
//	while (node3)
//	{
//		printf("node [%i] : %s\n",i,node3->content);
//		node3 = node3->next;
//		i++;
//	}
	void *ptr_func;
	ptr_func = func;
	hey = ft_lstmap(node1,ptr_func,del);
	while (hey)
	{
		func(hey->content);
		hey = hey->next;
		i++;
	}
	ft_lstdelone(node2, &del);
}
