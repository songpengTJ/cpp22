#include<stdio.h>
#include<ctype.h>
#define LENGTH 11
int main()
{
    char c[LENGTH] = {"CHinA No.1"};
    int i;
    puts(c);
    for(i=0;i<LENGTH - 1;i++){
        if(isalpha(c[i]) && islower(c[i]) )
        {
            c[i] = toupper(c[i]);
        }
    }
    puts(c);
    return 0;
}