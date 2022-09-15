#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char*);

int main(int argc, char *argv[])
{ 
    if (argc == 1){
        do_ls(".");
    } else {
        while(--argc!=0){
            printf("%s: \n",*++argv);
            do_ls(*argv);
        }
    }
    return 0;
}

void do_ls(char* dirname){
    DIR * dir;
    struct dirent * curr;
    if ((dir=opendir(dirname))==NULL){
        perror("open dir error");
    } else{
        while((curr = readdir(dir)) != NULL){
        printf("%s\n",curr->d_name);
        }
        closedir(dir);
    }
    return;
}