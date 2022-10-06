#include<stdio.h>
#include<stdlib.h>
int main()
{
    const char *s ={"87.99%已完成"};
    char *p;
    double d;
    d = strtod(s,&p);

    printf("数值是: %.2f\n",d);
    printf("%.2f后的字符串是：%s\n",d,p);

    long l = 1234567890;
    printf("数值是: %ld\n",l);
    
    return 0;
}