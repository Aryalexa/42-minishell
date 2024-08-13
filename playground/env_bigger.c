# include "../1_libft/libft.h"

char ** add_one(char **list, int n_items, char *new_str)
{
	char	**copy;
	int		i;

	copy = malloc((n_items + 1) * sizeof(char *));
	i = 0;
	while (i < n_items - 1)
	{
		copy[i] = list[i];
		i++;
	}
	copy[i++] = ft_strdup(new_str);
	copy[i] = NULL;
	free(list);
	return (copy);
}

int main(int argc, char **argv)
{
	char	**list1;
	char	**list2;
	int		i;

	(void)argc;
	(void)*argv;
// crear env
	list1 = malloc(4 * sizeof(char *));
	i = 0;
	while (i < 3)
	{
		list1[i] = ft_strdup("holan");
		i++;
	}
	list1[3] = NULL;
	ft_printf("before:");
	ft_putarr_str(list1);
	// añadir uno
	list2 = add_one(list1, 4, "nuevo");
	ft_printf("after:");

	ft_putarr_str(list2);
	ft_free_arrstr(list2);
}
