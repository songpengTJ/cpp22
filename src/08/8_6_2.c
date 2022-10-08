#include <stdio.h>							//调用基本输入输出函数
#define M 2								// 定义常量M，用作二维数组的行数
#define N 4								// 定义常量N，用作二维数组的列数
int main()
{
   int a[M][N], *pa;							// 定义整型二维数组N和整型指针变量*pa
   int i, j;									// 定义循环控制变量i和j
   pa = a[0];								// 将指针变量*pa指向数组第1行的首地址
   printf("请输入数组的数值：");				// 输出提示信息
   for(i = 0; i < M; i++){						// i从1到M循环
      for(j = 0; j < N; j++){					// j从1到N循环
         scanf("%d", pa + i * N + j);				// 从键盘输入获取数据，保存到数组中
         putchar('\0');						// 换行
      }
   }
   printf("数组内的数值是：");					// 输出提示信息
   for(i = 0; i < M * N; i++){					// i从1到M × N循环
      printf("%d\n", *(pa + i));					// 输出数组的值
   }
   return 0;
}