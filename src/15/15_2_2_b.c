// 这是第二个文件，调用者，文件名为doexec.c
#include <unistd.h>
#include <stdio.h>
extern char **environ;
int main(int argc, char* argv[])
{
   puts("此信息可能无法输出");
   execve("beexec",argv,environ); 		// 用beexec程序替换进程执行映像
   puts("正常情况此信息无法输出");
}
