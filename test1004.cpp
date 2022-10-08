#include<stdio.h>
//#include<stdlib.h>
#include<string.h>

void page132()
{
    const char *s1 = "Happy new Year!";
    const char *s2 = "Year";
    const char *s3 = "pye HwNa";
    const char *p;

    p = strchr( s1, 'a' );
    printf("在字符串s1中首次出现字母'a'的位置：");
    p!=NULL?puts(p):puts("无");

    p = strrchr( s1 , 'a' );
    printf("在字符串s1中最后一次出现字母'a'的位置：");
    p!=NULL?puts(p):puts("无");

    printf("字符串从首字符开始只包括字符串s2所包含字符的分段长度是：%d\n",strcspn(s1,s2));
    printf("字符串从首字符开始只包括字符串s3所包含字符的分段长度是：%d\n",strspn(s1,s3));

    p=strpbrk(s1,s2);
    printf("字符串s2中任意字符出现在s1中的任意位置是：");
    p!=NULL?puts(p):puts("无");

    p=strstr(s1,s2);
    printf("字符串s2出现在s1中的位置是：");
    p!=NULL?puts(p):puts("无");
}

int main(){
    char s[] = "Linux has come a long way";
    char *p;
    p= strtok(s," ");
    while(p!=NULL){
        puts(p);
        p = strtok(NULL," ");
    }
    page132();
}