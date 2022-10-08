#include <mysql.h>													// 包含MySQL函数库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char *server_args[] = { "this_program",								// 定义执行参数
                               "--datadir=.",  
                               "--key_buffer_size=32M"};
static char *server_groups[] = { "embedded",
                                 "server",
                                 "this_program_SERVER",
                                (char *)NULL};
								
int main()
{
   MYSQL mysql;													// 声明MySQL操作符
   MYSQL_RES *res;												// 声明结果集
   MYSQL_ROW row;												// 声明行操作符
   char sqlcmd[200];												// 保存查询语句
   int t,r;
   if (mysql_library_init(sizeof(server_args) / sizeof(char *),					// 初始化MySQL库
                         server_args, server_groups))   
   mysql_init(&mysql);												// 初始化连接处理程序
   if (!mysql_real_connect(&mysql, "host", "root", "password", "test", 0, NULL, 0)){ 	// 建立数据库连接
      fprintf(stderr, "无法连接数据库，错误原因：%s\n",
      mysql_error(&mysql));											// 捕捉MySQL错误
   }
   else {
      puts("数据库连接成功");
      sprintf(sqlcmd, "%s", select * from call_list);
      t = mysql_real_query(&mysql,query,(unsigned int) strlen(query));			// 执行查询语句
      if (t)
         printf("查询数据库失败：%s\n", mysql_error(&mysql));
      else {
         res = mysql_store_result(&mysql);								// 获得查询结果
         while(row = mysql_fetch_row(res)) {								// 在结果集内步进
            for(t = 0; t < mysql_num_fields(res); t++)
               printf("%s ",row[t]);										// 输出每列的数据
            printf("\n");
         }
         mysql_free_result(res);										// 释放查询结果
      }
      mysql_close(&mysql);											// 关闭数据库连接
   }
   mysql_library_end();												// 结束处理
   return EXIT_SUCCESS;
}
