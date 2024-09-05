#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * i want w1 the same as w2
 */
void duppp(char **w1, char **w2)
{
	char *aux;

	aux = *w1;
	*w1 = *w2;
	free(aux);
}

int main()
{
	char *s;
	char *s2;

	s = strdup("hola");
	s2 = strdup("adios");
	
	//
	write(1, s, strlen(s));
	write(1, s2, strlen(s2));
	duppp(&s, &s2);
	write(1, s, strlen(s));
	write(1, s2, strlen(s2));
	//free(s);
	free(s2);

}
