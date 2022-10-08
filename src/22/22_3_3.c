#include <glib.h>

int main()
{
   GRand *rand;										// 创建一个随机数对象指针
   GTimer *timer;										// 创建一个计时器对象指针
   gint n;
   timer = g_timer_new();									// 创建计时器对象
   g_timer_start(timer);									// 开始计时
   rand = g_rand_new();									// 创建随机数对象
   for(n = 0; n < G_MAXINT; n++)
      g_print("%d\t", g_rand_int_range(rand, 1, 100));			// 产生随机数并输出
   g_print("\n");
   g_rand_free(rand);									// 释放随机数对象
   g_timer_stop(timer);									// 计时结束
   g_print("执行耗时：%.2f秒\n", g_timer_elapsed(timer,NULL));	// 输出计时结果
   return 0;
}
