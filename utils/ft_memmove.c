#include "../minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	if (s > d)
		while (len--)
			*d++ = *s++;
	else if (s < d)
		while (len--)
			*(d + len) = *(s + len);
	return (dst);
}
