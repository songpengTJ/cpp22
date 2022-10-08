#include <stdio.h>
void common_multiple(a, b, c)

int a, b, c;
{
	if (a > 0 && b > 0 && c > 0) {
		if (a % (b * c) == 0) {
			printf("最小公倍数是%d", a);
			return;
		}
		if (b % (a * c) == 0) {
			printf("最小公倍数是%d", b);
			return;
		}
		if (c % (a * b) == 0) {
			printf("最小公倍数是%d", c);
			return;
		}
		int i;
		for (i = a * b; i < a * b * c; i += a * b) {
			if (i % c == 0) {
				printf("最小公倍数是%d", i);
				return;
			}
		}
	}
	else
		puts("无公倍数");
}

int main()
{
	common_multiple(2, 6, 32);
	return 0;
}
