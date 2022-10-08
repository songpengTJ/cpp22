#include <db.h>
typedef struct stock_dbs {
   DB *inventory_dbp;								// 买主数据包内容的04	信息
   DB *vendor_dbp;									// 卖主数据包内容的06	信息
   char *db_home_dir;								// 数据文件目录
   char *inventory_db_name;							// 买主数据包名称
   char *vendor_db_name;							// 卖主数据包名称
} STOCK_DBS;
int databases_setup(STOCK_DBS *, const char *, FILE *);	// 设置数据文件
int databases_close(STOCK_DBS *);				// 关闭数据文件标识符
void initialize_stockdbs(STOCK_DBS *);			// 初始化数据包
int open_database(DB **, const char *, const char *, FILE *);
													// 打开数据文件
void set_db_filenames(STOCK_DBS *my_stock); 		// 设置数据文件名
