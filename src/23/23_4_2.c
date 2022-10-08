#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "分隔菜单项演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkAccelGroup *accel_group;
	accel_group = gtk_accel_group_new();

	GtkWidget *menubar;
	menubar = gtk_menu_bar_new ();
	gtk_widget_show (menubar);
	gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

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

	GtkWidget *sepitem;
	sepitem = gtk_separator_menu_item_new();
	gtk_widget_show (sepitem);
	gtk_container_add (GTK_CONTAINER (file_menu), sepitem);

	GtkWidget *quit1;
	quit1 = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, accel_group);
	gtk_widget_show (quit1);
	gtk_container_add (GTK_CONTAINER (file_menu), quit1);



	gtk_main();
	return 0;
}
