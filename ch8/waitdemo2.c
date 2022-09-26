#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define DELAY 5

void child(int delay );
void parent(int childpid);

int main(int argc, char *argv[]){
    int childpid;
    if((childpid=fork())==-1){
        perror("fork failed");
    }
    if (childpid == 0){
        child(DELAY);
    } else{
        parent(childpid);
    }
    return 0;
}

void child(int delay){
    printf("child: pid %d\n",getpid());
    sleep(delay);
    printf("finish child\n");
    exit(18);
}

void parent(int childpid){
    int status,waitpid;
    int high8,low7,bit7;
    waitpid = wait(&status);
    printf("parent pid: %d, child pid: %d,waiting %d\n",getpid(),childpid,waitpid);
    high8 = status >> 8;
    low7 = status & 0x7f;
    bit7 = status&0x80;
    printf("high 8 %d, low7 %d, bit7 %d\n", high8,low7,bit7);
    
}

