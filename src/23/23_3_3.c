#include < gtk/gtk.h>
#include < gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
void menu_activate(GtkMenuItem *menuitem,
                               GtkWindow *window)	// 菜单项被选择的回调函数
{
   const char *label;
   label = gtk_label_get_label(GTK_LABEL(GTK_BIN(menuitem) -> child));
   // 获取菜单项中的标签构件
   GtkWidget *dialog;
   dialog = gtk_message_dialog_new(window,
                                   GTK_DIALOG_MODAL,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,
                                   "%s菜单被选择",
                                   label);	// 将被选菜单项上的文本传递给消息对话框
   gtk_window_set_title(GTK_WINDOW(dialog), "消息对话框");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}
int main(int argc, char *argv[]) {
   gtk_init(&argc, &argv);
   GtkWidget *window;
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "多级菜单演示");
   gtk_widget_show(window);
   g_signal_connect(G_OBJECT(window), "delete_event",
                    G_CALLBACK(gtk_main_quit), NULL);
   GtkAccelGroup *accel_group;
   accel_group = gtk_accel_group_new();
   GtkWidget *menubar;
   menubar = gtk_menu_bar_new();					// 创建菜单栏构件
   gtk_widget_show(menubar);
   gtk_container_add(GTK_CONTAINER(window), menubar);
   GtkWidget *first1;
   first1 = gtk_menu_item_new_with_mnemonic("第一级(_F)");
   // 创建菜单项构件
   gtk_widget_show(first1);
   gtk_container_add(GTK_CONTAINER(menubar), first1);
   GtkWidget *first1_menu;
   first1_menu = gtk_menu_new();					// 创建二级菜单构件
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(first1), first1_menu);
   GtkWidget *secend1;
   secend1 = gtk_menu_item_new_with_mnemonic("第二级 1");
   gtk_widget_show(secend1);
   gtk_container_add(GTK_CONTAINER(first1_menu), secend1);
   gtk_widget_add_accelerator(secend1, "activate",
                              accel_group, GDK_1,
                              (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);		// 添加快捷方式
   GtkWidget *secend2;
   secend2 = gtk_menu_item_new_with_mnemonic("第二级 2");
   											// 创建二级菜单项构件
   gtk_widget_show(secend2);
   gtk_container_add(GTK_CONTAINER(first1_menu), secend2);
   GtkWidget *secend2_menu;
   secend2_menu = gtk_menu_new();					// 创建三级菜单构件
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(secend2), secend2_menu);
   GtkWidget *third1;
   third1 = gtk_menu_item_new_with_mnemonic("第三级 1");
   												// 创建三级菜单项构件
   gtk_widget_show(third1);
   gtk_container_add(GTK_CONTAINER(secend2_menu), third1);
   gtk_widget_add_accelerator(third1, "activate",
                              accel_group, GDK_2,
                              (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);
   GtkWidget *third2;
   third2 = gtk_menu_item_new_with_mnemonic("第三级 2");
   gtk_widget_show(third2);
   gtk_container_add(GTK_CONTAINER(secend2_menu), third2);
   gtk_widget_add_accelerator(third2, "activate",
                                   accel_group, GDK_3,
                                  (GdkModifierType) GDK_CONTROL_MASK,
                                  GTK_ACCEL_VISIBLE);
   g_signal_connect((gpointer) secend1, "activate",
                        G_CALLBACK(menu_activate),// 菜单选择时连接回调函数
                       (gpointer) window);		   // 窗体构件的指针作为参数79	被传递
   g_signal_connect((gpointer) third1, "activate",
                        G_CALLBACK(menu_activate),
                        (gpointer) window);
   g_signal_connect((gpointer) third2, "activate",
                        G_CALLBACK(menu_activate),
                       (gpointer) window);
   gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
   											   // 使快捷方式生效
   gtk_main();
   return 0;
}
