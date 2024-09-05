

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_free_arrstrn3(char ***words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free((*words)[i]);
		i++;
	}
	free(*words);
	*words = NULL; // se hace, debido al triple puntero
}

void	ft_free_arrstrn2(char **words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(words[i]);
		i++;
	}
	free(words);
	words = NULL; // no se hace
}


/**
 * ambos hacen los frees!
 */
int main()
{
	char **lista;
    int n = 3;

    lista = malloc(n * sizeof(char *));
    lista[0] = strdup("hola");
    lista[1] = strdup("h2ola");
    lista[2] = strdup("hol5a");

    ft_free_arrstrn3(&lista, n);
    if (lista == NULL)
		write(1,"----------null", 15);
	else
		write(1,"--------no-null", 16);

}
