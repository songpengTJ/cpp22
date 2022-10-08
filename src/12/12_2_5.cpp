#include <iostream>
using namespace std;
template <typename T> T Add2Value(T a, T b)
// 定义模板T，计算任何数据类型两个数之和
{
   T result;								// 定义返回类型
   result = a + b;						// 计算两个数之和
   return (result);						// 返回两个数之和的计算结果
}
int main ()
{
   int i = 11, j = 645, k;				// 定义整型变量
   float l = 2.718, m = 34.23, n;		// 定义单精度浮点型变量
   k = Add2Value(i, j);					// 利用模板计算整型变量之和
   n = Add2Value(l, m);					// 利用模板计算单精度浮点型变量之16	和
   cout << k << endl;
   cout << n << endl;
   return 0;
}
