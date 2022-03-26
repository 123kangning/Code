#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int flags;

    if (argc > 1) {
        flags = fcntl(STDOUT_FILENO, F_GETFD);              /* Fetch flags */
        if (flags == -1){
            perror("fcntl - F_GETFD");
            exit(1);
        }
            

        flags |= FD_CLOEXEC;                    /* Turn on FD_CLOEXEC */

        if (fcntl(STDOUT_FILENO, F_SETFD, flags) == -1){
            perror("fcntl - F_SETFD");
            exit(1);
        }   /* Update flags */
            
    }

    execlp("ls", "ls", "-l", argv[0], (char *) NULL);
    return 0;
}
