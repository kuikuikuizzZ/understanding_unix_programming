#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 128

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t,char *,int);



int main(int argc, char *argv[])
{ 
    printpathto(get_inode("."));
    printf("\n");
    return 0;
}

void printpathto(ino_t this_node){

    if (get_inode("..") != this_node ){
        chdir("..");
        char name[BUFFERSIZE];
        inum_to_name(this_node,name,BUFFERSIZE);
        ino_t node = get_inode(".");
        printpathto(node);
        printf("/%s",name);
    }
}

void inum_to_name(ino_t this_node,char* target,int size){
    DIR * dir;
    struct dirent * curr;
    int count =0;

    if ((dir=opendir("."))==NULL){
        perror("open dir error");
        exit(1);
    } else{
        while((curr = readdir(dir)) != NULL){
            if (curr->d_ino == this_node ){
                strcpy(target,curr->d_name);
                closedir(dir);
                return;
            } 
        }
    }
    fprintf(stderr,"error looking for inum %ld\n",this_node);
    exit(1);
}

ino_t get_inode(char* path){
    struct stat info;
    if( stat(path,&info)==-1){
        perror("stat error");
        exit(1);
    }
    return info.st_ino;
}