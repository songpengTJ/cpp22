#include <fcntl.h>							// 提供open()函数
#include <sys/types.h>						// 提供mode_t类型
#include <sys/stat.h>						// 提供open()函数的符号
#include <unistd.h>							// 提供close()函数
#include <stdio.h>
#include <stdlib.h>
int main()
{
   int f;								// 声明变量f，用于保存文件标识符
   const char *f_path = "test";			// 定义路径字符串
   mode_t f_attrib;						// 声明mode_t型变量，保存文件属性
   struct stat *buf = malloc(sizeof(struct stat));	// 动态分配结构体*buf的内存
   f_attrib = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
  										// 为umask变量赋值
   f = creat(f_path, f_attrib);			// 创建一个新文件，并设置访问权限
   if (f == -1) {						// 判断文件创建是否成功
      puts("文件创建失败");				// 输出错误信息
      return 1;
   }
   else
      puts("文件创建成功");				// 输出成功信息
   fstat(f, buf);						// 通过文件标识符获取访问权限
   if (buf->st_mode & S_IRUSR)			// 引用buf内的信息读取权限
      puts("所有者拥有读权限");
   if (buf->st_mode & S_IRGRP)
      puts("群组拥有读权限");
   close(f);									// 关闭文件
   chmod(f_path, 0771);						// 修改该文件的权限
   stat(f_path, buf);						// 通过路径获取访问权限
   if (buf->st_mode & S_IWUSR)				// 引用buf内的信息读取权限
      puts("所有者拥有写权限");
   if (buf->st_mode & S_IWGRP)
      puts("群组拥有写权限");
   free(buf);							// 释放buf指针所指向的内存空间
   return 0;
}
