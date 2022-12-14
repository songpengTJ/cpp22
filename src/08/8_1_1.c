#include <stdio.h>				// 调用基本输入输出函数
#include <stdlib.h>				//调用常用函数库，提供生成随机数函数
int main()
{
   int a[10];					// 声明数组a，类型为整型，长度为10
   int i, j;						// 声明循环控制变量
   int t;						// 声明整型变量t，用于排序中交换数组元素的值
   printf("排序前的数组：\n");		// 输出提示信息
   for(i = 0; i < 10; i++) {			// i从0循环到9
      a[i] = rand() % 100 + 1;		// 使用随机函数，生成1到100间随机数
      printf("%4d ", a[i]);			// 输出未排序前的数组
   }
   printf("\n排序后的数组：\n");	// 输出提示信息
   for(i = 0; i < 9; i++) {			// i从0循环到8
      for(j = i + 1; j < 10; j++) {		// j从i + 1循环到9
         if (a[i] > a[j]) {			// 比较的两个元素值的大小，如果前一个大于后一个，交换两个元素的值
            t = a[i];				// 将前一个元素的值保存到变量t中
            a[i] = a[j];			// 将后一个元素的值复制到前一个元素中
            a[j] = t;				// 将变量t所保存的值，复制到后一个元素中
         }
      }
   }
   for(i = 0; i < 10; i++) {			// i从0循环到9
      printf("%4d ", a[i]);			// 输出未排序后的数组
   }
   return 0;					// 退出程序
}
