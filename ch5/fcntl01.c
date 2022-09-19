#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{ 
    if (argc != 2){
        fprintf(stderr,"args should be 2");
        exit(1);
    }
    int fd,val;
    if ((fd = open(argv[1],O_RDWR))==-1){
        perror("open error");
    }

    if ((val=fcntl(fd,F_GETFL,0))<0){
        perror("fcntl error");
    }
    switch (val&O_ACCMODE)
    {
    case O_APPEND:
        printf("O_APPEND");
        break;
    default:
        printf("output mode %d\n",val&O_ACCMODE);
        break;
    }
}