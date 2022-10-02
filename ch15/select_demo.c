#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#define oops(msg,x) {perror(msg);exit(x);}

void show_data(char*,int);

int main(int argc, char *argv[])
{ 
    int fd1,fd2;
    struct timeval timeout;
    fd_set readfds;
    int maxfd;
    int retval;

    if (argc != 4){
        fprintf(stderr,"usage: select_demo file1, file2 timeout");
        exit(1);
    }
    if ((fd1=open(argv[1],O_RDONLY))==-1){
        oops(argv[1],2);
    }
    if ((fd2=open(argv[2],O_RDONLY))==-1){
        oops(argv[2],2);
    }
    maxfd = 1+(fd1>fd2?fd1:fd2);

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd1,&readfds);
        FD_SET(fd2,&readfds);

        timeout.tv_sec = atoi(argv[3]);
        timeout.tv_usec = 0;

        retval = select(maxfd,&readfds,NULL,NULL,&timeout);
        if (retval == -1){
            oops("select failed",3);
        } 
        if (retval > 0){
            if(FD_ISSET(fd1,&readfds)){
                show_data(argv[1],fd1);
            }
            if (FD_ISSET(fd2,&readfds)){
                show_data(argv[2],fd2);
            }
        }else{
            printf("no input after %s seconds\n",argv[3]);
            fflush(stdout);
        }
    }
    return 0;
}

void show_data(char* name,int fd){
    char buf[BUFSIZ];
    int n ;
    
    printf("%s: %d ",name,n);
    fflush(stdout);
    if ((n=read(fd,buf,BUFSIZ))>0){
        write(1,buf,n);
        write(1,"\n",1);
    }else{
        oops(name,4);
    }
}