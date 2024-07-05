#include "minishell.h"


void main_parser()
{
	t_token tokens[MAX_TKNS];

	//char *input = "  <in  \"'ls$USER'\" 'arg1 '$arg2'  |  543 'arg3' =fgf >> appendhere we $fd < file1 <<lim arg   ";
	char *input = " ls . $ass '< inf' | <    inf2 <<a cmd2 > s >s2 >>append arg11";
	//ft_printf("%c\n",input[0]);

	int n_t = lexer(input, tokens);
	print_tokens(tokens, n_t);

	int n_n = parse_tokens(tokens, n_t, nodes);
	print_nodes(nodes, n_n);


}


/*Begins minishell and checks the input*/
int main(int argc, char **argv)
{
	char	*input;
		t_cmdnode nodes[MAX_CMDS];


	while (1)
	{
		input = readline("minishell> ");
		if (input)
			add_history(input);

		//Ctrl+D and NULL management to exit program
		//if (input == NULL)


		
		free(input);
	}
	return (0);
}