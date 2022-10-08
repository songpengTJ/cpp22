#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window1;
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window1);
	g_signal_connect(G_OBJECT(window1), "delete_event", G_CALLBACK(
			gtk_main_quit), NULL);

	GtkAccelGroup *accel_group;
	accel_group = gtk_accel_group_new();

	GtkWidget *menubar1;
	menubar1 = gtk_menu_bar_new();
	gtk_widget_show(menubar1);
	gtk_container_add(GTK_CONTAINER(window1), menubar1);

	GtkWidget *menuitem1;
	menuitem1 = gtk_menu_item_new_with_mnemonic("文件(_F)");
	gtk_widget_show(menuitem1);
	gtk_container_add(GTK_CONTAINER(menubar1), menuitem1);
	GtkWidget *menuitem1_menu;
	menuitem1_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1), menuitem1_menu);
	GtkWidget *open1;
	  GtkWidget *save1;
	  GtkWidget *close1;
	  GtkWidget *exit1;
	open1 = gtk_menu_item_new_with_mnemonic("打开");
	gtk_widget_show(open1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), open1);
	gtk_widget_add_accelerator(open1, "activate", accel_group, GDK_o,
			(GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	save1 = gtk_menu_item_new_with_mnemonic("保存");
	gtk_widget_show(save1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), save1);
	gtk_widget_add_accelerator(save1, "activate", accel_group, GDK_s,
			(GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	close1 = gtk_menu_item_new_with_mnemonic("关闭");
	gtk_widget_show(close1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), close1);
	gtk_widget_add_accelerator(close1, "activate", accel_group, GDK_c,
			(GdkModifierType) GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

	exit1 = gtk_menu_item_new_with_mnemonic("退出");
	gtk_widget_show(exit1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), exit1);
	gtk_widget_add_accelerator(exit1, "activate", accel_group, GDK_x,
			(GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_main();
	return 0;
}
