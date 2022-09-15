#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void do_ls(char*);
int cmp(const void *a, const void *b){
	return strcmp(*(char **)a, *(char **)b);//升序
//	return strcmp(*(char **)b, *(char **)a);//降序
}  
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
    int count =0;

    if ((dir=opendir(dirname))==NULL){
        perror("open dir error");
    } else{
        while((curr = readdir(dir)) != NULL){
            count++;
        }
    }
    char ** s = (char**) malloc(sizeof(char*)*count);
    printf("sorted:\n");
    seekdir(dir,0);
    int i = 0;
    while((curr = readdir(dir)) != NULL){
        s[i] = (char *)malloc(sizeof(char *));//分配空间 
        s[i] = curr->d_name;
        i++;
    }
    closedir(dir);

	qsort(s, count, sizeof(s[0]), cmp);
	for(int i=0;i<count;i++){
		printf("%s\n",s[i]);
	}
    return;
}