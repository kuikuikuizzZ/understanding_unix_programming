#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[])
{   
    int fd,pid;
    char msg[]="hello\n";
    char msg2[] = "test\n";
    if ( (fd = creat("testfile",0644))==-1){
        return 0;
    }
    if ((write(fd,msg,strlen(msg))==-1)){
        return 0;
    }
    if (fork()==-1){
        return 0;
    }
    if (write(fd,msg2,strlen(msg2))==-1){
        return 0;
    }
    close(fd);
    return 0;
}