#include <stdio.h>
#include <sqlora.h>									// 包含Oracle数据库接口函数
static int _abort_flag = 0;								// 错误代码标志

int main()
{
   const char *cstr = "test1234/4321test";					// 用户名和密码
   sqlo_db_handle_t dbh;								// 该变量用于数据库标识符
   int status;
   char server_version[1024];							// 用于保存服务器版本
   status = sqlo_init(SQLO_OFF, 1, 100); 				// 初始化libsqlora
   if (status != SQLO_SUCCESS) { 
      puts("libsqlora初始化失败。"); 
      return 1; 
   } 
   status = sqlo_connect(&dbh, cstr);					// 连接Oracle数据库服务器
   if (status != SQLO_SUCCESS) {
      printf("不能使用下列用户登录：%s\n", cstr);
      return 1;
   }
   RETURN_ON_ABORT;							// 如果扑捉到信号则结束
   if (SQLO_SUCCESS != sqlo_server_version(dbh, 
                         server_version,
                         sizeof(server_version))) {		// 获得Oracle数据库服务器版本信息
    printf("无法获得版本信息：%s\n", sqlo_geterror(dbh));
    return 1;
   }
   printf("已连接到：\n%s\n\n", server_version);
   RETURN_ON_ABORT;
   sqlo_finish(dbh);									// 断开连接
   puts("服务器连接已断开");
   return 0;
}
