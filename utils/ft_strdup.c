#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_memmove(str, s1, len);
	str[len] = '\0';
	return (str);
}
