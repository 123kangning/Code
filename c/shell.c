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

int in = 0, out = 0, add = 0, bg = 0,sign=0;

char **getcmd(int *p);
char **cutcmd(char *input);
void execcmd(char **cmd);
void piexec(char **cmd, int *p, int pipesize);
void mywait(pid_t pid, int *status, int options);
void newexec(char**cmd,int*p,int pipesize,int start,int head);

int main(void)
{

    // sigset_t set;
    // sigemptyset(&set);
    // sigaddset(&set, SIGINT);
    // sigprocmask(SIG_BLOCK, &set, NULL);

    while (1)
    {
        out = 0, add = 0;
        int p[10] = {0}, fd, pipesize = 0;
        printf("# ");
        char **cmd = getcmd(p);
        if (!cmd)
            continue;
        int aaa=0;
        if (in)
        {
            fd = open(cmd[in], O_RDWR, S_IRUSR|S_IWUSR);
            if(dup2(fd, STDIN_FILENO)==-1){
                
                perror("dup2");
                exit(1);
            }
            cmd[in] = NULL;
            sign=1;
        }//else{
        //     fd = open(cmd[in], O_RDWR, S_IRUSR|S_IWUSR);
        //     if(dup2(STDIN_FILENO,fd)==-1){
        //         perror("dup21111");
        //         printf("\n%s\n",strerror(errno));
        //         exit(1);
        //     }

        //     aaa=1;
        // }
        // if(aaa)printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        if (strcmp(cmd[0], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(cmd[0], "cd") == 0)
        {
            chdir(cmd[1]);
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
            //newexec(cmd,p,pipesize,0,0);
        }
        else
            execcmd(cmd);
        if(in){
            
            close(fd);
            in=0;
        }
        // fflush(stdout);
    }
    
    return 0;
}

char **getcmd(int *p)
{
    char **cmd = (char **)malloc(sizeof(char *) * 100);
    char *input = (char *)malloc(sizeof(char) * 1000);
    int len = 0, count = 0, pi = 0, i = 0;

    fgets(input, 1000, stdin);
    int l = strlen(input);
    if (l == 0)
        exit;
    if (l == 1)
        return NULL;
    input[l - 1] = '\0';
    while (len < l - 1)
    {
        while (input[len] == ' ')
        {
            len++;
            i++;
        }
        cmd[count] = (char *)malloc(sizeof(char) * 20);
        while (len<l && (input[len]!= ' ' && input[len]!= '|' && input[len]!= '>'&&input[len]!='<'&&input[len]!='&'))
        {
            if (input[len] == '&'){
                bg = 1;
                input[len]=' ';
            }
                
            len++;
        }
        strncpy(cmd[count++], input + i, len - i);
        printf("|%s|\n",cmd[count-1]);
        while (input[len] == ' '||input[len]=='&'){
            if(input[len]=='&'){
                bg=1;
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
    return cmd;
}

char **cutcmd(char *input)
{
    char **cmd = (char **)malloc(sizeof(char *) * 100);
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

            if ((fd = open(cmd[out], O_RDWR, S_IWUSR | S_IRUSR)) == -1)
            {
                perror("open");
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
            cmd[out] = NULL;
        }
        if (add)
        {
            int fd;

            if ((fd = open(cmd[add], O_RDWR, S_IWUSR | S_IRUSR)) == -1)
            {
                perror("open");
            }
            lseek(fd, -1, SEEK_END);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            cmd[add] = NULL;
        }
        execvp(cmd[0], cmd);
    default:
        if(!bg)
            mywait(pid, &status, 0);
        
        for (int i = 0; i < (sizeof(cmd) / sizeof(cmd[0])); i++)
        {
            free(cmd[i]);
        }
        free(cmd);
    }
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
// ls -al | wc 
void piexec(char **cmd, int *p, int pipesize)
{
    char **subcmd = (char **)malloc(sizeof(char *) * pipesize);
    int start = 0, i = 0, status;
    pid_t ppid;

    for (i = 0; i < pipesize; i++)
    {
        subcmd[i] = (char *)malloc(sizeof(char) * 100);
        strcpy(subcmd[i], "");
        for (int j = start; j < p[i]; j++)
        {
            strcat(subcmd[i], cmd[j]);
            strcat(subcmd[i], " ");
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
        int fd[2];
        char buf[1000];
        if (pipe(fd) == -1)
        {
            perror("pipe");
        }
        // dup2(fd[1],STDOUT_FILENO);
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
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    char **tmp = cutcmd(subcmd[i]);
                    execvp(cmd[0], tmp);
                }
                else
                {
                    mywait(pid, &status, 0);
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
                    dup2(fd[0], STDIN_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    execvp(cmd[p[i]], cutcmd(subcmd[i]));
                }
                else
                {
                    mywait(pid, &status, 0);
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
                    int res = dup2(fd[0], STDIN_FILENO);
                    if (res == -1)
                    {
                        fprintf(stderr, "error dup2\n");
                        exit(1);
                    }
                    close(fd[0]);
                    close(fd[1]);
                    if (out)
                    {
                        int fd;
                        if ((fd = open(cmd[out], O_RDWR, S_IWUSR | S_IRUSR)) == -1)
                        {
                            perror("open");
                        }

                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        cmd[out] = NULL;
                    }
                    if (add)
                    {
                        int fd;

                        if ((fd = open(cmd[add], O_RDWR, S_IWUSR | S_IRUSR)) == -1)
                        {
                            perror("open");
                        }
                        lseek(fd, -1, SEEK_END);
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        cmd[add] = NULL;
                    }
                    
                    execvp(cmd[start], cmd + start);
                }
                else
                {
                    close(fd[0]);
                    close(fd[1]);
                    mywait(pid, &status, 0);
                    
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

        for (i = 0; i < pipesize; i++)
        {
            free(subcmd[i]);
        }
        free(subcmd);
    }
}

void newexec(char**cmd,int*p,int pipesize,int start,int head){
    // if(start){
    //     char buf[1000];
    //     read(fd0,buf,1000);
    //     printf("~~~~~~~~~~~~~~~~~~~~~~\n%s\n~~~~~~~~~~~~~~~~~~~~~~~~~\n",buf);
        
    // }
    if(head==pipesize){
        
        return;
    }
    char *subcmd = (char *)malloc(sizeof(char)*100);
    int count,i,status,fd[2];
    pid_t pid;
    strcpy(subcmd, "");
    for(i=start;i<p[head];i++){
        strcat(subcmd, cmd[i]);
        strcat(subcmd, " ");
    }
    //start=p[head];
    if(pipe(fd) == -1){
        perror("pipe");
    }
    pid=fork();
    if(pid==-1){
        perror("fork");
    }else if(pid==0){
        
        pid_t son=fork();
        if(son==-1){
            perror("fork");
        }else if(son==0){
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execvp(cmd[start],cutcmd(subcmd));
            printf("execvp error\n");
        }else{
            sleep(3);
            mywait(son,&status,0);
            printf("\nson = %d\n",son);
        }
    }else{
        mywait(pid,&status,0);
        
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        newexec(cmd,p,pipesize,p[head],head+1);
        dup2(STDIN_FILENO,fd[0]);
        dup2(STDOUT_FILENO,fd[1]);
        printf("\npid = %d\n",pid);
        fflush(stdout);
        free(subcmd);
    }

}