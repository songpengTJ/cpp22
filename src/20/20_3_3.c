#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
static void exit_nicely(PGconn *conn)						// 该函数用于结束数据库连接
{
   PQfinish(conn);
   exit(1);
}


int main()
{
   const char *conninfo;
   PGconn *conn;
   PGresult *res;
   conninfo = "dbname = mydb";							// 假设服务器中已有“mydb”数据库
   conn = PQconnectdb(conninfo);							// 建立数据库连接
   if (PQstatus(conn) != CONNECTION_OK)	{				// 检查后端连接成功建立
      fprintf(stderr, "数据库连接失败：%s",
      PQerrorMessage(conn));
      exit_nicely(conn);
   }
   else
      puts("连接数据库成功");
   const char *sqlcmd = "CREATE TABLE call_list (
                        id INTEGER[4] NOT NULL AUTO_INCREMENT PRIMARY KEY, \
                        type INTEGER[1], \
                        telnum INTEGER[4], \
                        bttime CHAR(14), \
                        tcount INTEGER[4], \
                        charge_rate FLOAT[4], \				// “\”符号用于将一行分为多行
                        charge_sum FLOAT[4])";				// 创建一个通话清单数据表
   res = PQexec(conn, const char sqlcmd);					// 执行SQL命令
   if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "创建数据表失败：%s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
   PQclear(res);										// 清除PGresult对象
   PQfinish(conn);
   return 0;
}
