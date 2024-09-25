#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

//#include <stdio.h>
#include <unistd.h>
// void test_terminal_tty()
// {
// 	char *name = ttyname(STDIN_FILENO);
// 	if (name != NULL)
// 		printf("stdin is associated with terminal: %s\n", name);
// 		// /dev/ttys002
// 	else
// 		perror("ttyname");

// 	int slot = ttyslot();
// 	if (slot > 0)
// 		printf("Terminal slot index: %d\n", slot);
// 	else
// 		perror("ttyslot");
	
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <termios.h>
// #include <sys/ioctl.h>
// // disable echo
// void test_iotcl()
// {
// 	struct termios term;

// 	// Get the current terminal attributes using ioctl
// 	if (ioctl(STDIN_FILENO, TIOCGETA, &term) == -1)
// 		perror("ioctl TCGETS");
// 	// Disable echo
// 	term.c_lflag &= ~ECHO;
// 	// Set the terminal attributes using ioctl
// 	if (ioctl(STDIN_FILENO, TIOCSETA, &term) == -1)
// 		perror("ioctl TCSETS");

// 	printf("Echo is now off. Type something: ");
// 	char buffer[100];
// 	fgets(buffer, sizeof(buffer), stdin);
// 	printf("\nYou typed: %s\n", buffer);

// 	// Restore original settings
// 	if (ioctl(STDIN_FILENO, TIOCGETA, &term) == -1)
// 		perror("ioctl TCGETS");
// 	term.c_lflag |= ECHO;
// 	if (ioctl(STDIN_FILENO, TIOCSETA, &term) == -1)
// 		perror("ioctl TCSETS");

// }

// #include <stdio.h>
// #include <unistd.h>
// #include <termios.h>
// // disable echo
// void test_tc_getset_att()
// {
// 	struct termios term;

// 	// Get the current terminal attributes
// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		perror("tcgetattr");

// 	// Disable echo
// 	term.c_lflag &= ~ECHO;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
// 		perror("tcsetattr");

// 	printf("Echo is now off. Type something: ");
// 	char buffer[100];
// 	fgets(buffer, sizeof(buffer), stdin);
// 	printf("\nYou typed: %s\n", buffer);

// 	// Restore original settings
// 	term.c_lflag |= ECHO;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
// 		perror("tcsetattr");
// }

// void test_env()
// {
// 	const char *env_var = "PATH";
// 	char *value = getenv(env_var);
// 	if (value != NULL) 
// 		printf("%s=%s\n", env_var, value);
// 	else
// 		printf("%s is not set.\n", env_var);
// }

// void test_prompt_hist()
// {
// 	const char prompt[] = "minishell >";

// 	char *line = readline(prompt);
// 	while (line)
// 	{
// 		printf("[%s]\n", line);
// 		add_history(line);
// 		free(line);
// 		line = readline(prompt);
// 	}
// 	printf("exit\n");
// }

// #include <stdio.h>
// #include <term.h>
// #include <curses.h>
// void test_terminfo()
// {
// 	char term_buffer[2048];

// 	if (tgetent(term_buffer, getenv("TERM")) != 1)
// 		fprintf(stderr, "Could not find terminfo entry for TERM.\n");

// 	// Use other terminfo functions with the loaded entry...
// 	if (tgetflag("am"))
// 		printf("Terminal has automatic margins.\n");
// 	else
// 		printf("Terminal does not have automatic margins.\n");

// 	int columns_ = tgetnum("co");
// 	if (columns_ != -1) 
// 		printf("Terminal has %d columns.\n", columns_);
// 	else
// 		printf("Could not determine number of columns.\n");

// 	char area[2048]; // Buffer to store terminfo strings
// 	char *area_ptr = area; // Pointer to the current position in the buffer

// 	// Get the clear screen string
// 	char *clearscreen = tgetstr("cl", &area_ptr);
// 	if (clearscreen != NULL)
// 	{
// 		// tputs(clearscreen, 1, putchar);
// 		printf("after clean\n");
// 		// printf("Clear screen sequence: %snew\n", clearscreen);
// 	}
// 	else
// 		printf("Could not determine clear screen sequence.\n");

// 	// Get the cursor motion string
// 	char *move_cursor = tgetstr("cm", &area_ptr);
// 	if (move_cursor != NULL)
// 	{
// 		char *move_cmd = tgoto(move_cursor, 10, 5);
// 		// tputs(move_cmd, 1, putchar);
// 		// printf("Moved cursor to column 10, row 5\n");
// 		// printf("Cursor move sequence to column 10, row 5: %sss\n", move_cmd);
// 		printf("new line\n");
// 	}
// 	else
// 		printf("Could not determine cursor move sequence.\n");
//}
	
	/**
	 * How It Works:

Buffer Management: The area buffer is used to store the terminfo strings 
retrieved by tgetstr. The initial pointer value of area is updated to point 
to the end of the last stored string. This ensures that subsequent calls to 
tgetstr do not overwrite previously stored strings.
String Storage: When tgetstr retrieves a string, it stores it in the buffer 
pointed to by *area. The pointer *area is then incremented past the stored 
string, preparing it for the next call to tgetstr.
	*/



int main(void) {
    while (1) {
        char *input = readline("Enter a command: ");
        printf("You entered: %s\n", input);
        //rl_on_new_line();
    }
    return 0;
}

/*
int main()
{
	//test_terminal();
	//test_env();
	//test_iotcl();
	// test_tc_getset_att();
	test_terminfo();
}*/

// gcc playground/playground_may.c -lreadline -lncurses