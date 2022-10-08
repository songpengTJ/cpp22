#include <glib.h>							// 包含GLib函数库
static GMutex *mutex = NULL;
static gboolean t1_end = FALSE;				// 用于结束线程1的标志
static gboolean t2_end = FALSE;				// 用于结束线程2的标志
typedef struct _Arg Arg;
struct _Arg
{
   GMainLoop* loop;						// 该成员为一个GLib实现循环对象
   gint max;
};
void run_1(Arg *arg)							// 线程1函数
{
   int i ;
   for(i=0; i < arg->max; i++) {
      if(g_mutex_trylock(mutex) == FALSE) {
         g_print("%d ：线程2锁定了互斥对象\n", i);
         g_mutex_unlock(mutex);				// 对像解锁
      }
      else
         g_usleep(10);						// 使线程睡眠10秒
   }
   t1_end = TRUE;							// 将该线程结束的标志置为非0
}
void run_2(Arg *arg)							// 线程2函数
{
   int i;
   for(i = 0; i < arg->max; i++) {
      if(g_mutex_trylock(mutex) == FALSE) {
         g_print("%d ：线程1锁定了互斥对象\n", i);
         g_mutex_unlock(mutex);				// 对像解锁
      }
      else
         g_usleep(10);						// 使线程睡眠10秒
   }
   t2_end = TRUE;							// 将该线程结束的标志置为非0
}
void run_3(Arg *arg)							// 线程3函数
{
   for( ; ; ) {								// 建立一个死循环
      if(t1_end && t2_end) {					// 判断线程1和线程2是否已结束
         g_main_loop_quit(arg->loop);			// 退出GLib主循环
         break;
      }
   }
}

int main()
{
   GMainLoop *mloop;						// 创建GLib主循环
   Arg *arg;								// 声明包含指向GLib主循环指针和计数器的结构
   if(!g_thread_supported())					// 判断是否支持GLib线程
      g_thread_init(NULL);
   mloop = g_main_loop_new(NULL, FALSE);		// 开始GLib主循环
   arg = g_new(Arg, 1);
   arg->loop = mloop;
   arg->max = 11;
   mutex = g_mutex_new();					// 创建一个GMutex对象线程池
   g_thread_create(run_1, arg, TRUE, NULL);		// 创建线程1
   g_thread_create(run_2, arg, TRUE, NULL);		// 创建线程2
   g_thread_create(run_3, arg, TRUE, NULL);		// 创建线程3
   g_main_loop_run(mloop);					// 运行主循环
   g_print("线程3退出事件循环\n");
   g_mutex_free(mutex);						// 释放GMutex对象
   g_print("释放互斥对象\n"); 
   g_free(arg);								// 清除结构体arg
   g_print("释放参数所用的内存\n");
   return 0;
}
