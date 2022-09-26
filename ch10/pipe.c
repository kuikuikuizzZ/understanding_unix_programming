#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define oops(m,x) {perror(m);exit(x);}


int main(int argc, char *argv[])
{ 
    if (argc != 3){
        oops("arg nums invalid" ,1);
    }
    int thepipe[2];
    int pid;
    if (pipe(thepipe)==-1){
        oops("pipe failed",2);
    }
    if ((pid = fork())==-1){
        oops("fork failed",3);
    } 
    if (pid == 0){
        close(thepipe[0]);
        if (dup2(thepipe[1],1)==-1){
            oops("dup failed",6)
        }
        // close(thepipe[1]);
        execlp(argv[1],argv[1],NULL);
        oops(argv[1],4);
    } else{
        close(thepipe[1]);
        if (dup2(thepipe[0],0)==-1){
            oops("dup failed",6)
        }        
        // close(thepipe[0]);
        execlp(argv[2],argv[2],NULL);
        oops(argv[2],5);
    }
}