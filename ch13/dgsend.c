#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "dgram.c"
#define oops(msg) {perror(msg);exit(1);}


int make_dgram_client_socket();
int make_internet_address(char* ,int,struct sockaddr_in*);

int main(int argc, char *argv[])
{ 
    int sock,msglen;
    struct sockaddr_in saddr;
    
    if ((msglen=strlen(argv[3])) <=0){
        oops("message should not empty");
    }
    if (argc != 4){
        fprintf(stderr,"usage: dgsend host port 'message'\n");
        exit(1);
    }
    if ((sock = make_dgram_client_socket())<0){
        oops("make client sock failed");
    }
    if (make_internet_address(argv[1],atoi(argv[2]),&saddr)==-1){
        oops("make inter address failed");
    }
    
    if (sendto(sock,argv[3],msglen,0,(struct sockaddr*)&saddr,sizeof(saddr))==-1){
        oops("sendto failed")
    }
    return 0;
}