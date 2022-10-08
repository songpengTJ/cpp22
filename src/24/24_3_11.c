#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "工具栏构件演示");
	gtk_widget_show(window);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 15);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkWidget *toolbar;
	GtkIconSize tmp_toolbar_icon_size;
	toolbar = gtk_toolbar_new ();
	gtk_widget_show (toolbar);
	gtk_box_pack_start (GTK_BOX (vbox), toolbar, FALSE, FALSE, 0);
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);
	tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar));

	g_print("%d",tmp_toolbar_icon_size);

	GtkWidget *toolbutton1;
	toolbutton1 = (GtkWidget*) gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	gtk_widget_show (toolbutton1);
	gtk_container_add (GTK_CONTAINER (toolbar), toolbutton1);

	GtkWidget *toolbutton2;
	toolbutton2 = (GtkWidget*) gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	gtk_widget_show (toolbutton2);
	gtk_container_add (GTK_CONTAINER (toolbar), toolbutton2);

	GtkWidget *toolbutton3;
	toolbutton3 = (GtkWidget*) gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	gtk_widget_show (toolbutton3);
	gtk_container_add (GTK_CONTAINER (toolbar), toolbutton3);

	GtkWidget *separatortoolitem;
	separatortoolitem = (GtkWidget*) gtk_separator_tool_item_new ();
	gtk_widget_show (separatortoolitem);
	gtk_container_add (GTK_CONTAINER (toolbar), separatortoolitem);

	GtkWidget *toolbutton4;
	toolbutton4 = (GtkWidget*) gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
	gtk_widget_show (toolbutton4);
	gtk_container_add (GTK_CONTAINER (toolbar), toolbutton4);
	gtk_tool_item_set_is_important (GTK_TOOL_ITEM (toolbutton4), TRUE);

	GtkWidget *textview;
	textview = gtk_text_view_new ();
	gtk_widget_show (textview);
	gtk_box_pack_start (GTK_BOX (vbox), textview, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
