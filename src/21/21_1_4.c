#include <stdio.h>
#include <string.h>
#include "database.h"
#define TM_L 14										// 定义表示时间的字符串长度
typedef struct _calllist callist;
struct _calllist {
   long id;											// 记录编号
   int type;											// 通话类型
   long telnum;											// 对方号码
   char btime[TM_L];									// 通话起始时间
   long tcount;											// 通话时长
   float charge_rate;										// 费率
   float charge_sum;									// 总费用
};
void printdb(callist *cl, int length)							// 输出记录函数
{
   int i = sizeof(callist);
   int j;
   char btime[TM_L + 1] = {0};								// 用于读取字符串，为字符串加入结束符
   for(j = 0 ;j < length / i; j++) {
      memcpy(btime, (cl + j) -> btime, TM_L);					// 将字符串读出
      printf("%ld, %d, %ld, %14s, %ld, %1.2f, %1.2f\n",			// 输出数据中的内容
             (cl + j) -> id,
             (cl + j) -> type,
             (cl + j) -> telnum,
             btime,
             (cl + j) -> tcount,
             (cl + j) -> charge_rate,
             (cl + j) -> charge_sum);
   }
}


int main()
{
   const char *dbfile = "data.sqlite";							// 定义数据库文件名
   int res;
   char *errmsg = NULL;
   char **result;										// 用于保存查询结果
   int row, col;											// 用于保存行和列
   int i;
   res = open_database(dbfile);							// 打开数据库
   if (res != 0) {
      printf("数据库打开失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已打开");
   const char *sqlcmd = "SELECT * FROM call_list";			// 定义SQL查询字符串
   res = sqlite3_get_table(db, sqlcmd, &result, row, col, &errmsg);	// 执行SQL命令
   if (res != SQLITE_OK )
      printf("查询失败，代码：%d-%s\n", res, errmsg);
   else if (row < 2)										// 判断查询到的实际记录数是否为0
      puts("查询结果为0条");
   else {
      puts("查询成功，查询结果为：");
      callist *cl = malloc(sizeof(callist) * row - 1);				// 为保存结果的结构体动态分配内存
      callist *p_cl;										// 定义一个callist类型指针
      p_cl = cl;
      for(i = 0; i <= row; i++) {								// 将结果中的值取出
         p_cl -> id = atol(result[i * ncol]);
         p_cl -> type = atoi(result[i * ncol + 1]);
         p_cl -> telnum = atol(result[i * ncol + 2]);
         memcpy (p_cl -> btime, result[i * ncol + 3], TM_L);
         p_cl -> tcount = atol(result[i * ncol + 4]);
         p_cl -> charge_rate = atof(result[i * ncol + 5]);
         p_cl -> charge_sum = atof(result[i * ncol + 6]);
      }
      sqlite3_free_table(result);							// 释放结果所占用的内存空间
      printdb(cl, row -1);									// 输出结果
      free(cl);
   }
   res = close_database();
   if (res != 0) {
      printf("数据库关闭失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已关闭");
   return 0;
}
