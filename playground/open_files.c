
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fdout;
    char *f1 = "f1";
    char *f2 = "f2";

    fdout = open(f1, O_RDWR | O_CREAT | O_APPEND, 0777);
    write(fdout, "soy f1\n", 7);

	fdout = open(f2, O_RDWR | O_CREAT | O_TRUNC, 0777);
    write(fdout, "QQ", 7);

}