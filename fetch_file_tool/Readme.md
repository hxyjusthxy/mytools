需求背景：SVN提交加速
    SVN提交文件分类
        1.新增文件
        2.修改原生文件，此文件之前不在SVN Repo中
            需要先从Android BSP中获取原生文件上传（包括文件路径）
        3.修改文件，此文件之前就在SVN Repo中
需求分析：
    正常操作中，
        1.从Ubuntu中通过git diff --name-only | xargs zip dest_dir.tar.gz，解压获取最终推送目录：DestDir
        2.从SVN仓库下载得到SVNBase目录
        3.【工作内容1】对比DestDir和SVNBase目录，获取DestDir中有的文件，而SVNBase中没有的organ文件路径列表orphan_list
            排除.svn目录
        4.【工作内容2】
            按照orphan_list将文件从AndroidBSPOriginalProject中将文件拷贝到SVNBase中。
 具体实施：
    对比目录获取orphan_list:
        注意遍历DestDir中的所有层级文件
            get_orphan_list(input dest_dir_path){
                if (!get_file_from_dest_dir(&file_info)){
                    return;//本目录已经获取不了文件了
                }
                if (file_info.is_dir){
                    new_dir = dest_dir_path + file_info.name;
                    get_orphan_list(new_dir)
                }else(file_info.is_file){
                    if (access(file_info.path)){
                        store_file_name_to_file();
                    }
                    else{
                        
                    }
                }
            }

    
    