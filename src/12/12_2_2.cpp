#include <iostream>
using namespace std;				// 使用std名字空间下的所有操作符
Class Cstd							// 定义父类Cstd
{
public:
   void set_values (int a, int b) { width=a; height=b;}
protected:
   int width;						// 图形的底
   int height;						// 图形的高
};
class Crect: public Cstd			// 定义子类Crect
{
public:
   int area (void){ return (width * height); }
   // 定义子类成员函数，用于计算矩形面积
};
class Cdelt: public Cstd			// 定义子类Cdelt
{
public:
   int area (void){ return (width * height / 2); }
   // 定义子类成员函数，用于计算三角形面积
};
    
int main () {
   Crect rect;						// 生成对象
   Cdelt delt;
   rect.set_values (4,5);			// 使用对象的成员函数赋值（父类中定义）
   delt.set_values (4,5);
   cout << rect.area() << endl;		// 使用对象的成员函数输出（子类中定义）
   cout <<delt.area() << endl;
   return 0;
}
