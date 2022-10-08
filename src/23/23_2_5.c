#include  gtk/gtk.h>
int main(int argc, char *argv[])
{
   int i;
   const char *lb[6] = {"菜单",
                            "小尺寸工具条",
                            "大尺寸工具条",
                            "按钮",
                            "拖放",
                            "对话框"};
   gtk_init(&argc, &argv);
   GtkWidget *window1;
   window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_widget_show(window1);
   gtk_window_set_title(GTK_WINDOW(window1), "图片库演示");
   g_signal_connect(G_OBJECT(window1), "delete_event",
                    G_CALLBACK(gtk_main_quit), NULL);
   GtkWidget *table1;
   table1 = gtk_table_new(2, 6, FALSE);			// 创建表格容器
   gtk_widget_show(table1);
   gtk_container_add(GTK_CONTAINER (window1), table1);
   GtkWidget *image[6];								// 创建图像构件数组
   GtkWidget *label[6];								// 创建标签构件数组
   for(i = 0; i < 6; i++) {
      image[i] = gtk_image_new_from_stock(GTK_STOCK_COPY,
      // 定义图像库中的图像名
                                  GTK_ICON_SIZE_MENU + i);// 定义图像尺寸
      gtk_widget_show(image[i]);
      gtk_table_attach(GTK_TABLE (table1), image[i], i, i + 1, 0, 1,
                       (GtkAttachOptions)(GTK_EXPAND | GTK_FILL),
                       (GtkAttachOptions)(GTK_EXPAND | GTK_FILL), 0, 0);
// 将图像放入表格容器
      label[i] = gtk_label_new (lb[i]);
      gtk_widget_show (label[i]);
      gtk_table_attach (GTK_TABLE (table1), label[i], i, i + 1, 1, 2,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);
   }
   gtk_main();
   return 0;
}
