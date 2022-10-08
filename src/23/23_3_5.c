#include <gtk/gtk.h>
void son1_activate(GtkCheckMenuItem *menuitem,
                       GtkLabel *label)			// 复选菜单项的回调函数
{
   const char *citem;
   if (gtk_check_menu_item_get_active(menuitem))// 判断复选菜单项
      citem = "复选菜单状态为：选中";
   else
      citem = "复选菜单状态为：未选中";
   gtk_label_set_label(label, citem);			// 修改窗体中的标签
}
void son2_activate(GtkCheckMenuItem *son2,
                      GtkCheckMenuItem *son1)
{
   if (gtk_check_menu_item_get_active(son1))
      gtk_check_menu_item_set_active(son1, FALSE);// 改变复选菜单项状态
}
int main(int argc, char *argv[])
{
   gtk_init(&argc, &argv);
   GtkWidget *window;
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "复选菜单演示");
   gtk_widget_show(window);
   g_signal_connect(G_OBJECT(window), "delete_event",
         G_CALLBACK(gtk_main_quit), NULL);
   GtkWidget *vbox;
   vbox = gtk_vbox_new (FALSE, 0);				// 创建一个横向盒容器
   gtk_widget_show (vbox);
   gtk_container_add(GTK_CONTAINER(window), vbox);
   GtkWidget *menubar;
   menubar = gtk_menu_bar_new ();
   gtk_widget_show (menubar);
   gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
   GtkWidget *rootitem;
   rootitem = gtk_menu_item_new_with_label("菜单");	// 创建顶级菜单项
   gtk_widget_show(rootitem);
   gtk_container_add(GTK_CONTAINER(menubar), rootitem);
   GtkWidget *rootitem_menu;
   rootitem_menu = gtk_menu_new();
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootitem), rootitem_menu);
   GtkWidget *son1;
   son1 = gtk_check_menu_item_new_with_label("复选菜单项");
   // 创建一个复选菜单项
   gtk_widget_show(son1);
   gtk_container_add(GTK_CONTAINER(rootitem_menu), son1);
   GtkWidget *son2;
   son2 = gtk_menu_item_new_with_label("清除复选菜单项状态");
   // 创建一个菜单项
   gtk_widget_show(son2);
   gtk_container_add(GTK_CONTAINER(rootitem_menu), son2);
   GtkWidget *label;
   label = gtk_label_new("请修改复选菜单项状态");
   gtk_widget_show(label);
   gtk_misc_set_padding(GTK_MISC(label), 0, 80);
   gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
   g_signal_connect((gpointer) son1, "activate", G_CALLBACK(son1_
   activate),
            (gpointer) label);
   g_signal_connect((gpointer) son2, "activate", G_CALLBACK(son2_
   activate),
            (gpointer) son1);
   gtk_main();
   return 0;
}
