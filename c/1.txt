#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

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

int main(void)
{
    int fd;
    fd=open("temp",O_RDWR|O_CREAT,S_IWUSR|S_IRUSR);
    if(fd==-1){
        fprintf(stderr,"error open\n");
        return 0;    
    }char*buf=(char*)malloc(1000);


    read(fd,buf,1000);
        printf("~~%s~~\n",buf);

    return 0;
} 


void swap(int fd0,int fd1){
    int size=4096;
    char*buf1=(char*)malloc(size);
    char*buf2=(char*)malloc(size);
    memset(buf1,'\0',size);
    memset(buf2,'\0',size);
    read(fd0,buf1,size);
    read(fd1,buf2,size);
    write(fd0,buf2,size);
    write(fd1,buf1,size);
    printf("%s\n",buf1);
    printf("%s\n",buf2);
}

// void piexec1(char **cmd, int *p, int pipesize)
// {
//     char **subcmd = (char **)malloc(sizeof(char *) * pipesize);
//     int start = 0, i = 0, status;
//     pid_t ppid;

//     for (i = 0; i < pipesize; i++)
//     {
//         subcmd[i] = (char *)malloc(sizeof(char) * 100);
//         strcpy(subcmd[i], "");
//         for (int j = start; j < p[i]; j++)
//         {
//             if(cmd[j]){
//                 strcat(subcmd[i], cmd[j]);
//                 strcat(subcmd[i], " ");
//             }
            
//         }
//         start = p[i];
//     }

//     ppid = fork();
//     if (ppid == -1)
//     {
//         perror("fork");
//     }
//     else if (ppid == 0)
//     {
//         pid_t pid;
//         int fd[2];
//         if ((fd[0] = open("fd0", O_RDWR|O_CREAT, S_IWUSR | S_IRUSR)) == -1)
//         {
//             fprintf(stderr,"error open\n");
//             exit(1);
//         }
//         if ((fd[1] = open("fd1", O_RDWR|O_CREAT, S_IWUSR | S_IRUSR)) == -1)
//         {
//             fprintf(stderr,"error open\n");
//             exit(1);
//         }
        
//         for (i = 0; i <= pipesize; i++)
//         {
//             if (i == 0)
//             {
//                 if ((pid = fork()) == -1)
//                 {
//                     perror("fork");
//                 }
//                 else if (pid == 0)
//                 {
//                     dup2(fd[1], STDOUT_FILENO);
                    
//                     char **tmp = cutcmd(subcmd[i]);
//                     execvp(cmd[0], tmp);
//                 }
//                 else
//                 {
//                     mywait(pid, &status, 0);
//                     swap(fd[0],fd[1]);
//                 }
//             }
//             else if (i < pipesize)
//             {
//                 if ((pid = fork()) == -1)
//                 {
//                     perror("fork");
//                 }
//                 else if (pid == 0)
//                 {
//                     dup2(fd[0], STDIN_FILENO);
//                     dup2(fd[1], STDOUT_FILENO);
//                     // close(fd[0]);
//                     // close(fd[1]);
//                     execvp(cmd[p[i]], cutcmd(subcmd[i]));
//                 }
//                 else
//                 {
//                     mywait(pid, &status, 0);
//                     swap(fd[0],fd[1]);
//                 }
//             }
//             else
//             {
//                 if ((pid = fork()) == -1)
//                 {
//                     perror("fork");
//                 }
//                 else if (pid == 0)
//                 {
//                     int res = dup2(fd[0], STDIN_FILENO);
//                     if (res == -1)
//                     {
//                         fprintf(stderr, "error dup2\n");
//                         exit(1);
//                     }
//                         // close(fd[1]);
//                         // close(fd[0]);
//                     if (out)
//                     {
//                         int fd;
//                         if ((fd = open(cmd[out], O_RDWR|O_CREAT|O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
//                         {
//                             perror("open");
//                         }

//                         dup2(fd, STDOUT_FILENO);
//                         close(fd);
//                         cmd[out] = NULL;
//                     }
//                     if (add)
//                     {
//                         int fd;

//                         if ((fd = open(cmd[add], O_RDWR|O_CREAT, S_IWUSR | S_IRUSR)) == -1)
//                         {
//                             perror("open");
//                         }
//                         lseek(fd, -1, SEEK_END);
//                         dup2(fd, STDOUT_FILENO);
//                         close(fd);
//                         cmd[add] = NULL;
//                     }
                    
//                     execvp(cmd[start], cmd + start);
//                 }
//                 else
//                 {
//                     mywait(pid, &status, 0);
//                     close(fd[0]);
//                     close(fd[1]);
//                 }
//             }
//         }
//     }
//     else if (ppid > 0)
//     {
//         if (!bg)
//         {
//             mywait(ppid, &status, 0);
//         }

//         for (i = 0; i < pipesize; i++)
//         {
//             free(subcmd[i]);
//         }
//         free(subcmd);
//     }
// }

// void newexec(char**cmd,int*p,int pipesize,int start,int head){
//     // if(start){
//     //     char buf[1000];
//     //     read(fd0,buf,1000);
//     //     printf("~~~~~~~~~~~~~~~~~~~~~~\n%s\n~~~~~~~~~~~~~~~~~~~~~~~~~\n",buf);
        
//     // }
//     if(head==pipesize){
        
//         return;
//     }
//     char *subcmd = (char *)malloc(sizeof(char)*100);
//     int count,i,status,fd[2];
//     pid_t pid;
//     strcpy(subcmd, "");
//     for(i=start;i<p[head];i++){
//         strcat(subcmd, cmd[i]);
//         strcat(subcmd, " ");
//     }
//     //start=p[head];
//     if(pipe(fd) == -1){
//         perror("pipe");
//     }
//     pid=fork();
//     if(pid==-1){
//         perror("fork");
//     }else if(pid==0){
        
//         pid_t son=fork();
//         if(son==-1){
//             perror("fork");
//         }else if(son==0){
//             int sfd0,sfd1;
//             sfd0=dup(STDIN_FILENO);
//             sfd1=dup(STDOUT_FILENO);
//             dup2(fd[0],STDIN_FILENO);
//             close(fd[0]);
//             dup2(fd[1],STDOUT_FILENO);
//             close(fd[1]);
//             newexec(cmd,p,pipesize,p[head],head+1);
//             dup2(STDIN_FILENO,sfd0);
//             dup2(STDOUT_FILENO,sfd1);
//             //execvp(cmd[start],cutcmd(subcmd));
//             printf("execvp error\n");
//         }else{
//             mywait(son,&status,0);
//             printf("\nson = %d\n",son);
//         }
//     }else{
//         mywait(pid,&status,0);
        
//         close(fd[1]);
//         close(fd[0]);
        
//         printf("\npid = %d\n",pid);
//         //fflush(stdout);
//         free(subcmd);
//     }

// }
