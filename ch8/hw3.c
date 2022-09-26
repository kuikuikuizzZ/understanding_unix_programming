#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[])
{   
    int i;
    if(fork()!=0){
        exit(0);
    }
    for (i=1;i<10;i++){
        printf("still here \n");
        sleep(1);
    }
    return 0;
}