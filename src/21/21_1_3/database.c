#include "database.h"
int open_database(const char *dbfile)					// �������ݿ�򿪺���
{
   int result;
   result = sqlite3_open(dbfile, &db );					// ��һ�����ݿ�
   return result;
}
int close_database(void)								// �������ݿ�رպ���
{
   int result;
   result = sqlite3_close(db);
   return result;
}
