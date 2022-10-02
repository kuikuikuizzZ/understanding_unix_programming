#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "dgram.c"


#define oops(msg) {perror(msg);exit(1);}

int make_dgram_server_socket(int);
int get_internet_address(char* ,int,int *,struct sockaddr_in*);
void say_who_called(struct sockaddr_in*);


int main(int argc, char *argv[])
{ 
    int port = atoi(argv[1]);
    int sock_id;
    char buf[BUFSIZ];
    size_t msglen;
    struct sockaddr_in saddr;
    socklen_t saddrlen;
    if (argc != 2 || port<0){
        fprintf(stderr,"usage: dgrecv portnumber\n");
        exit(1);
    }
    if ((sock_id = make_dgram_server_socket(port))==-1){
        oops("server socket failed")
    }
    saddrlen = sizeof(saddr);
    while ((msglen=recvfrom(sock_id,buf,BUFSIZ,0,(struct sockaddr *) &saddr,&saddrlen))>0)
    {
        buf[msglen]='\0';
        printf("dgrecv: %s\n",buf);
        say_who_called(&saddr);
    }
    return 0;
}

void say_who_called(struct sockaddr_in* saddr){
    char host[BUFSIZ];
    int port;
    get_internet_address(host,BUFSIZ,&port,saddr);
    printf("from %s:%d\n",host,port);
    return;
}
