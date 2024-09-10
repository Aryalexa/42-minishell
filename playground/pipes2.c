

#include "../3_utils/utils.h"
#include <sys/wait.h>
#include <fcntl.h>

void	my_exec(char *cmd, char *argv[], char *env[])
{
    
	int	pid;
	int	status; // salida!!

    // dup2(fd[0], STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{

        // lectura: pipe con contenido
        // escritura SDTOUT
		debug("child execs");
        // char * buff[2000];
		// read(0, buff, 45);
		// debug("read done");
		// write(2, buff, 45);
		// debug("write done");
		// write(1, "salida\n", 7);
		
		execve(cmd, argv, (char *const *)env);
	}
	else
	{
		debug("parent waiting");
		if (wait(&status) == -1)
			my_perror_exit("wait error");
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			my_perror_exit("child did not success");

		debug("parent waited!");
	}
}


int main(int argc, char *argv[], char *env[])
{
    
    int pipefd[2];

    if (pipe(pipefd)  == -1)
        my_perror_exit("pipe failed");

    (void)argc;
    (void)argv;
	char *cmd1 = "/usr/bin/ls";
    char *argv1[] = {"ls", NULL};
	char *cmd2 = "/usr/bin/wc";
    char *argv2[] = {"wc", "-l", NULL};

    dup2(pipefd[1], STDOUT_FILENO);
    my_exec(cmd1, argv1, env);
    dup2(pipefd[0], STDIN_FILENO);
    
    my_exec(cmd2, argv2, env);
    dup2(pipefd[0], STDIN_FILENO);


}