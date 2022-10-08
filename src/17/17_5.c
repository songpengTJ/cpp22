#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>								// 包含线程库
void *thread_function(void *arg);						// 定义线程函数原型

int main()
{
   int res;											// 用于保存操作结果
   pthread_t a_thread;								// 用户保存线程信息
   void *thread_result;								// 用于保存线程返回值
   res = pthread_create(&a_thread, NULL, thread_function, NULL);	// 创建线程
   if (res != 0) {										// 判断线程创建是否有错误
      perror("线程创建失败");
      exit(EXIT_FAILURE);
   }
   sleep(3);										// 睡眠3秒
   printf("取消线程...\n");
   res = pthread_cancel(a_thread);						// 发送取消线程请求
   if (res != 0) {										// 判断线程取消是否有错误
      perror("取消线程失败");
      exit(EXIT_FAILURE);
   }
   printf("等待线程结束...\n");
   res = pthread_join(a_thread, &thread_result);			// 等待线程结束
   if (res != 0) {										// 判断线程结束是否有错误
      perror("线程结束失败");
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)						// 定义线程函数细节
{
   int i, res;
   res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	
												// 定义线程状态，允许接收取消请求
   if (res != 0) {										// 判断定义线程状态是否有错误
      perror("定义线程状态失败");
      exit(EXIT_FAILURE);
   }
   res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
												// 定义线程结束的方式为采取一些动作后再结束
   if (res != 0) {										// 判断定义线程结束方式是否有错误
      perror("定义线程结束失败");
      exit(EXIT_FAILURE);
   }
   printf("线程函数正在运行\n");

   for (i = 0; i < 10; i++) {
      printf("线程函数正在运行(%d)...\n", i);
      sleep(1);										// 睡眠1秒钟
   }
   pthread_exit(0);
}
