#include <stdio.h>
#include "database.h"

int main()
{
   const char *dbfile = "data.sqlite"						// �������ݿ��ļ���
   int res;
   char *errmsg = NULL;
   res = open_database(dbfile);						// �����ݿ�
   if (res != 0) {
      printf("���ݿ��ʧ�ܣ�%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("���ݿ��Ѵ�");
   const char *sqlcmd = "CREATE TABLE call_list (
                        id INTEGER PRIMARY KEY, \
                        type NUMERIC, \
                        telnum NUMERIC, \
                        bttime TEXT, \
                        tcount NUMERIC, \
                        charge_rate NUMERIC, \			// ��\���������ڽ�һ�з�Ϊ����
                        charge_sum NUMERIC)";		// ����һ��ͨ���嵥���ݱ�
   res = sqlite3_exec(db, sqlcmd, NULL, NULL, &errmsg);	// ִ��SQL����
   if (res != SQLITE_OK )
      printf("ִ��ʧ�ܣ����룺%d-%s\n", res, errmsg);
   else
      puts("ִ�гɹ���������һ�����ݱ�");
   res = close_database();
   if (res != 0) {
      printf("���ݿ�ر�ʧ�ܣ�%s", sqlite3_errmsg(db));
      return 1;
   }
   else
      puts("���ݿ��ѹر�");
   return 0;
}
