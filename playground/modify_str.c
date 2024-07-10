#include "../1_libft/libft.h"
#include <string.h>



void change_str(char **s)
{
    char *s2;
    s2 = strdup("bye");
    ft_printf("s2:(%s)\n", s2);
    ft_printf("s2 dir:(%p)\n", s2);
    ft_printf("s dir:(%p)\n", *s);
    *s = s2;
    ft_printf("s dir:(%p)\n", *s);

}

int main()
{
    char *str;
    str = NULL;

    ft_printf("before str dir:(%p)\n", &str);
    ft_printf("before str dir:(%p)\n", str);
    change_str(&str);
    ft_printf("new val:(%s)\n", str);
    ft_printf("after str dir:(%p)\n", str);

}