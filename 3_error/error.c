
#include "error.h"


void    perror_exit(char *msg)
{
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    //ft_printf("bye\n");
    exit(1);
}