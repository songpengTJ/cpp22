#include "baby.h"
enum { BABY_BORN, LAST_SIGNAL };						// 定义枚举常量
static gint baby_signals[LAST_SIGNAL] = { 0 };
static void baby_cry (void);
static void baby_born(void);
static void baby_init(Baby *baby);
static void baby_class_init(BabyClass *babyclass);
GType baby_get_type(void)								// 返回类的类型函数
{
   static GType baby_type = 0;
   if(!baby_type)
   {
      static const GTypeInfo baby_info = {
         sizeof(BabyClass),
         NULL,NULL,
         (GClassInitFunc)baby_class_init,
         NULL,NULL,
         sizeof(Baby),
         0,
         (GInstanceInitFunc)baby_init
      };
      baby_type = g_type_register_static(G_TYPE_OBJECT,"Baby",&baby_info,0);
   }
   return baby_type;
}
static void baby_init(Baby *baby)							// Baby对象初始化函数
{
   baby->age = 0;
   baby->name = "none";
   baby->cry = baby_cry;
}
static void baby_class_init(BabyClass *babyclass)				// BabyClass对象初始化函数
{
   babyclass->baby_born = baby_born;
   baby_signals[BABY_BORN] = g_signal_new("baby_born",
            BABY_TYPE,
            G_SIGNAL_RUN_FIRST,
            G_STRUCT_OFFSET(BabyClass,baby_born),
            NULL,NULL,
            g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE, 0, NULL);
}
Baby *baby_new(void)									// 创建新对象函数
{
   Baby *baby;
   baby = g_object_new(BABY_TYPE, NULL);
   g_signal_emit(baby,baby_signals[BABY_BORN],0);
   return baby;
}
int baby_get_age(Baby *baby)								// 返回age成员的值
{
   return baby->age;
}
void baby_set_age(Baby *baby, int age)						// 设置age成员的值
{
   baby->age = age;
}
char *baby_get_name(Baby *baby)							// 返回name成员的值
{
   return baby->name;
}
void baby_set_name(Baby *baby, char *name)					// 设置name成员的值
{
   baby->name = name;
}
Baby*  baby_new_with_name(gchar *name)					// 创建新对象并对age赋值函数
{
   Baby* baby;
   baby = baby_new();
   baby_set_name(baby, name);
   return baby;
}
Baby*  baby_new_with_age(gint age)						// 创建新对象并对name赋值函数
{
   Baby* baby;
   baby = baby_new();
   baby_set_age(baby, age);
   return baby;
}
Baby *baby_new_with_name_and_age(gchar *name, gint age)		// 创建新对象并对name和age赋值函数
{
   Baby *baby;
   baby = baby_new();
   baby_set_name(baby,name);
   baby_set_age(baby,age);
   return baby;
}
static void baby_cry (void)
{
   g_print("婴儿正在哭泣……\n");
}
static void baby_born(void)
{
   g_print("消息：一个婴儿出生了。\n");
}
void  baby_info(Baby *baby)
{
   g_print("婴儿的名字是：%s\n", baby->name);
   g_print("婴儿的年龄是%d\n", baby->age);
}
