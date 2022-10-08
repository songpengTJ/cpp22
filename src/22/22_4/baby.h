#ifndef __BABY_H__
#define __BABY_H__
#include <glib-object.h>
#define BABY_TYPE (baby_get_type())
#define BABY(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), BABY_TYPE, baby))	// 定义对象转换宏
typedef struct _Baby Baby;												// 定义Baby结构
typedef struct _BabyClass BabyClass;										// 定义类结构
struct _Baby {
   GObject parent;														// 定义类成员，父类
   gint age;
   gchar *name;
   void (*cry)(void);														// 类的行为
};
struct _BabyClass {														// 定义类结构
   GObjectClass parent_class;
   void (*baby_born)(void);												//类似于C++构造函数
};
GType baby_get_type(void);
Baby* baby_new(void);
int baby_get_age(baby *baby);
void baby_set_age(baby *baby, int age);
char* baby_get_name(baby *baby);
void baby_set_name(baby *baby, char *name);
baby* baby_new_with_name(gchar *name);
baby* baby_new_with_age(gint age);
baby* baby_new_with_name_and_age(gchar *name, gint age);
void baby_info(baby *baby);
#endif
