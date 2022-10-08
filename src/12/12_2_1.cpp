#include <string.h>						// 使用C语言的字符串处理库
#include <stdio.h> 						// 使用C语言的输入输出库

class String{ 							// 创建字符串类String
public: 
   String(const char* str = NULL); 		// 构造函数
   char *m_data;							// 放置字符串数据的成员
   char *addstr;						// 字符串相加时使用的临时空间
   String& operator + (const String& rhs);	// 重载加法运算符 
}; 
String::String(const char* str)			// 定义构造函数
{ 
   if(str == NULL) {			// 如果输入为空字符串，则添加“\0”表示空串
      m_data = new char[1]; 		// 动态为字符串分配内存空间
      m_data[0] = '\0'; 			// 初始化字符串
   }
   else							// 如果输入非空串，复制该字符串。 
   {
      m_data = new char[strlen(str) + 1];
      strcpy(m_data, str);
   }
}
String& String::operator+(const String& rhs)	// 重载加法运算符
{ 
   addstr = new char[strlen(m_data) + strlen(rhs.m_data) + 1];
   // 为临时空间划分内存，长度为两个字符串之合
   strcpy(addstr, m_data);		// 将第一个字符串复制到临时空间中
   strcat(addstr, rhs.m_data);	// 将第二个字符串追加到临时空间中
   delete [] m_data;			// 释放为m_data成员所划分的内存空间
   m_data = new char[strlen(addstr) + 1];
   // 以临时空间的长度为m_data成员划分内存空间
   strcpy(m_data, addstr);		// 将临时空间内的数据复制给m_data成员
   delete [] addstr;			// 释放临时空间
   return *this;					// 返回this指针
} 

int main() 
{ 
   String s1("I love ");		// 生成字符串对象并初始化
   String s2("C++!"); 
   s1 + s2;						// 将字符串s1与字符串s2相加
   puts(s1.m_data);				// 输出相加后s1字符串
   return 0;
}
