#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <time.h>

void show_info(struct utmp *record);
void show_time(long t);
struct utmp * utmp_next();
void utmp_close();
void utmp_open();
int main(int argc, char *argv[])
{   
    struct utmp *current_record;
    utmp_open();
    while ((current_record = utmp_next())!= (struct utmp*)NULL){
        if (current_record->ut_type != USER_PROCESS){
            continue;
        }
        show_info(current_record);
    }
    utmp_close();
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