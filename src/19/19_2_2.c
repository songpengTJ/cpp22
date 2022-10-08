#include <libspopc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _emaillist emaillist;
struct _emaillist {											// 定义结构体，用于保存邮件信息
   int size;
   int sig;
   char head[500];
   char msg[65536];
};


int mail()
{
   popsession* mysession;									// 定义libspopc会话
   int error;
   char servername[200]; 									// 用于保存pop3服务器地址
   char user[20]; 											// 用于保存用于名
   char pass[20]; 											// 用于保存密码
   int last, total, i, j;
   puts("请输入pop3服务器地址：");
   scanf("%s", servername);
   puts("请输入用户名：");
   scanf("%s", user);
   puts("请输入密码：");
   scanf("%s", pass);
   libspopc_init(); 											// 初始化libspopc
   error = popbegin(servername, 
                    user, 
                    pass, 
                    &mysession);								// 打开pop连接
   if (error != 0) {
      puts("无法打开邮箱");
      return 1;
   }
   last = mysession -> last;									// 获取最后一个邮件的编码
   total = mysession -> num;									// 获取邮件总数
   emaillist *els = malloc(sizeof(emaillist) * total);					// 动态分配内存存放邮件内容
   for(i = 1; i <= last; i++){
      (els + i - 1) -> size = popmsgsize(mysession,i) ;				// 获取邮件大小
      (els + i - 1) -> sig = popmsguid(mysession,i);					// 获取邮件编号
      strncpy((els + i - 1) -> head, popgethead(mysession,i), 499);		// 获取邮件标题
      strncpy((els + i - 1) -> msg, popgetmsg(mysession,i), 65535);		// 获取邮件内容
      *((els + i - 1) -> head) +500) = '\0';
      *((els + i - 1) -> msg) + 65536) = '\0';
      popdelmsg(mysession,i);								// 在邮箱中删除邮件
   }
   popend(mysession);										// 结束会话
   libspopc_clean();											// 终止libspopc
   for (i = 0; i <= last - 1; i++) {
      printf("%d：%30s %dB", (els + i) -> sig,
                             (els + i) -> head,
                             (int) (els + i) -> size / 1024 );			// 显示邮件概要信息
   while(1) {
      puts("请输入要查看邮件的编码，输入“-1”退出");
      scanf("%d", &j);
      if (j == -1)
         break;
      else {
         for(i = 0; i <= last - 1; i++) {
            if ((els + i) -> sig == j);
               puts((els + i) -> msg);							// 输出邮件内容
         }
      }
   }
   free(els);
   return 0;
}
