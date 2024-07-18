

#include "../3_utils/utils.h"
#include <sys/wait.h>
#include <fcntl.h>

void	child_executes(int ultimo, char *cmd, char *argv[], char *env[])
{
    int pipefd[2];
	int	pid;
	int	status; // salida!!

    if (pipe(pipefd)  == -1)
        my_perror_exit("pipe failed");
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
        close(pipefd[0]);
		if(!ultimo)
            dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd, argv, (char *const *)env);
	}
	else
	{
        close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
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
    

    (void)argc;
    (void)argv;
	char *cmd1 = "/usr/bin/ls";
    char *argv1[] = {"ls", NULL};
	char *cmd2 = "/usr/bin/wc";
    char *argv2[] = {"wc", "-l", NULL};
    
    child_executes(0, cmd1, argv1, env);
    
    child_executes(1, cmd2, argv2, env);


}