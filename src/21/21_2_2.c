#include <mysql.h>
#include <stdlib.h>
static char *server_args[] = { "this_program",					// 定义执行参数
                               "--datadir=.",  
                               "--key_buffer_size=32M"};
static char *server_groups[] = { "embedded",
                                 "server",
                                 "this_program_SERVER",
                                (char *)NULL}; 
int main(void)
{
   if (mysql_library_init(sizeof(server_args) / sizeof(char *),		// 初始化MySQL库
                         server_args, server_groups))   
      exit(1);
   mysql_library_end();									// 结束处理
   return EXIT_SUCCESS;
}
