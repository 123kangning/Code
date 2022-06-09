#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int in = 0, out = 0, add = 0, bg = 0, cmdsize = 100, realsize = 0;
char *last;

char **getcmd(int *p);
char **cutcmd(char *input);
void execcmd(char **cmd);
void swap(int *fd0, int *fd1);
void piexec(char **cmd, int *p, int pipesize);
void piexec1(char **cmd, int *p, int pipesize);
void mywait(pid_t pid, int *status, int options);
void newexec(char **cmd, int *p, int pipesize, int start, int head);

int main(void)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);
    setvbuf(stdout, NULL, _IONBF, 0);

    last = (char *)malloc(sizeof(char) * 100);

    while (1)
    {
        out = 0, add = 0, realsize = 0;
        int p[10] = {0}, sfd, fd, pipesize = 0;
        printf("# ");

        char **cmd = getcmd(p);
        if (strcmp(cmd[0], "\n") == 0)
        {
            free(cmd[0]);
            cmd[0] = NULL;
            free(cmd);
            cmd = NULL;
            continue;
        }

        int aaa = 0;
        if (in)
        {
            sfd = dup(STDIN_FILENO);
            fd = open(cmd[in], O_RDWR, S_IRUSR | S_IWUSR);
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                fprintf(stderr, "error dup2\n");
                exit(1);
            }
            free(cmd[in]);
            cmd[in] = NULL;
        }

        if (strcmp(cmd[0], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(cmd[0], "cd") == 0)
        {
            if (cmd[1] && strcmp(cmd[1], "-") == 0)
            {
                if (last)
                {

                    char *buf = (char *)malloc(sizeof(char) * 100);
                    getcwd(buf, 100);
                    printf("%s\n", last);

                    chdir(last);

                    strcpy(last, buf);
                }
                else
                { // last==NULL
                    printf("bash: cd: OLDPWD 未设定\n");
                }
            }
            else
            {

                getcwd(last, 100);
                chdir(cmd[1]);
            }

            continue;
        }

        for (int i = 0; i < 10; i++)
        {
            if (p[i])
                pipesize++;
        }
        if (p[0])
        {
            piexec(cmd, p, pipesize);
        }
        else
            execcmd(cmd);

        if (in)
        {
            if (dup2(sfd, STDIN_FILENO) == -1)
            {
                fprintf(stderr, "error dup2\n");
            }
            in = 0;
        }
        // printf("realsize = %d\n",realsize);
        for (int i = 0; i < realsize; i++)
        {
            if ((add && (i == add)) || (out && (i == out)) || (in && (i == in)))
                continue;
            free(cmd[i]);
            cmd[i] = NULL;
        }
        free(cmd);
        cmd = NULL;
    }
    free(last);
    return 0;
}
char **getcmd(int *p)
{
    char **cmd = (char **)malloc(sizeof(char *) * cmdsize);
    char *input = (char *)malloc(sizeof(char) * 1000);
    int len = 0, count = 0, pi = 0, i = 0;
    if (fgets(input, 1000, stdin) == NULL)
    {
        input[0] = 0;
    }

    int l = strlen(input);
    if (l == 0)
    {

        free(cmd);
        free(input);
        exit(0);
    }

    if (strcmp(input, "\n") == 0)
    {
        cmd[0] = (char *)malloc(5);
        strcpy(cmd[0], "\n");
        free(input);
        return cmd;
    }

    input[l - 1] = '\0';
    // add_history(input);
    while (len < l - 1)
    {
        while (input[len] == ' ')
        {
            len++;
            i++;
        }

        while (len < l - 1 && (input[len] != ' ' && input[len] != '|' && input[len] != '>' && input[len] != '<' && input[len] != '&'))
        {
            if (input[len] == '&')
            {
                bg = 1;
                input[len] = ' ';
            }

            len++;
        }
        cmd[count] = (char *)malloc(sizeof(char) * 20);
        realsize++;
        strncpy(cmd[count++], input + i, len - i);
        cmd[count - 1][len - i] = '\0';
        if (strcmp(cmd[count - 1], "~") == 0)
        {
            strcpy(cmd[count - 1], "/home/kangning");
        }
        // printf("|%s|\n",cmd[count-1]);
        while (input[len] == ' ' || input[len] == '&')
        {
            if (input[len] == '&')
            {
                bg = 1;
            }
            len++;
        }

        if (input[len] == '<')
        {
            in = count;
            len++;
        }
        else if (input[len] == '>')
        {
            len++;
            if (input[len] == '>')
            {
                len++;
                add = count;
            }
            else
                out = count;
        }
        if (input[len] == '|')
        {
            len++;
            p[pi++] = count;
        }

        while (input[len] == ' ' || input[len] == '<' || input[len] == '|' || input[len] == '>')
        {
            len++;
        }
        i = len;
    }
    free(input);
    input = NULL;
    return cmd;
}

char **cutcmd(char *input)
{
    char **cmd = (char **)malloc(sizeof(char *) * cmdsize);
    int len = 0, count = 0, pi = 0, i = 0;

    int l = strlen(input);
    while (len < l)
    {

        cmd[count] = (char *)malloc(sizeof(char) * 20);
        while (len < l && (input[len] != ' '))
        {
            len++;
        }
        strncpy(cmd[count++], input + i, len - i);
        if (strcmp(cmd[count - 1], "~") == 0)
        {
            strcpy(cmd[count - 1], "/home/kangning");
        }
        i = len;

        while (input[len] == ' ' || input[len] == '|')
        {
            i++;
            len++;
        }
    }
    return cmd;
}

void execcmd(char **cmd)
{
    pid_t pid;
    int status;
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        return;
    case 0:
        if (out)
        {
            int fd;

            if ((fd = open(cmd[out], O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
            {
                perror("open");
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
            free(cmd[out]);
            cmd[out] = NULL;
        }
        if (add)
        {
            int fd;

            if ((fd = open(cmd[add], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
            {
                perror("open");
            }
            lseek(fd, -1, SEEK_END);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            free(cmd[add]);
            cmd[add] = NULL;
        }
        execvp(cmd[0], cmd);
    default:
        if (!bg)
            mywait(pid, &status, 0);
    }
}

void swap(int *fd0, int *fd1)
{
    int temp = *fd0;
    *fd0 = *fd1;
    *fd1 = temp;
}

void mywait(pid_t pid, int *status, int options)
{
    waitpid(pid, status, options);

    if (WIFSIGNALED(*status))
    {
        printf("\nshell be killed by %d", WTERMSIG(*status));
        if (WCOREDUMP(*status))
        {
            printf("\n退出 (核心已转储)");
        }
    }
}

void piexec(char **cmd, int *p, int pipesize)
{
    char subcmd[10][50]={};
    int start = 0, i = 0, status;
    pid_t ppid;

    for (i = 0; i < pipesize; i++)
    {
        for (int j = start; j < p[i]; j++)
        {
            if (cmd[j])
            {
                strcat(subcmd[i], cmd[j]);
                strcat(subcmd[i], " ");
            }
        }
        start = p[i];
    }

    ppid = fork();
    if (ppid == -1)
    {
        perror("fork");
    }
    else if (ppid == 0)
    {
        pid_t pid;
        int sfd[2];
        for (i = 0; i <= pipesize; i++)
        {
            if (i == 0)
            {
                if ((pid = fork()) == -1)
                {
                    perror("fork");
                }
                else if (pid == 0)
                {
                    int fd[2];
                    if ((fd[0] = open("fifo1", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }
                    if ((fd[1] = open("fifo2", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }

                    sfd[1] = dup(STDOUT_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    char **tmp = cutcmd(subcmd[i]);
                    execvp(cmd[0], tmp);
                }
                else
                {
                    mywait(pid, &status, 0);
                    dup2(sfd[1], STDOUT_FILENO);
                }
            }
            else if (i < pipesize)
            {
                if ((pid = fork()) == -1)
                {
                    perror("fork");
                }
                else if (pid == 0)
                {
                    int fd[2];
                    if ((fd[0] = open("fifo1", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }
                    if ((fd[1] = open("fifo2", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }
                    swap(&fd[0], &fd[1]);

                    sfd[1] = dup(STDOUT_FILENO);
                    sfd[0] = dup(STDIN_FILENO);

                    dup2(fd[0], STDIN_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    execvp(cmd[p[i]], cutcmd(subcmd[i]));
                }
                else
                {
                    mywait(pid, &status, 0);
                    dup2(sfd[0], STDIN_FILENO);
                    dup2(sfd[1], STDOUT_FILENO);
                }
            }
            else
            {
                if ((pid = fork()) == -1)
                {
                    perror("fork");
                }
                else if (pid == 0)
                {
                    int fd[2];
                    if ((fd[0] = open("fifo1", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }
                    if ((fd[1] = open("fifo2", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
                    {
                        perror("open");
                    }
                    if (pipesize % 2)
                        swap(&fd[0], &fd[1]);

                    sfd[0] = dup(STDIN_FILENO);
                    int res = dup2(fd[0], STDIN_FILENO);
                    if (res == -1)
                    {
                        fprintf(stderr, "error dup2\n");
                        exit(1);
                    }
                    if (out)
                    {
                        int fd;
                        if ((fd = open(cmd[out], O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
                        {
                            perror("open");
                        }

                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        free(cmd[out]);
                        cmd[out] = NULL;
                    }
                    if (add)
                    {
                        int fd;

                        if ((fd = open(cmd[add], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) == -1)
                        {
                            perror("open");
                        }
                        lseek(fd, -1, SEEK_END);
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        free(cmd[add]);
                        cmd[add] = NULL;
                    }
                    close(fd[0]);
                    close(fd[1]);
                    printf("here\n");
                    execvp(cmd[start], cmd + start);
                }
                else
                {
                    mywait(pid, &status, 0);
                    dup2(sfd[0], STDIN_FILENO);
                }
            }
        }
    }
    else if (ppid > 0)
    {
        if (!bg)
        {
            mywait(ppid, &status, 0);
        }
        // while(1){
        //     sleep(1);
        //     printf("-");
        // }
        unlink("fifo1");
        unlink("fifo2");
    }
}
