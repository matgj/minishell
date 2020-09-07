#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	n;

	if (!s1 && !s2)
		return (0);
	n = (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(str = malloc(sizeof(char) * n)))
		return (0);
	ft_memmove(str, s1, ft_strlen(s1));
	ft_memmove(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}
