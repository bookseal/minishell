#include "main.h"

char	*ft_strjoin(char *s1, char *s2, char sep)
{
	char	*result_s;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result_s = (char *)ft_calloc(sizeof(char), (len_s1 + len_s2 + 1 + 1));
	ft_strlcpy(result_s, s1, len_s1 + 1);
	result_s[len_s1] = sep;
	ft_strlcat(result_s, s2, len_s1 + len_s2 + 1 + 1);
	return (result_s);
}