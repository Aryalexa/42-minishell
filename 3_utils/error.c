
#include "utils.h"


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

void	debug(char *msg)
{

	write(2, msg, ft_strlen(msg));
	//1 > 2
	// ft_printf
	//reset 1
}

/**
 * 0 -in
 * 1 - out
 * 2 -err
 * open .. 3,4,5
 * 3 - file
 * 
 * 
 * i = dup(1) --> i = 4 // 
 * 4 - out 
 * 
 * 
 * dup2(3, 1) --> 3 new out
 * 1 - file
 * 
 * dup2(4, 1) --> 4 new out
 * 1 - out 
 * 
 */