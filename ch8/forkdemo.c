#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("before fork, pid: %d, \n",getpid());
    // fflush(stdout);
    sleep(1);
    fork();
    fork();
    fork();
    printf("after fork, pid: %d, ppid %d\n",getpid(),getppid());
}