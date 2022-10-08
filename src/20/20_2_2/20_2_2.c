void my_error_handler(const char *error_prefix, char *msg)
												// 回调函数，在错误发生时调用
{
   printf("%s：%s\n", error_prefix, msg);		// 输出错误信息
}
DB *dbp;										// 创建数据包标识符
int ret;
ret = db_create(&dbp, NULL, 0);				// 初始化数据包
if (ret != 0) {
   fprintf(stderr, "%s: %s\n", "数据包初始化失败：",
         db_strerror(ret));				// 将错误信息输出到标准输出中
        return(ret);
}
dbp->set_errcall(dbp, my_error_handler);	// 设置错误发生时的回调函数
dbp->set_errpfx(dbp, "数据包"); 					// 设置错误信息前缀
ret = dbp->open(dbp, 
                NULL,
                "mydb.db", 
                NULL,
                DB_BTREE,
                DB_CREATE,
                0);
if (ret != 0) {
    dbp->err(dbp, ret, 数据文件打开失败: %s", "mydb.db");	// 捕捉错误信息
    return(ret);
}
