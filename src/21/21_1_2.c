#include <sqlite3.h>									// 包含SQLite接口函数
#include <stdio.h>
sqlite3 *db = NULL;									// 定义一个全局的数据库标识符
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

int main()
{
   const char *dbfile = "data.sqlite"						// 定义数据库文件名
   int res;
   res = open_database(dbfile);						// 打开数据库
   if (res != 0) {
      printf("数据库打开失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已打开");
   res = close_database();
   if (res != 0) {
      printf("数据库关闭失败：%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("数据库已关闭");
   return 0;
}
