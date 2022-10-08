#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "固定容器构件演示");
	gtk_widget_show(window);

	GtkWidget *fixed;
	fixed = gtk_fixed_new();
	gtk_widget_show(fixed);
	gtk_container_add(GTK_CONTAINER(window), fixed);

	GtkWidget *textview;
	textview = gtk_text_view_new();
	gtk_widget_show(textview);
	gtk_fixed_put(GTK_FIXED(fixed), textview, 80, 24);
	gtk_widget_set_size_request(textview, 296, 216);

	GtkWidget *label;
	label = gtk_label_new("备注");
	gtk_widget_show(label);
	gtk_fixed_put(GTK_FIXED(fixed), label, 24, 24);
	gtk_widget_set_size_request(label, 39, 17);

	GtkWidget *button;
	button = gtk_button_new_from_stock("gtk-quit");
	gtk_widget_show(button);
	gtk_fixed_put(GTK_FIXED(fixed), button, 280, 248);
	gtk_widget_set_size_request(button, 98, 40);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
