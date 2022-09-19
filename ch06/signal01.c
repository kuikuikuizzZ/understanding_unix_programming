#include<stdio.h>
#include<signal.h>
#include <unistd.h>

void f(int);

int main(int argc, char *argv[])
{  
    signal(SIGINT,SIG_IGN);
    for(int i=0;i<5;i++){
        printf("hello\n");
        sleep(1);
    } 

}  

void f(int signum){
    printf("signal num: %d",signum);
}