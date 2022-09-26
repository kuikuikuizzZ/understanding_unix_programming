#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORTNUM 13000
#define oops(msg) {perror(msg);exit(1);}

int main(int argc, char *argv[])
{ 
    struct sockaddr_in saddr;
    struct hostent * hp;
    int sockid, sock_fd;
    char message[BUFSIZ];
    int messlen;

    sockid = socket(PF_INET,SOCK_STREAM,0);
    if (sockid == -1){
        oops("socket failed");
    }
    if (argc != 2){
        oops("argument must 2");
    }
    hp = gethostbyname(argv[1]);
    if (hp == NULL){
        oops("get host failed");
    }
    bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;
    printf("hostname %s,sin_addr %s\n",hp->h_name,hp->h_addr);
    if (connect(sockid,(struct sockaddr *)&saddr,sizeof(saddr))!=0){
        oops("connect");
    }

    messlen = read(sockid,message,BUFSIZ);
    if (messlen == -1){
        oops("read");
    }
    if(write(1,message,messlen) != messlen){
        oops("write");
    }
    close(sockid);
}