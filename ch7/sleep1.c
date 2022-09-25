#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void wakeup(int);


int main(int argc, char *argv[])
{   
    void* fn = signal(SIGTSTP,wakeup);
    printf("before pause,function %p \n ",fn);
    alarm(3);
    pause();
    printf("after pause,function %p \n ",fn);
}

void wakeup(int s){
    printf("wake up\n");
}