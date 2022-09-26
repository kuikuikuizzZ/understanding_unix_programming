#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define NUMARGS 20
#define ARGLEN 100 

char *makestring(char*);
void excute(char* arglist[]);

int main(int argc, char *argv[])
{ 
    int numargs=0;
    char buf[ARGLEN];
    char* arglist[NUMARGS];
    signal(SIGINT,SIG_IGN);
    while (numargs < NUMARGS)
    {
         printf("Args[%d]: \n",numargs);
        if ((fgets(buf,ARGLEN,stdin))&&*buf != '\n'){
            if (strcmp(buf,"quit\n")==0){
                exit(0);
            }
            arglist[numargs++]=makestring(buf);
        }else{
            arglist[numargs] = NULL;
            excute(arglist);
            numargs=0;
        }
    }
    
}

void excute(char* arglist[]){
    int pid = fork();
    int status;
    switch (pid){
    case -1:
        perror("fork failed");    
        exit(1);
    case 0: 
        signal(SIGINT,SIG_DFL);
        execvp(arglist[0],arglist);
        exit(1);
    default:
        wait(&status);
        printf("exit code %d, %d\n",status>>8,status&0x7F);
    }
    return;
}

char* makestring(char* in){
    printf("input %s,len %ld\n",in,strlen(in));
    char* buf = malloc(strlen(in)+1);
    in[strlen(in)-1] = '\0';
    strcpy(buf,in);
    return buf;
}