#include <sqlite3.h>									// 包含SQLite接口函数
sqlite3 *db = NULL;									// 定义一个全局的数据库标识符
int open_database(const char *dbfile);					// 定义数据库打开函数原型
int close_database(void);								// 定义数据库关闭函数
