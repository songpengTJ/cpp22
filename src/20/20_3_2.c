#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>						// 包含libpq函数库
static void exit_nicely(PGconn *conn)		// 该函数用于结束数据库连接
{
   PQfinish(conn);
   exit(1);
}
int main()
{
   const char *conninfo;
   PGconn *conn;
   conninfo = "dbname = postgres";			// 定义数据库连接字符串
   conn = PQconnectdb(conninfo);			// 建立数据库连接
   if (PQstatus(conn) != CONNECTION_OK)	{	// 检查后端连接成功建立
      fprintf(stderr, "数据库连接失败：%s",
      PQerrorMessage(conn));
      exit_nicely(conn);
   }
   else
      puts("连接数据库成功");
	   PQfinish(conn);								// 断开与数据库连接
      puts("已断开与数据库的连接");
   return 0;
}
