#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define HOSTLEN 256
#define oops(msg) {perror(msg);exit(1);}

int make_internet_address();

int make_dgram_server_socket(int port){
    struct sockaddr_in saddr;
    char hostname[HOSTLEN];
    int sock_id;
    if((sock_id = socket(PF_INET,SOCK_DGRAM,0))<0){
        return -1;
    }
    gethostname(hostname,HOSTLEN);
    make_internet_address(hostname,port,&saddr);
    if (bind(sock_id,(struct sockaddr*) &saddr,sizeof(saddr))!=0){
        return -1;
    }
    return sock_id;
}

int make_dgram_client_socket(){
    return socket(PF_INET,SOCK_DGRAM,0);
}

int make_internet_address(char* hostname,int port, struct sockaddr_in* saddr){
    struct hostent * hp;
    bzero((void*)saddr,sizeof(struct sockaddr_in));
    if ((hp = gethostbyname(hostname))==NULL){
        return -1;
    }
    
    bcopy((void*)hp->h_addr,(void*)&saddr->sin_addr,hp->h_length);
    saddr->sin_port = htons(port);
    saddr->sin_family = AF_INET;
    return 0;
}

int get_internet_address(char* host, int len,int *port, struct sockaddr_in* saddr){
    strncpy(host,inet_ntoa(saddr->sin_addr),len);
    *port = ntohs(saddr->sin_port);
    return 0;
}