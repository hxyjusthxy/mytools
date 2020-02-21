#include "fetch_file_tool.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#define SRC_FILE_PATH "/home/xyhu/source_factory/mytools/fetch_file_tool/test_sample/pps/test1"
#define SRC_FILE_PATH "/home/xyhu/source"
#define DEST_FILE_PATH "/home/xyhu/source_factory/mytools/fetch_file_tool/out"
CFetchFile::CFetchFile(char *src_file_path, char *dest_dir_path)
:m_src_file_path(src_file_path),m_dest_dir_path(dest_dir_path){
    printf("input the src file path = %s\n",m_src_file_path );
    printf("input the dest file path = %s\n",m_dest_dir_path );
}
CFetchFile::CFetchFile(char *src_file_list){

}
CFetchFile::~CFetchFile(){

}
int CFetchFile::DoIt(void){
    int ret=0;
    if (!m_src_file_path){
        printf("src file path NULL!\n");
        return -1;
    }
    ret = GetFileDirPath(m_src_file_path,m_src_dir_path);
    if (ret){
        printf("split_file_path error,ret =%d\n",ret);
    }

    ret = split_file_path(m_src_dir_path, m_src_dir_array);
    if (ret){
        printf("split file path error =ret =%d\n",ret);
    }

    //Get m_dest_file_path;

    ret = CopyFile(m_src_file_path,m_dest_file_path);
    if (ret){
        printf("Copy file error\n");
    }
    return ret;
}
int CFetchFile::GetFileDirPath(char *src_file_path, char *src_file_dir_path){
    int ret=0;
    char *index_pos=NULL;
    int dir_path_mem_length=0;
    if (!src_file_path) return -1;
    index_pos = strrchr(src_file_path,'/');
    dir_path_mem_length = index_pos-src_file_path+2;//include '\0'
    printf("src path length = %d--pos = %d\n",strlen(src_file_path)+1,index_pos);
    src_file_dir_path = (char *)malloc(dir_path_mem_length);
    if (!src_file_dir_path) return -2;
    memcpy(src_file_dir_path,src_file_path,dir_path_mem_length-1);
    printf("src_file_dir_path = %s\n",src_file_dir_path);
    //*****
    ret = split_file_path(src_file_path,m_src_dir_array);

    return 0;
}
int CFetchFile::split_file_path(char *src_file_path,char ** src_dir_array){
    int first_index=0;
    int second_index=0;
    int i=0;
    int k=0;
    int dir_mem_length=0;
    int dir_index=0;
    char temp[100];
    while(i<strlen(src_file_path)){
        if (src_file_path[i]=='/'){
            first_index = i;
            printf("first_index = %d\n",first_index);
            for (k=i+1;k<strlen(src_file_path);k++){
                if (src_file_path[k]=='/'){
                    second_index=k;
                    printf("second_index = %d\n",second_index);
                    break;
                }
            }
            if (k==strlen(src_file_path)) break;
            dir_mem_length = second_index - first_index;
            printf("==> dir mem length = %d\n",dir_mem_length);
            memcpy(temp,src_file_path+first_index+1,dir_mem_length-1);
            printf("==>dir name = %s\n",temp);
            i = second_index;
            sleep(1);
        }    
        
    }
    printf("out\n");
    return 0;
}
int CFetchFile::DirCreate(char *src_dir_path, char *dest_path){
    if (!src_dir_path) return -1;
    //add directory
    //create directory
    return 0;
}

int CFetchFile::CopyFile(char *src_file_path,char *dest_file_path){
    return 0;
}

int main(int argc , char **argv) {
    int i=0;
    char c;
    int ret;
    for (i=0;i<argc;i++){
        printf("input [%d]-%s-\n",argc, argv[i]);
    }
    //process input option
    while ((c = getopt(argc, argv, ":h")) != -1) {
        switch (c){
            case 'h':
                {
                    cout <<"****show this table START***"<<endl;
                    cout << "copy file from SRC_ROOT_PATH to DEST_PATH andr create the corrding directory in the path" <<endl;
                    cout << "[usage]:file_fetch_tool ROOT_PATH SRC_ROOT_PATH, DEST_PATH" <<endl;
                    cout << "[usage]:file_fetch_tool -l ROOT_PATH SRC_ROOT_PATH, DEST_PATH" <<endl;
                    cout << "****show this table END***" <<endl;
                    break;
                }
            case 'l':
                {
                    
                }
            default:
            {
                break;
            }
        }
    }
    CFetchFile fetch_file_instance(SRC_FILE_PATH,DEST_FILE_PATH);
    fetch_file_instance.DoIt();
    return 0;
}