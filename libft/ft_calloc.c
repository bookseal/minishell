#include "../main.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	idx;

	if (n == 0)
		return ;
	else
	{
		idx = 0;
		while (idx < n)
		{
			((char *)s)[idx] = 0;
			idx++;
		}
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}