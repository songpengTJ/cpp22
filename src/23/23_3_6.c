#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

void radio_activate(GtkRadioMenuItem *menuitem,
		              GtkLabel *label) {
	char citem[100];
	sprintf(citem, "被选中的单选菜单项为：%s",
			gtk_label_get_label(GTK_LABEL(GTK_BIN(menuitem) -> child)));
	gtk_label_set_label(label, citem);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "单选菜单演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkWidget *menubar;
	menubar = gtk_menu_bar_new ();
	gtk_widget_show (menubar);
	gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

	GtkWidget *rootitem;
	rootitem = gtk_menu_item_new_with_label ("菜单");
	gtk_widget_show (rootitem);
	gtk_container_add (GTK_CONTAINER (menubar), rootitem);

	GtkWidget *rootitem_menu;
	rootitem_menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (rootitem), rootitem_menu);

	GSList *group = NULL;
	GtkWidget *son1;
	son1 = gtk_radio_menu_item_new_with_label (group, "单选菜单项1");
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (son1), TRUE);
	group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (son1));
	gtk_widget_show (son1);
	gtk_container_add (GTK_CONTAINER (rootitem_menu), son1);

	GtkWidget * son2;
	son2 = gtk_radio_menu_item_new_with_label(group, "单选菜单项2");
	group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(son2));
	gtk_widget_show(son2);
	gtk_container_add(GTK_CONTAINER(rootitem_menu), son2);

	GtkWidget * son3;
	son3 = gtk_radio_menu_item_new_with_label(group, "单选菜单项3");
	group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(son3));
	gtk_widget_show(son3);
	gtk_container_add(GTK_CONTAINER(rootitem_menu), son3);

	GtkWidget * son4;
	son4 = gtk_radio_menu_item_new_with_label(group, "单选菜单项4");
	group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(son4));
	gtk_widget_show(son4);
	gtk_container_add(GTK_CONTAINER(rootitem_menu), son4);

	GtkWidget * son5;
	son5 = gtk_radio_menu_item_new_with_label(group, "单选菜单项5");
	group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(son5));
	gtk_widget_show(son5);
	gtk_container_add(GTK_CONTAINER(rootitem_menu), son5);

	GtkWidget *label;
	label = gtk_label_new ("请修改单选菜单项状态");
	gtk_widget_show (label);
	gtk_misc_set_padding (GTK_MISC (label), 0, 120);
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

	g_signal_connect((gpointer) son1, "activate", G_CALLBACK(radio_activate),
				(gpointer) label);
	g_signal_connect((gpointer) son2, "activate", G_CALLBACK(radio_activate),
				(gpointer) label);

	gtk_main();
	return 0;
}
