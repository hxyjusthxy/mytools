#ifndef __FETCH_FILE_TOOL_H__
#define __FETCH_FILE_TOOL_H__
#include <string>
#include <iostream>
using namespace std;
struct list{
    unsgined int *next;            
    unsgined int *pre;
    unsgined int *pre;
}
class CFetchFile{
    public:
        CFetchFile(char *src_file_path,char *dest_file_path);
        CFetchFile(char *src_file_list);
        ~CFetchFile(void);
         int DoIt(void);
        
    private:
       
        int GetFileDirPath(char *src_file_path, char *src_file_dir_path);
        int split_file_path(char *src_file_path,char ** src_dir_array);
        int DirCreate(char *src_dir_path,  char *dest_path);
        int CopyFile(char *src_file_path,char *dest_file_path);
        char *m_src_file_path;   // 相对路径,输入值
        char **m_src_dir_array;  
        int  src_dir_index;
        char *m_dest_dir_path;  //相对或者绝对路径，输入值
        char *m_src_dir_path; //output
        char *m_dest_file_path;//output
        
        

        
        
        
        
};
#endif