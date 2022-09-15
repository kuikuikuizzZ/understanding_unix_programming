#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void do_ls(char*);
void do_stat(char*,char*);
void show_file_info(char*, struct stat*);
void mode_to_letter(int,char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

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
        if (strcmp(dirname, ".")==0){
            do_stat(s[i],"");
        } else{
            char dirname_clone[100]; 
            strcpy(dirname_clone, dirname);
            strcat(dirname_clone,"/");
            do_stat(s[i],dirname_clone);
        }
	}
    return;
}

void do_stat(char *filename,char* dirname){
    struct stat info;
    if (strcmp(filename,".")==0||strcmp(filename,"..")==0){
        return;
    }
    char* name = filename;
    if (strcmp(dirname,"")!=0){
        name = strcat(dirname,filename);
    }
    
    if (stat(name,&info)==-1){
        fprintf(stderr,"%s: stat error\n",filename);
    } else{
        show_file_info(filename,&info);
    }
}

void show_file_info(char* name, struct stat* info){
    char modestr[11];
    mode_to_letter(info->st_mode,modestr);
    printf("%s",modestr);
    printf("%4d ",(int)info->st_nlink);
    printf("%-8s",uid_to_name(info->st_uid));
    printf("%-8s",gid_to_name(info->st_gid));
    printf("%8ld",(long)info->st_size);
    printf("%.12s ",3+ctime(&info->st_mtim.tv_sec));
    printf("%s\n",name);
    return;
}



void mode_to_letter(int mode,char str[]){
    strcpy(str,"-----------");
    if(S_ISDIR(mode)) str[0]='d';
    if(S_ISCHR(mode)) str[0]='c';
    if(S_ISBLK(mode)) str[0]='b';

    if(mode&S_IRUSR)  str[1]='r';
    if(mode&S_IWUSR)  str[2]='w';
    if(mode&S_IXUSR)  str[3]='x';
    if(mode&S_IRGRP)  str[4]='r';
    if(mode&S_IWGRP)  str[5]='w';
    if(mode&S_IXGRP)  str[6]='x';
    if(mode&S_IROTH)  str[7]='r';
    if(mode&S_IWOTH)  str[8]='w';
    if(mode&S_IXOTH)  str[9]='x';
}

#include<pwd.h>
char *uid_to_name(uid_t uid){
    static char name[20];
    struct passwd* pw_ptr;
    if ((pw_ptr=getpwuid(uid))!=NULL){
        return pw_ptr->pw_name;
    } 
    sprintf(name,"%d",uid);
    return name;
}
#include <grp.h>
char *gid_to_name(gid_t gid){
    static char name[20];
    struct group* g_ptr;
    if ((g_ptr=getgrgid(gid))!=NULL){
        return g_ptr->gr_name;
    } 
    sprintf(name,"%d",gid);
    return name;
}