#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include "db.h"
#include "medialib.h"
sqlite3 *db = NULL;					// SQLite数据库标识符指针


int open_database(void);			// 连接数据库
int close_database(void);			// 断开数据库连接



int open_database(void)
{
   int res;
   const char *filename = "data.sqlite";
   res = sqlite3_open_v2(filename,
                        &db,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
                        NULL);						// 打开或创建数据库文件
   if (res) {
      printf("%s\n", sqlite3_errmsg(db));		// 输出错误信息
      return 0;
   }
   return 1;
}



int close_database(void)
{
   int res;
   res = sqlite3_close(db);							// 关闭数据库文件
   if (res) {
      printf("%s\n", sqlite3_errmsg(db));
      return 0;
   }
   return 1;
}



int create_medialib(void)
{
   int res;
   char *errmsg = NULL;
   const char *sqlcmd = "CREATE TABLE 'medialib' ('title' TEXT,\
                                                'artist' TEXT,\
                                                'album' TEXT,\
                                                'genre' TEXT,\
                                                'record_time' NUMERIC,\
                                                'filepath' TEXT)";	
													// SQL语句字符串
   res = sqlite3_exec( db, sqlcmd, 0, 0, &errmsg );	// 执行SQL语句
   if (res) {
      printf("创建数据表失败：%d-%s\n", res, errmsg );	// 输出错误信息
      return 0;
   }
   return 1;
}



int load_medialib(link_t *mlink, find_cond t)
{
   int res;								// 用于保存操作结果
   char *errmsg = NULL;					// 用于保存错误信息字符串
   char **tb;							// 用于保存查询结果字符串的地址
   int i;
   int nrow;								// 用于保存查询结果的行数
   int ncol;								// 用于保存查询结果的列数
   char sqlcmd[256];
   const char *str = NULL;
   node_t *endnode = NULL;
   node_t *mnode = NULL;				// 操作节点指针
   link_del_all(mlink);					// 删除链表中所有的节点
   switch(t) {							// 判断排序调节
      case BY_TITLE:
         str = "title";
         break;
      case BY_ARTIST:
         str = "artist";
         break;
      case BY_ABLUM:
         str = "album";
         break;
      case BY_GENRE:
         str = "genre";
         break;
      case BY_FILEPATH:
         str = "filepath";
         break;
   }
   if (str) {								// 判断是否使用了排序条件
      sprintf(sqlcmd, "SELECT * FROM medialib ORDER BY %s", str);
   }
   else {
      sprintf(sqlcmd, "SELECT * FROM medialib");
   }
   res = sqlite3_get_table(db,sqlcmd,&tb,&nrow,&ncol,&errmsg);	// 查询库
   if (res) {								// 判断是否有错误发生
      printf("读取数据库失败：%d-%s\n", res, errmsg );
      return 0;
   }
   else {
      if (nrow > 0) {					// 判断查询到的记录数是否大于0
         for(i = 0; i < nrow; i++) {
            mnode = (node_t *)malloc(sizeof(node_t));   // 为节点分配内存空间
            strcpy(mnode->item.title, tb[(i + 1) * ncol + 0]);	// 复														// 制数据到节点
            strcpy(mnode->item.atrist, tb[(i + 1) * ncol + 1]);
            strcpy(mnode->item.album, tb[(i + 1) * ncol + 2]);
            strcpy(mnode->item.genre, tb[(i + 1) * ncol + 3]);
            mnode->item.record_time = atoi(tb[(i + 1) * ncol + 4]);
            strcpy(mnode->item.filepath, tb[(i + 1) * ncol + 5]);
            if (i) {					// 判断是否为首端节点，否则执行判断体
               endnode->p = mnode;	// 将当前节点地址赋值给上一个节点
               mnode->p = NULL;		// 将当前节点指针置为NULL
               endnode = mnode;		// 保留当前节点的地址
               mlink->length++;		// 链表长度增1
            }
            else {					// 如果是首端节点，执行判断体
               endnode = mnode;		// 保留当前节点的地址
               mlink->np = mnode;		// 将当前节点地址赋值给链表入口
               mlink->length = 1;		// 将链表长度置为1
            }
         }
      }
   }
   return 1;
}



int medialib_insert(node_t *mnode)
{
   int res; 								// 用于保存操作结果
   char *errmsg = NULL; 					// 用于保存错误信息字符串
   char **tb; 							// 用于保存查询结果字符串的地址
   int nrow; 							// 用于保存查询结果的行数
   int ncol;
   char sqlcmd[MAX_TITLE_LENGTH
              + MAX_ATRIST_LENGTH
              + MAX_ALBUM_LENGTH
              + MAX_GENRE_LENGTH
              + MAX_PATH_LENGTH
              + 256];						// 计算SQL语句最大长度
   if (!mnode) {							// 判断节点的地址是否有误
      printf("链表节点地址有误\n");
      return 0;
   }
   sprintf(sqlcmd,
         "SELECT title FROM medialib WHERE filepath = \"%s\"",
         mnode->item.filepath);			// 生成查询语句
   res = sqlite3_get_table(db,sqlcmd,&tb,&nrow,&ncol,&errmsg);		
   // 查询数据库
   if (res) {
      printf("读取数据库失败：%d-%s\n", res, errmsg );
      return 0;
   }
   if (nrow > 0) {					// 判断要插入的文件是否存在
      sprintf(sqlcmd,
              "UPDATE medialib SET title = \"%s\",\
                                    artist = \"%s\",\
                                    album = \"%s\",\
                                    genre = \"%s\",\
                                    record_time = %d \
               WHERE filepath = \"%s\"",
               mnode->item.title,
               mnode->item.atrist,
               mnode->item.album,
               mnode->item.genre,
               (int) mnode->item.record_time,
               mnode->item.filepath);		// 生成UPDATE语句
   }
   else {
      sprintf(sqlcmd,
              "INSERT INTO medialib VALUES \
              (\"%s\", \"%s\", \"%s\", \"%s\", %d, \"%s\")",
              mnode->item.title,
              mnode->item.atrist,
              mnode->item.album,
              mnode->item.genre,
              (int) mnode->item.record_time,
              mnode->item.filepath);				// 生成INSERT语句
   }
   res = sqlite3_exec( db, sqlcmd, 0, 0, &errmsg );	// 执行SQL语句
   if (res) {
      printf("写入数据库失败：%d-%s\n", res, errmsg );
      return 0;
   }
   return 1;
}



int medialib_delete(node_t *mnode)
{
   int res;
   char *errmsg = NULL;
   char sqlcmd[MAX_PATH_LENGTH + 256];
   if (!mnode) {
      printf("链表节点地址有误\n");
      return 0;
   }
   sprintf(sqlcmd,
           "DELETE FROM medialib WHERE filepath = \"%s\"",
           mnode->item.filepath);				// 创建删除指定记录语句
   res = sqlite3_exec( db, sqlcmd, 0, 0, &errmsg );// 执行SQL语句
   if (res) {
      printf("删除记录失败：%d-%s\n", res, errmsg );
      return 0;
   }
   return 1;
}



int medialib_delete_all(void)
{
   int res;
   char *errmsg = NULL;
   char sqlcmd[256];
   sprintf(sqlcmd, "DELETE FROM medialib");		// 创建删除所有记录语句
   res = sqlite3_exec( db, sqlcmd, 0, 0, &errmsg );
   if (res) {
      printf("删除记录失败：%d-%s\n", res, errmsg );
      return 0;
   }
   return 1;
}
