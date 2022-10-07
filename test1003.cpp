#include<stdio.h>
#include<stdlib.h>
#define LENGTH  6

int main0()
{
    const char *s ={"87.99%已完成"};
    char *p;
    double d;
    d = strtod(s,&p);

    printf("数值是: %.2f\n",d);
    printf("%.2f后的字符串是：%s\n",d,p);

    long l = 1234567890;
    printf("数值是: %ld\n\n",l);
    
    return 0;
}
 
 int main()
 {

    main0();

    double d =123.45678;
    char p[LENGTH+2];
    gcvt(d,LENGTH,p);
    puts(p);
    char q[100];
    sprintf(q,"%4.2f%s\n",d,"已转换");
    puts(q);

    return 0;
 }