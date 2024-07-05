
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
