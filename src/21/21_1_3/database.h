#include <sqlite3.h>									// ����SQLite�ӿں���
sqlite3 *db = NULL;									// ����һ��ȫ�ֵ����ݿ��ʶ��
int open_database(const char *dbfile);					// �������ݿ�򿪺���ԭ��
int close_database(void);								// �������ݿ�رպ���
