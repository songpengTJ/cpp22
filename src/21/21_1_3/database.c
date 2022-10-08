#include "database.h"
int open_database(const char *dbfile)					// 定义数据库打开函数
{
   int result;
   result = sqlite3_open(dbfile, &db );					// 打开一个数据库
   return result;
}
int close_database(void)								// 定义数据库关闭函数
{
   int result;
   result = sqlite3_close(db);
   return result;
}
