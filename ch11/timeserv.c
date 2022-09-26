#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include<stdlib.h>

#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg);exit(1);}

int main(int argc, char *argv[])
{ 
    struct sockaddr_in saddr;
    struct hostent * hp;
    char hostname[HOSTLEN];
    int sockid, sock_fd;
    FILE * sock_fp;
    char *ctime();
    time_t thetime;

    sockid = socket(PF_INET,SOCK_STREAM,0);
    if (sockid == -1){
        oops("socket failed");
    }
    bzero((void *)&saddr,sizeof(saddr));
    gethostname(hostname,HOSTLEN);
    hp = gethostbyname(hostname);
    bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;
    printf("hostname %s,sin_addr %s\n",hostname,hp->h_addr);
    if (bind(sockid,(struct sockaddr *)&saddr,sizeof(saddr))!=0){
        oops("bind");
    }
    if(listen(sockid,10) != 0){
        oops("listen");
    }
    while (1)
    {
        printf("server ready\n");
        fflush(stdout);
        sock_fd = accept(sockid,NULL,NULL); // 为啥不需要 saddr?
        if (sock_fd == -1){
            oops("accept failed");
        }
        sock_fp = fdopen(sock_fd,"w");
        if (sock_fp==NULL){
            oops("fdopen failed");
        }
        thetime = time(NULL);
        fprintf(sock_fp,"the time is ..");
        fprintf(sock_fp,"%s",ctime(&thetime));
        fclose(sock_fp);
    }
}
