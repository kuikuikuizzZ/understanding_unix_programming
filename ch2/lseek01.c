#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{  
    if (argc != 2){
        fprintf(stderr,"need 1 args");
        exit(1);
    }
    int fd = open(argv[1],O_RDWR);
    if(lseek(fd,200,SEEK_END)==-1){
        fprintf(stderr,"lseek error");
        exit(1);
    }
    char* buf;
    if (read(fd,buf,10) == -1){
        fprintf(stderr,"lseek error");
        exit(1);
    }
    printf("buf %s",buf);
    buf = "11111111";
    if (write(fd,buf,10) == -1){
        fprintf(stderr,"write error");
        exit(1);
    }
     
    return 0;
}