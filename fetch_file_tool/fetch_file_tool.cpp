#include "fetch_file_tool.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include<sys/stat.h>
//#define SRC_FILE_PATH "/home/xyhu/source_factory/mytools/fetch_file_tool/test_sample/pps/test1"
#define SRC_FILE_PATH "/home/xyhu/source"
#define DEST_FILE_PATH "/home/xyhu/source_factory/mytools/fetch_file_tool/out"

#define ABSOLUTE_PATH
#ifdef ABSOLUTE_PATH
#define SVN_BASE_PATH  "/home/xyhu/source_factory/mytools/fetch_file_tool/test_sample/svn_base"
#define DEST_BASE_PATH "/home/xyhu/source_factory/mytools/fetch_file_tool/test_sample/dest_base"
#else
#define SVN_BASE_PATH  "./test_sample/svn_base"
#define DEST_BASE_PATH  "./test_sample/dest_base"
#endif
#define ORPHAN_FILE_LIST "/home/xyhu/source_factory/mytools/fetch_file_tool/out/organ_file_list.txt"
#if 0
CFetchFile::CFetchFile(char *src_file_path, char *dest_dir_path)
:m_src_file_path(src_file_path),m_dest_dir_path(dest_dir_path){
    printf("input the src file path = %s\n",m_src_file_path );


    
    printf("input the dest file path = %s\n",m_dest_dir_path );
}
#endif
CFetchFile::CFetchFile(char *svn_base_path,char *dest_base_path,char *orphan_file_path)
:m_svn_base_path(svn_base_path),
 m_dest_base_path(dest_base_path),
 m_orphan_file_path(orphan_file_path),
 m_src_dir_path(NULL)
{
    printf("input dest_base_path = %s\n",m_dest_base_path);
    printf("input svn base path=%s\n",m_svn_base_path);
}
CFetchFile::~CFetchFile(){
    if (m_src_dir_path!=NULL){
        free(m_src_dir_path);
    }
    
}
int CFetchFile::GetOrphanFileList(){
    /*
    Input:
        1.svn_base_dir  
        2.dest_dir      
        3.file_path
    Output:
        file with a orphan file list
    */
   int ret=0;
   if (!m_svn_base_path) return -1;
   if (!m_dest_base_path) return -1;
   if (!m_orphan_file_path) return -1;

   ret = ProcessOrphanFileList(m_dest_base_path);
   return 0;
    
}
int CFetchFile::ProcessOrphanFileList(char *name){
    DIR *dir;
    struct dirent *entry;
    char new_path[1024];
    char file_path[1024];
    if (!(dir = opendir(name))){
        printf("can't open dir:%s\n",name);
        return -1;
    }
    while((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
        }else if (entry->d_type == DT_DIR){
            snprintf(new_path, sizeof(new_path), "%s/%s", name, entry->d_name);
            ProcessOrphanFileList(new_path);
        }else{
            snprintf(file_path, sizeof(file_path), "%s/%s", name, entry->d_name);
            //printf("dest_base_file:%s\n",file_path);
            if(access_file(file_path) == false){
                printf("find orphan file:%s\n",file_path);
                process_svn_base_dir(file_path);
                //Here the svn_base dir include the dest_base_dir,then copy file 
                

            }
            
        }

    }
    
}
void CFetchFile::process_svn_base_dir(char *file_path){
    char *different_part =NULL;
    int length_different_part=0;
    int i=0;
    char different_dir_part[1024];
    char new_svn_dir_path[1024];
    char new_svn_file_path[1024];
    //different part
    different_part = file_path + strlen(m_dest_base_path)+1;
    length_different_part = strlen(different_part);
    //printf("different_part = %s,length =%d \n",different_part,length_different_part);
    
    
    //different dir
    int different_dir_length = strrchr(different_part,'/') - different_part;
    //printf("different_dir_length = %d\n",different_dir_length);
    memcpy(different_dir_part, different_part,different_dir_length);
    different_dir_part[different_dir_length]='\0';
    //printf("different_dir_part = %s\n",different_dir_part);
    
    //to make dir 
    sprintf(new_svn_dir_path,"%s/%s",m_svn_base_path,different_dir_part);
    printf("we need to create:%s\n",new_svn_dir_path);
    mkdir(new_svn_dir_path,0777);
    
    //copy file
    sprintf(new_svn_file_path,"%s/%s",new_svn_dir_path,different_part+different_dir_length+1);
    printf("new file path:%s\n",new_svn_file_path);
    copyFile(file_path,new_svn_file_path);
   
    
    
}
int CFetchFile::copyFile(const char* src, const char* des)
{
	int nRet = 0;
	FILE* pSrc = NULL, *pDes = NULL;
	pSrc = fopen(src, "r");
	pDes = fopen(des, "w+");
 
 
	if (pSrc && pDes)
	{
		int nLen = 0;
		char szBuf[1024] = {0};
		while((nLen = fread(szBuf, 1, sizeof szBuf, pSrc)) > 0)
		{
			fwrite(szBuf, 1, nLen, pDes);
		}
	}
	else
		nRet = -1;
 
 
	if (pSrc)
		fclose(pSrc), pSrc = NULL;
 
 
	if (pDes)
		fclose(pDes), pDes = NULL;
 
 
	return nRet;
}

bool CFetchFile::access_file(char *file_path){
    if(file_path ==NULL) return false;
    char check_file_path[1024];
    if (access(file_path,F_OK)){
        printf("%s  unreachable!\n",file_path);
        return false;
    }
    if (m_svn_base_path[0] =='.' ){
        printf("relative path\n");
    }else{
        //printf("absolute path\n");
        sprintf(check_file_path,"%s/%s",m_svn_base_path,file_path + strlen(m_dest_base_path));
        //printf("check file :%s\n",check_file_path);
        if (!access(check_file_path,F_OK)){
            return true;
        }else{
            return false;
        }
        
    }
    
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
    CFetchFile fetch_file_instance(SVN_BASE_PATH,DEST_BASE_PATH,ORPHAN_FILE_LIST);
    fetch_file_instance.GetOrphanFileList();
    return 0;
}