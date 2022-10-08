#include <stdio.h>

int main(int argc, char *argv[])						// 定义主函数参数
{
   int i;										// 声明循环控制变量
   printf("您输入的运行参数共有：%d条\n", argc);		// 输出参数的条数
   for (i = 0; i < argc; i++)							// 以参数的条数为条件循环
      puts(argv[i]);								// 输出每条参数
   return 0;
}
