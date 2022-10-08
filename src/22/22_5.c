#include <cairo.h>							// 包含Cairo库主要函数
#include <cairo-png.h>						// 包含Cairo库png格式图形函数
#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *file;
   file = fopen("a.png", "w");					// 打开一个文件，写入，文件名为a.png
   cairo_t *cr;								// 声明一支画笔
   cr = cairo_create();						// 创建画笔
   cairo_set_target_png(cr,					// 定义画布名
                      file,					// 目标文件标识符号
                      CAIRO_FORMAT_ARGB32,// 画布格式
                      400,					// 画布的宽
                      400);					// 画布的高
   cairo_set_rgb_color(cr, 0, 1, 0);				// 设置画笔颜色，也就是红，绿，蓝，这里设置成绿色
   cairo_rectangle(cr, 10, 10, 200, 200);			// 画一个方块，位置从坐标(10,10)开始，宽200，高200
   cairo_fill(cr);								// 填充，使用的颜色是上面设置的颜色。
   cairo_move_to(cr, 250, 200);				// 将画笔移动到坐标(250,200)
   cairo_select_font (cr, 
                   "DongWen--Song",			// 设置字体名
                   CAIRO_FONT_SLANT_NORMAL,			// 字体样式
                   CAIRO_FONT_WEIGHT_NORMAL);		// 字体宽度
   cairo_scale_font(cr, 60);					// 缩放字体到60倍
   cairo_show_text(cr, "hello world");			// 画出一个串
   cairo_destroy(cr);							// 删除画笔
   fclose(file);								// 关闭文件
   return 0;
}
