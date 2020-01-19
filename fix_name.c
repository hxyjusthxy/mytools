#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#define TARGET_STRING "fuckyou"
#define PATH_MAX_LENGTH 500
#if 0
void list_dir_all_file(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(name)))return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR){
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            list_dir_all_file(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        
        }
    }
    closedir(dir);
}
#endif
int file_get_newname(char *old_name,const char *target_str,int pos, char* new_name)
{
    int ret=0;
    int target_str_length = 0;
    target_str_length = strlen( target_str );
    //printf("target_str_name length = %d,pos =%d\n",target_str_length,pos);
    memcpy(new_name,old_name,strlen(old_name)+1);
    //printf("new_name111111 = %s\n",new_name);
    strcpy(new_name+pos,new_name+pos+target_str_length);
    printf("new_name222222 =%s\n",new_name);
    ret = rename(old_name,new_name);
    return 0;
}
void list_current_file_process_file_name(const char *dir_ab_path,const char *target_str)
{
    DIR *dir;
    struct dirent *entry;
    char *str_pos=0;
    int ret=0;
    char new_name[PATH_MAX_LENGTH]={0};
    char old_name[PATH_MAX_LENGTH]={0};
    if (!(dir = opendir(dir_ab_path))){
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;    
        }
        memcpy(old_name,dir_ab_path,strlen(dir_ab_path)+1);
        //printf("old_name00000000000000 =%s\n",old_name);
        strcat(old_name,"/");
        strcat(old_name,entry->d_name);
        //printf("old_name11111111111111 =%s\n",old_name);
        str_pos = strstr(old_name,target_str);
        if (str_pos != NULL){
            printf("the file old_name 22222222222 to fix :%s--\n",old_name);
            strcpy(old_name,dir_ab_path);
            strcat(old_name,"/");
            strcat(old_name,entry->d_name);
            printf("Process old file Path:%s,(str_pos - old_name)=%ld\n",old_name,str_pos-old_name);

            file_get_newname(old_name,target_str,str_pos-old_name,new_name);
        }
    }
    printf("close the directory!\n");
    closedir(dir);
}
int main(void) {
    char path[PATH_MAX_LENGTH]={0};
    char *path_ret=NULL;
    path_ret = getcwd(path, sizeof(path)/sizeof(char));
    if (path_ret == NULL){
        printf("get the execute directory error!");
        return -1;
    }
    printf("EXECTE Path = %s\n",path);

    list_current_file_process_file_name(path, TARGET_STRING);
    
    return 0;
}