#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[])
{   
    FILE *fp;
    char msg[]="hello\n";
    char msg2[] = "test\n";
    if ( (fp = fopen("testfile2","w"))==NULL){
        return 0;
    }
    fprintf(fp,"%s",msg);
    fflush(fp);
    if (fork()==-1){
        return 0;
    }
    fprintf(fp,"%s",msg2);
    fclose(fp);
    return 0;
}