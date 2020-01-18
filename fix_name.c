#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
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
void list_current_file_process_file_name(const char *name, int indent,const char *fix_str)
{
    DIR *dir;
    struct dirent *entry;
    char *str_pos=0;
    int ret=0;
    if (!(dir = opendir(name)))return;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;    
        //printf("%s\n", , entry->d_name);
        str_pos = strstr(entry->d_name,fix_str);
        if (str_pos != NULL){
            printf("the file to fix :%s--\n",entry->d_name);
            ret = rename(const char *oldname, const char *newname);
        }
    }
    printf("close the directory!\n");
    closedir(dir);
}
int main(void) {
    list_current_file_process_file_name(".", 0,"fuckyou");
    return 0;
}