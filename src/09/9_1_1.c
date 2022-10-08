#include <stdio.h>
#define PI 3.141593
float cylinder_area(float r, float h);

int main()
{
	float r, h, s;
	puts("请输入圆柱体的半径和高：");
	if (scanf("%f,%f", &r, &h) == 2)
		s = cylinder_area(r, h);
	else
		puts("您输入的数据格式不合法！");
	printf("\n该圆柱体的表面积为： %f\n", s);
	return 0;
}

float cylinder_area(float r, float h)
{
	float s;
	s = 2 * (PI * r * r) + (2 * PI * r * h);
	return s;
}
