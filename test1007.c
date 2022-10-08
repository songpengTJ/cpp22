#include<stdio.h>
//#include<stdlib.h>
#include<string.h>

int main()
{
    char s1[20];
    const char *s2 = "Linux Kernel";
    memcpy(s1,s2,20);
    puts(s1);
    printf("%s,%d\n",s1,strlen(s1) );
    memcpy(s1,s1+6,7);
    puts(s1);
    printf("%d\n",strlen(s1));
    printf("比较s1和s2第6个开始的7个字节的结果是：%d\n",memcmp(s1,s2+6,7));
    memchr(s2,'e',13);
    puts(s2);
    char *s3 = (char *)memset(s1,'A',3);
    puts(s1);
    puts(s3);

    puts(strerror(2));

    float score = 123456789.51015926;
    printf("%7.2f\n",score);
}