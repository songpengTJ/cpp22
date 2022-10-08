#include <stdio.h>
#include "database.h"

int main()
{
   const char *dbfile = "data.sqlite"						// 定义数据库文件名
   int res;
   char *errmsg = NULL;
   res = open_database(dbfile);						// 打开数据库
   if (res != 0) {
      printf("数据库打开失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已打开");
   const char *sqlcmd = "CREATE TABLE call_list (
                        id INTEGER PRIMARY KEY, \
                        type NUMERIC, \
                        telnum NUMERIC, \
                        bttime TEXT, \
                        tcount NUMERIC, \
                        charge_rate NUMERIC, \			// “\”符号用于将一行分为多行
                        charge_sum NUMERIC)";		// 创建一个通话清单数据表
   res = sqlite3_exec(db, sqlcmd, NULL, NULL, &errmsg);	// 执行SQL命令
   if (res != SQLITE_OK )
      printf("执行失败，代码：%d-%s\n", res, errmsg);
   else
      puts("执行成功，创建了一个数据表");
   res = close_database();
   if (res != 0) {
      printf("数据库关闭失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已关闭");
   return 0;
}
