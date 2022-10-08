#include <stdlib.h>
#include <stdio.h>
#include <odbc/sql.h>						// ODBC的SQL语句支持函数库
#include <odbc/sqlext.h>					// ODBC的SQL执行支持函数库
#include <odbc/sqltypes.h>					// ODBC的SQL数据类型函数库
SQLHENV V_OD_Env;							// ODBC环境标识符
long V_OD_erg;								// 函数运行结果
SQLHDBC V_OD_hdbc;							// 数据库连接标识符
char V_OD_stat[10];							// SQL状态
SQLINTEGER V_OD_err,V_OD_rowanz,V_OD_id;
SQLSMALLINT V_OD_mlen,V_OD_colanz;
char V_OD_msg[200],V_OD_buffer[200];



int main(int argc,char *argv[])
{
   V_OD_erg = SQLAllocHandle(SQL_HANDLE_ENV,
                              SQL_NULL_HANDLE,
                              &V_OD_Env);		// 分配环境标识符并注册版本
   if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)) 19	{
      puts("分配错误。");
      return 1;
   }

   
   
      V_OD_erg = SQLSetEnvAttr(V_OD_Env,
                   SQL_ATTR_ODBC_VERSION,
                  (void*)SQL_OV_ODBC3, 0);		// 设置环境属性 
  if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)) 05	{
     puts("设置环境属性出错。");
     SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
      return 1;
   }

   
   
      V_OD_erg = SQLAllocHandle(SQL_HANDLE_DBC,
                              V_OD_Env,
                              &V_OD_hdbc);			// 连接到unixODBC
   if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)) 05	{
      printf("连接错误，代码为：%d\n",V_OD_erg);
      SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
      return 1;
   }

   
   
      SQLSetConnectAttr(V_OD_hdbc,
                     SQL_LOGIN_TIMEOUT,
                     (SQLPOINTER *)5, 0);				// 设置连接属性
   V_OD_erg = SQLConnect(V_OD_hdbc,
                     (SQLCHAR*) "Test",			// DSN名称
                      SQL_NTS,
                     (SQLCHAR*) "root", SQL_NTS,	// 数据库的用户名
                     (SQLCHAR*) "", SQL_NTS);	// 数据库的密码
   if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)) 10	{
      printf("连接错误，代码为：%d\n",V_OD_erg);
      SQLGetDiagRec(SQL_HANDLE_DBC,
                      V_OD_hdbc,1, 
                      V_OD_stat,
                      &V_OD_err,
                      V_OD_msg,
                      100,
                      &V_OD_mlen);
      printf("%s (%d)\n",V_OD_msg,V_OD_err);
      SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
      return 1;
   }
   puts("成功连接到服务器中");

   
   
     V_OD_erg = SQLAllocHandle(SQL_HANDLE_STMT,
                             V_OD_hdbc,
                             &V_OD_hstmt);			// 设置数据库驱动
   if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
{
      printf("驱动设置错误，代码为：%d\n",V_OD_erg);
      SQLGetDiagRec(SQL_HANDLE_DBC,
                      V_OD_hdbc,
                      1,
                      V_OD_stat,
                      &V_OD_err,
                      V_OD_msg,
                      100,
                      &V_OD_mlen);
      printf("%s (%d)\n",V_OD_msg,V_OD_err);
      SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
      return 1;
   }
SQLBindCol(V_OD_hstmt, 1, SQL_C_CHAR, &V_OD_buffer, 150,&V_OD_err);
    SQLBindCol(V_OD_hstmt, 2, SQL_C_ULONG, &V_OD_id, 150, &V_OD_err);
				// 将应用程序的数据缓冲绑定到结果集的各列

				
				
	V_OD_erg = SQLExecDirect(V_OD_hstmt,
               "SELECT dtname,iduser FROM web order by iduser",SQL_NTS);  
			// 执行SQL查询
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)){
       printf("查询错误，代码为：%d\n", V_OD_erg);
       SQLGetDiagRec(SQL_HANDLE_DBC,
                       V_OD_hdbc,
                       1,
                       V_OD_stat,
                       &V_OD_err,
                       V_OD_msg,
                       100,
                       &V_OD_mlen);					// 获得诊断信息
       printf("%s (%d)\n",V_OD_msg,V_OD_err);
       SQLFreeHandle(SQL_HANDLE_STMT, V_OD_hstmt);	// 释放结果集
       SQLFreeHandle(SQL_HANDLE_DBC, V_OD_hdbc);
       SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
       return 1;
}



    V_OD_erg = SQLNumResultCols(V_OD_hstmt, &V_OD_colanz);	// 查询错误信息
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)){
        SQLFreeHandle(SQL_HANDLE_STMT,V_OD_hstmt);
        SQLDisconnect(V_OD_hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
        return 1;
    }
    printf("结果的列数为：%d\n",V_OD_colanz);
    V_OD_erg = SQLRowCount(V_OD_hstmt, &V_OD_rowanz);		// 获取行数
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO)){
      printf("行数为：%d\n",V_OD_erg);
      SQLFreeHandle(SQL_HANDLE_STMT,V_OD_hstmt);
      SQLDisconnect(V_OD_hdbc);
      SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
      SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
      return 1;
    }
    printf("行数为：%d\n",V_OD_rowanz);
    V_OD_erg = SQLFetch(V_OD_hstmt);				// 获得结果集中的行
    while(V_OD_erg != SQL_NO_DATA) {
     printf("查询结果: %d %s\n",V_OD_id,V_OD_buffer);
     V_OD_erg = SQLFetch(V_OD_hstmt);  
    };

	
	
    SQLFreeHandle(SQL_HANDLE_STMT, V_OD_hstmt);
    SQLDisconnect(V_OD_hdbc);						// 断开数据库连接
    SQLFreeHandle(SQL_HANDLE_DBC, V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    return(0);
}
