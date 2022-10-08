#include "gettingstarted_common.h"
void initialize_stockdbs(STOCK_DBS *my_stock)	// 初始化stock_dbs结构
{
    my_stock->db_home_dir = DEFAULT_HOMEDIR;	// 数据包主目录
    my_stock->inventory_dbp = NULL;				// 库存
    my_stock->vendor_dbp = NULL;				// 卖方
    my_stock->inventory_db_name = NULL;			// 库存信息数据表名
    my_stock->vendor_db_name = NULL;			// 卖方信息数据表名
}



void set_db_filenames(STOCK_DBS *my_stock)		// 定义数据包所有相关文件
{
    size_t size;
    size = strlen(my_stock->db_home_dir) + strlen(INVENTORYDB) + 1;
    my_stock->inventory_db_name = malloc(size);
    snprintf(my_stock->inventory_db_name, size, "%s%s",
      my_stock->db_home_dir, INVENTORYDB);		// 定义买主数据包文件名
    size = strlen(my_stock->db_home_dir) + strlen(VENDORDB) + 1;
    my_stock->vendor_db_name = malloc(size);
    snprintf(my_stock->vendor_db_name, size, "%s%s",
      my_stock->db_home_dir, VENDORDB);			// 定义卖主数据包文件名
}



int open_database(DB **dbpp,					// 数据包标识符指针
                 const char *file_name,			// 数据文件名
                 const char *program_name,		// 程序名称
                 FILE *error_file_pointer)	// 存放错误信息的文件流指针
{
   DB *dbp;										// 定义数据包标识符
   u_int32_t open_flags;						// 定义打开标志
   int ret;
   ret = db_create(&dbp, NULL, 0);				// 初始化数据包标识符
   if (ret != 0) {
      fprintf(error_file_pointer, "%s: %s\n", program_name,
              db_strerror(ret));
      return(ret);
   }
   *dbpp = dbp;						// 指向db_create()动态分配的内存
   dbp->set_errfile(dbp, error_file_pointer);	// 指定错误输出文件
   dbp->set_errpfx(dbp, program_name);			// 指定错误信息前缀
   open_flags = DB_CREATE;						// 设定打开标志
   flags = DB_CREATE;				// 将数据包打开标识设为创建数据包
   ret = dbp->open(dbp,					// 数据包标识符指针
                   NULL,					// 事务指针
                   "my_db.db",				// 数据文件名称
                   NULL,					// 可选数据包逻辑名称
                   DB_BTREE,				// 将数据存取子系统设置为B树
                   flags,					// 数据包打开标识
                   0);						// 文件模式，0表示默认
   if (ret != 0) {
      dbp->err(dbp, ret, "数据包'%s'打开失败.", file_name);
      return(ret);
   }
   return (0);
}



int databases_setup(STOCK_DBS *my_stock,
                    const char *program_name,
                    FILE *error_file_pointer)			// 设置数据包文件
{
   int ret;
   ret = open_database(&(my_stock->vendor_dbp),
                       my_stock->vendor_db_name,
                       program_name,
                       error_file_pointer);			// 打开卖主数据包
   if (ret != 0)
      return (ret);
   ret = open_database(&(my_stock->inventory_dbp),
                      my_stock->inventory_db_name,
                      program_name,
                      error_file_pointer);				// 打开买主数据包
    if (ret != 0)
       return (ret);
    printf("数据包打开成功\n");
    return (0);
}



int databases_close(STOCK_DBS *my_stock)			// 关闭数据包标识符
{
   int ret;
   if (my_stock->inventory_dbp != NULL) {
      ret = my_stock->inventory_dbp->close(my_stock->inventory_dbp, 0);
      if (ret != 0)
         fprintf(stderr, "买主数据包关闭失败: %s\n",
                 db_strerror(ret));
   }
   if (my_stock->vendor_dbp != NULL) {
      ret = my_stock->vendor_dbp->close(my_stock->vendor_dbp, 0);
      if (ret != 0)
         fprintf(stderr, "卖主数据包关闭失败: %s\n",
                 db_strerror(ret));
    }
    printf("数据包已关闭.\n");
    return (0);
}



