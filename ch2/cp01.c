#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define COPYMODE 0644
#define BUFFERSIZE 4096
void oops(char*,char*);
extern int errno;

int main(int argc, char *argv[])
{   
    if (argc != 3){
        fprintf(stderr,"usage: %s source destination\n", *argv);
        exit(1);
    }
    int sourcefd, destinationfd; 
    if ((sourcefd=open(argv[1],O_RDONLY))==-1){
        if (errno == ENOENT){
            fprintf(stderr,"there is no such file %s\n",argv[1]);
        }
        oops("Cannot open ",argv[1]);
        
    }
    if ((destinationfd = creat(argv[2],COPYMODE))==-1){
        oops("Cannot create ",argv[2]);
    }
    char buf[BUFFERSIZE];
    size_t nchars;
    while((nchars = read(sourcefd,buf,BUFFERSIZE))>0){
        if (write(destinationfd,buf,nchars)!=nchars){
            oops("write error to ",argv[2]);
        }
    }
    if (nchars == -1){
        oops("read error",argv[1]);
    }
    if (close(sourcefd)==-1 || close(destinationfd)==-1){
        oops("close error","");
    }
}

void oops(char* s1, char* s2){
    fprintf(stderr,"Error: %s",s1);
    perror(s2);
    exit(1);
}