#include <stdio.h>
int x = 1000;						// 定义全局变量x
void func();

int main()
{
   printf("%d\n", x);					// 引用全局变量x
   x = 2000;						// 改变全局变量x的值
   func();							// 调用函数func()
   return 0;
}

void func()
{
   printf("%d\n", x);					// 引用全局变量x，此时全局变量x的值已被main()函数改变过
   return;
}
