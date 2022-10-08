#include <unistd.h>						// 标准函数库
#include <stdio.h>						// 基本输入输出函数库
#include <sys/types.h>					// 该头文件提供系统调用的标志
#include <sys/stat.h>					// 进程状态及相关操作函数库
#include <fcntl.h>						// 该头文件包含文件I/O操作相关
										// 标志
int main()
{
   int fd;
   if ((fd = open("output", O_CREAT|O_RDWR,0644)) == -1) {
											// 打开或创建文件
      perror("打开或创建文件出错");
      return 1;
   }
   close(1);									// 关闭标准输出
   dup(fd);									// 复制fd到文件描述符1上
   close(fd); 								// 关闭文件描述符fd
   puts("该行数据将输出到文件中");
   return 0;
}
