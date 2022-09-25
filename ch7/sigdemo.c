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
    signal(SIGINT,interrupt_handler);
    signal(SIGQUIT,quit_handler);
    char quit[INPUTLENGTH]="quit\n";
    do {
        int n = read(0,input,INPUTLENGTH);
        if (n == -1){
            perror("read error");
        } else{
            input[n]  = '\0';
            printf("you type: %s \n",input);
        }
        
    }while(strcmp(input,"quit\n")!=0);
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