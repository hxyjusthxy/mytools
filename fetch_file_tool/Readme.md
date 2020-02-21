需求背景：SVN提交加速
    SVN提交文件分类
        1.新增文件
        2.修改文件，此文件之前不在SVN Repo中
            需要先从Android BSP中获取原生文件上传（包括文件路径）
        3.修改文件，次文件之前就在SVN Repo中
需求分析：
    对于需求2类型文件进行软件开发；
    可以从“git status./”中获取需求2类型文件列表（相对路径）
        1.在DestPath中依次创建目录(access() mkdir())
        2.Copy文件到DestPath中： f_open fread fwrite
    
思路：
    对于任意的一个路径SourcePath:先分割得到一组目录名，以及一个文件名
    path_array[xx][]；
    对每一个目录，在DestPath中先查看是否存在，不存在则创建之，直到文件名处理时，
        拷贝相应的SourcePath文件到次目录下

    
    