#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
static void exit_nicely(PGconn *conn)				// 该函数用于结束数据库连接
{
   PQfinish(conn);
   exit(1);
}

int main()
{
   const char *conninfo;
   PGconn *conn;
   PGresult *res;
   int nFields;
   int i, j;
   conninfo = "dbname = postgres";					// 定义数据库连接字符串
   conn = PQconnectdb(conninfo);					// 建立数据库连接
   if (PQstatus(conn) != CONNECTION_OK)	{		// 检查后端连接成功建立
      fprintf(stderr, "数据库连接失败：%s",
      PQerrorMessage(conn));
      exit_nicely(conn);
   }
   else
      puts("连接数据库成功");
   res = PQexec(conn, "BEGIN");					// 开始一个事务块，即输入多个SQL命令一并执行
   if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      fprintf(stderr, "BEGIN命令失败：%s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
   }
   PQclear(res);								// 清除不需要的查询结果
   res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from pg_database");
											// 从系统表pg_database里抓取数据
   if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      fprintf(stderr, "声明游标失败：%s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
    }
   PQclear(res);
   res = PQexec(conn, "FETCH ALL in myportal");
   if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
   }
   nFields = PQnfields(res);
   for (i = 0; i < nFields; i++)
      printf("%-15s", PQfname(res, i));				// 输出属性名称
   printf("\n\n");
   for (i = 0; i < PQntuples(res); i++) {
      for (j = 0; j < nFields; j++)
         printf("%-15s", PQgetvalue(res, i, j));			// 输出每行数据记录
      printf("\n");
   }
   PQclear(res);
   res = PQexec(conn, "CLOSE myportal");			// 关闭游标
   PQclear(res);
   res = PQexec(conn, "END");					// 结束事务
   PQclear(res);
   PQfinish(conn);
   return 0;
}
