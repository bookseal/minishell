#include "../main.h"

size_t	is_needle(char *haystack, char *needle, size_t idx, size_t len)
{
	size_t	idx_needle;

	idx_needle = 0;
	while (haystack[idx] != '\0' && needle[idx_needle] != '\0' && idx < len)
	{
		if (haystack[idx] != needle[idx_needle])
			return (0);
		else
		{
			idx++;
			idx_needle++;
		}
	}
	if (needle[idx_needle] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;
	size_t	len_haystack;
	size_t	len_needle;
	char	*ptr_haystack;
	char	*ptr_needle;

	len_haystack = ft_strlen(haystack);
	len_needle = ft_strlen(needle);
	ptr_haystack = (char *)haystack;
	ptr_needle = (char *)needle;
	if (*ptr_needle == '\0')
		return (ptr_haystack);
	idx = 0;
	while (ptr_haystack[idx] != '\0' && idx < len)
	{
		if ((idx + len_needle <= len_haystack)
			&& is_needle(ptr_haystack, ptr_needle, idx, len))
			return (&ptr_haystack[idx]);
		idx++;
	}
	return (0);
}
