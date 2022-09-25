#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// int main(int argc, char *argv[])
// {   
//     void countdown(int);
//     int set_ticker(int);
//     signal(SIGALRM,countdown);
//     if(set_ticker(500)==-1){
//         perror("set timer error");
//         return 0;
//     }
//     while (1){
//         pause();
//     }
//     return 0;
// }

void countdown(int sig){
    static int num = 10;
    printf("countdown %d\n",num--);
    fflush(stdout);
    if (num<0){
        printf("Done");
        exit(0);
    }
}

int set_ticker(int n_msec)  {
    long n_sec = n_msec/1000;
    long n_usec = (n_msec%1000)*1000L;
    struct itimerval new_timeval;
    new_timeval.it_value.tv_sec = n_sec;
    new_timeval.it_value.tv_usec = n_usec;
    new_timeval.it_interval.tv_sec = n_sec;
    new_timeval.it_interval.tv_usec = n_usec;
    return setitimer(ITIMER_REAL,&new_timeval,NULL);
}