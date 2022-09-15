#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <time.h>

void show_info(struct utmp *record);

int main(int argc, char *argv[])
{   
    int utmp_fd;
    if ((utmp_fd = open(UTMP_FILE,O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(1);
    }
    struct utmp current_record;
    size_t reclen = sizeof(current_record); 
    while(read(utmp_fd,&current_record,reclen)==reclen){
        if (current_record.ut_type != USER_PROCESS){
            continue;
        }
        show_info(&current_record);
    }
    close(utmp_fd);
    return 0;
}

void show_info(struct  utmp *record)
{
    printf("% - 8.8s",record->ut_user);
    printf(" ");
    printf("% - 8.8s",record->ut_line);
    printf(" ");
    show_time(record->ut_tv.tv_sec);
    printf(" ");
    printf("%s",record->ut_host);
    printf("\n");
}

void show_time(long t){
    printf(" %s",ctime(&t));
}