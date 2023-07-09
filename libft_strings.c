#include "main.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	else
	{
		idx = 0;
		while (dst[idx] != '\0')
			idx++;
		while (idx + 1 < dstsize)
		{
			if (*src != '\0')
				dst[idx] = *src;
			else
				break ;
			src++;
			idx++;
		}
		dst[idx] = '\0';
		return (ft_strlen(src) + ft_strlen(dst));
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ch1;
	unsigned char	ch2;
	size_t			idx;

	if (n == 0)
		return (0);
	idx = 0;
	while (1)
	{
		ch1 = (unsigned char)s1[idx];
		ch2 = (unsigned char)s2[idx];
		if (ch1 != ch2 || ch1 == '\0' || ch2 == '\0' || idx + 1 == n)
			break ;
		idx++;
	}
	return (ch1 - ch2);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;
	size_t	idx;

	ptr_s = (char *)s;
	idx = 0;
	while (1)
	{
		if (ptr_s[idx] == (unsigned char)c)
			return (&ptr_s[idx]);
		else if (ptr_s[idx] == '\0')
			return (0);
		else
			idx++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	if (dstsize != 0)
	{
		idx = 0;
		while (src[idx] != '\0' && idx + 1 < dstsize)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*result_str;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	result_str = 0;
	result_str = (char *)ft_calloc(sizeof(char), (len_s1 + 1));
	if (result_str == 0)
		return (0);
	ft_strlcpy(result_str, s1, len_s1 + 1);
	return (result_str);
}

