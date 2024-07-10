
#include "error.h"


void	perror_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	my_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	*my_malloc(size_t size)
{
	void	*val;

	val = malloc(size);
	if (!val)
		perror_exit("malloc: mem error.");
	return (val);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*val;

	val = ft_calloc(count, size);
	if (!val)
		perror_exit("calloc: mem error.");
	return (val);
}
