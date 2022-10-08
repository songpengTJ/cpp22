#include <stdio.h>
int main()
{
   FILE *fp;								// 定义文件流指针
   fp = fopen("/usr/include/gnu-versions.h","r");
						// 以只读方式打开文件，函数返回的文件流指针赋给*fp
   if (fp != NULL)						// 判断文件是否打开成功
      puts("打开文件成功");
   else {
      perror("打开文件");
      return 1;
   }
   if (fclose(fp) != -1)				// 关闭文件并判断文件关闭是否成功
      puts("关闭文件成功");
   else {
      perror("关闭文件");
      return 1;
   }
   return 0;
}
