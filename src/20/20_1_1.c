#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 #include <fcntl.h>											// 提供open()函数
#include <sys/types.h>										// 提供mode_t类型
#include <sys/stat.h>										// 提供open()函数的符号
#include <unistd.h>											// 提供close()函数

typedef struct _calllist callist;
struct _calllist {
   long id;				// 记录编号
   int type;				// 通话类型
   long telnum;				// 对方号码
   char btime[14];				// 通话起始时间
   long tcount;				// 通话时长
   float charge_rate;			// 费率
   float charge_sum;		// 总费用
};




int selectdb(callist **cl, int f)						// 定义查询记录函数
{
   int i = sizeof(callist);						// 获取记录长度
   long length = lseek(f, 0, SEEK_END);				// 获取文件长度
   if (length < i) {
	   puts("无记录");
      return -1;								// 表示无记录
   }
   if (*cl != NULL)
      free(*cl);									// 释放原有内存空间
   *cl = malloc(length);							// 申请内存空间
   lseek(f, 0, SEEK_SET);						// 将文件指针指向文件开始
   if(read(f, *cl, length) != length) {					// 将所有记录读取到缓冲区
      perror("读取数据失败");
      return -2;
   }
   return 0;
}




int insertdb(callist *cr, int f, callist *cl)			// 定义插入记录函数
{
   int i = sizeof(callist);						// 获取记录长度
   int length = lseek(f, 0, SEEK_END);				// 获取文件长度
   cr -> id = (cl + length / i - 1) -> id + 1;
   lseek(f, 0, SEEK_END);						// 将文件指针指向文件结尾
   if(write(f, cr, i) != i) {							// 将所有记录写入到文件末端
      perror("插入记录失败");
      return -1;
   }
   return 0;
}




int changedb(callist *cr, int f, callist *cl)		// 定义查询记录函数
{
   int i = sizeof(callist);		// 获取记录长度
   long length = lseek(f, 0, SEEK_END);		// 获取文件长度
   long j;
   for(j = 0; j <= length / i; j++) {
      if ((cl + j) -> id == cr -> id)
     	  break;
      }
   memcpy(cl + j, cr, i);
   lseek(f, 0, SEEK_SET);			// 将文件指针指向文件开始
   if(write(f, cl, length) != length) {
      perror("读取数据失败");
      return -1;
   }
   return 0;
}




int deletedb(callist *cr, int *f, callist **cl)		// 定义查询记录函数
{
   int i = sizeof(callist);		// 获取记录长度
   long length = lseek(*f, 0, SEEK_END);		// 获取文件长度
   long j;
   for(j = 0; j <= length / i; j++) {
      if ((*cl + j) -> id == cr -> id)
     	  break;
      }
   memmove(*cl + j, *cl + j + 1, length - i * (j + 1));
   length -= i;
   close(*f);
	*f = open("listdb", O_RDWR | O_TRUNC);
   if(write(*f, *cl, length) != length) {
      perror("读取数据失败");
      return -1;
   }
   return 0;
}
void printdb(callist *cl, int f)
{
	int i = sizeof(callist);
	long length = lseek(f, 0, SEEK_END);				// 获取文件长度
	int j;
	char btime[15] = {0};
	for(j = 0 ;j < length / i; j++) {
		memcpy(btime, (cl + j) -> btime, 14);
		printf("%ld, %d, %ld, %14s, %ld, %1.2f, %1.2f\n",
				(cl + j) -> id,
				(cl + j) -> type,
				(cl + j) -> telnum,
				btime,
				(cl + j) -> tcount,
				(cl + j) -> charge_rate,
				(cl + j) -> charge_sum);
	}
}

int main()
{
	int f;
	callist cr = {1,0,12345,"20090301120011",30,0.36,0.36};
	callist *cl;
	cl = NULL;
	f = open("listdb", O_RDWR | O_CREAT, 0664);
	if (f == -1) {
		perror("打开文件错误");
		return 1;
	}
	puts("原始文件输出：");
	if (selectdb(&cl, f) == -2)
		return 1;
	printdb(cl, f);
	puts("插入操作后文件输出：");
	insertdb(&cr, f, cl);
	if (selectdb(&cl, f) == -2)
		return 1;
	printdb(cl, f);
	puts("修改文件输出：");
	if (selectdb(&cl, f) == -2)
		return 1;
	printdb(cl, f);

	cr.id = 2;
	cr.telnum = 54321;

	deletedb(&cr, &f, &cl);
	res = selectdb(&cl, f);
		if (res == -2) {
			puts("读取数据文件错");
			return 1;
		}
		printdb(cl, f);
	close(f);
	return 0;
}
