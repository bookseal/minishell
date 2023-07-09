#include "../main.h"

static int	is_set(char *set, char c)
{
	size_t	idx;

	idx = 0;
	while (set[idx] != '\0')
	{
		if (set[idx] == c)
			return (1);
		idx++;
	}
	return (0);
}

static size_t	trim_from_end(char *s1, char *set)
{
	size_t	idx;

	idx = ft_strlen(s1) - 1;
	while (idx > 0 && s1[idx] != '\0')
	{
		if (is_set((char *)set, s1[idx]))
			idx--;
		else
			return (idx);
	}
	if (idx == 0)
		return (ft_strlen(s1));
	return (idx);
}

static size_t	trim_from_beginning(char *s1, char *set)
{
	size_t	idx;

	idx = 0;
	while (s1[idx] != '\0')
	{
		if (is_set((char *)set, s1[idx]))
			idx++;
		else
			return (idx);
	}
	return (idx);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*new_str;
	size_t	idx_begin;
	size_t	idx_end;

	if (s1 == 0 || set == 0)
		return (0);
	if (!ft_strlen(s1))
	{
		new_str = (char *)malloc(sizeof(char) * 1);
		*new_str = '\0';
		return (new_str);
	}
	idx_begin = trim_from_beginning((char *)s1, (char *)set);
	idx_end = trim_from_end((char *)s1, (char *)set);
	new_str = (char *)malloc(sizeof(char) * (idx_end - idx_begin + 2));
	if (new_str == 0)
		return (0);
	ft_strlcpy(new_str, &s1[idx_begin], idx_end - idx_begin + 2);
	free(s1);
	return (new_str);
}