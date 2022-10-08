#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "图像菜单演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkAccelGroup *accel_group;
	accel_group = gtk_accel_group_new();

	GtkWidget *menubar;
	menubar = gtk_menu_bar_new();
	gtk_widget_show(menubar);
	gtk_container_add(GTK_CONTAINER(window), menubar);

	GtkWidget *menuitem_file;
	menuitem_file = gtk_menu_item_new_with_mnemonic ("文件(_F)");
	gtk_widget_show (menuitem_file);
	gtk_container_add (GTK_CONTAINER (menubar), menuitem_file);

	GtkWidget *file_menu;
	file_menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_file), file_menu);

	GtkWidget *new1;
	new1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, accel_group);
	gtk_widget_show (new1);
	gtk_container_add (GTK_CONTAINER (file_menu), new1);

	GtkWidget *open1;
	open1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, accel_group);
	gtk_widget_show (open1);
	gtk_container_add (GTK_CONTAINER (file_menu), open1);

	GtkWidget *save1;
	save1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE, accel_group);
	gtk_widget_show (save1);
	gtk_container_add (GTK_CONTAINER (file_menu), save1);

	GtkWidget *saveas1;
	saveas1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE_AS, accel_group);
	gtk_widget_show (saveas1);
	gtk_container_add (GTK_CONTAINER (file_menu), saveas1);

	GtkWidget *quit1;
	quit1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, accel_group);
	gtk_widget_show (quit1);
	gtk_container_add (GTK_CONTAINER (file_menu), quit1);

	GtkWidget *menuitem_edit;
	menuitem_edit = gtk_menu_item_new_with_mnemonic("编辑(_E)");
	gtk_widget_show(menuitem_edit);
	gtk_container_add(GTK_CONTAINER(menubar), menuitem_edit);

	GtkWidget *menuitem_view;
	menuitem_view = gtk_menu_item_new_with_mnemonic ("查看(_V)");
	gtk_widget_show (menuitem_view);
	gtk_container_add (GTK_CONTAINER (menubar), menuitem_view);


	g_signal_connect((gpointer) new1, "activate", G_CALLBACK(menu_activate),
			(gpointer) window);
	g_signal_connect((gpointer) open1, "activate", G_CALLBACK(menu_activate),
			(gpointer) window);
	g_signal_connect((gpointer) save1, "activate", G_CALLBACK(menu_activate),
			(gpointer) window);
	g_signal_connect((gpointer) saveas1, "activate", G_CALLBACK(menu_activate),
				(gpointer) window);
	g_signal_connect((gpointer) quit1, "activate", G_CALLBACK(gtk_main_quit),
				NULL);


	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
	gtk_main();
	return 0;
}
