#include "libft.h"

void	*ft_memalloc_exit(size_t size)
{
	size_t	t;
	char	*str;

	t = -1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		exit(0);
	while (++t < size)
		str[t] = '\0';
	return (str);
}
