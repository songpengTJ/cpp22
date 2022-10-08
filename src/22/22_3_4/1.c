#include <glib.h>
int main()
{
   GString *s;								// 定义一个字符串类型
   s = g_string_new("Hello");					// 输入字符串
   g_print("%s\n", s->str);						// 输出字符串
   s = g_string_append(s," World!");				// 在字符串对象后追加内容
   g_print("%s\n",s->str);
   s = g_string_erase(s,0,6);					// 删除字符串从位置0开始的6个字符
   g_print("%s\n",s->str);
   s = g_string_prepend(s,"Liunx ");				// 在字符串最前面插入内容
   g_print("%s\n",s->str);
   s = g_string_insert(s,6,"Programming");		// 在指定位置上插入内容
   g_print("%s\n",s->str);
   return 0;
}
