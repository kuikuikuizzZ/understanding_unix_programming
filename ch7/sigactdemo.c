#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define INPUTLENGTH 100

int main(int argc, char *argv[])
{ 
    void interrupt_handler(int);
    void quit_handler(int);
    char input[INPUTLENGTH];
    sigset_t blocked;
    struct sigaction newhandler;

    newhandler.sa_handler = interrupt_handler;
    newhandler.sa_flags = SA_NODEFER|SA_RESTART; // 允许递归调用
    sigemptyset(&blocked);
    sigaddset(&blocked,SIGQUIT);
    newhandler.sa_mask=blocked;

    if(sigaction(SIGINT,&newhandler,NULL)==-1){
        perror("sigaction error");
    } else{
        while (strcmp(input,"quit\n")!=0)
        {
            fgets(input,INPUTLENGTH,stdin);
            printf("input: %s",input);
        }
        
    }
    return 0;
}

void interrupt_handler(int sig){
    printf("interrupt %d\n",sig);
    sleep(2);
    printf("leaving interrupt %d\n",sig);
}

void quit_handler(int sig){
    printf("quit %d\n",sig);
    sleep(3);
    printf("leaving quit %d\n",sig);
}