#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <stdlib.h>
#include <sys/types.h>

#define NRECS 16
#define UTMPSIZE (sizeof(struct utmp))
#define NULLUT ((struct utmp*)NULL)

static char utmpbuf[NRECS*UTMPSIZE];
static int num_recs, current_rec;
static int utfd = -1;

void utmp_open(){
    utfd = open(UTMP_FILE,O_RDONLY);
    current_rec = num_recs= 0;
}

void utmp_close(){
    if (utfd != -1){
        close(utfd);
    } 
}

int utmp_reload(){
    int readbuf;
    if((readbuf = read(utfd,utmpbuf,NRECS*UTMPSIZE))==-1){
        perror("read error");
    }
    num_recs = readbuf/UTMPSIZE;
    current_rec = 0;
    return num_recs;
}

struct utmp * utmp_next(){
    struct utmp *recp;
    if (utfd == -1){
        return NULLUT;
    }
    if (current_rec == num_recs && utmp_reload()==0){
        return NULLUT;
    }
    recp = (struct utmp*)&utmpbuf[current_rec*UTMPSIZE];
    current_rec++;
    return recp;
}
