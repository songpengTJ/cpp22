#include "gettingstarted_common.h"
char * show_inventory_item(void *);					// 显示库存条目
int show_all_records(STOCK_DBS *);					// 显示所有记录
int show_records(STOCK_DBS *, char *);				// 显示指定记录
int show_vendor_record(char *, DB *); 				// 显示卖主记录
int main(int argc, char *argv[])					// 主函数
{
   STOCK_DBS my_stock;
   int ret;
   initialize_stockdbs(&my_stock);					// 初始化
   set_db_filenames(&my_stock);						// 设置数据文件名
   ret = databases_setup(&my_stock, "example_database_read", stderr);
   if (ret != 0) {
      fprintf(stderr, "打开数据文件失败\n");
      databases_close(&my_stock);
      return (ret);
   }
   ret = show_all_records(&my_stock);				// 显示所有记录
   databases_close(&my_stock);						// 关闭数据库连接
   return (ret);
} 
