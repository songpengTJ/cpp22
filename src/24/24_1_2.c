#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

static void set_label(GtkWidget *window)
{
	char citem[100];
	sprintf(citem, "窗体尺寸为：%d ＊ %d",
	               window->allocation.width,
	               window->allocation.height);

	gtk_window_set_title(GTK_WINDOW(window), citem);
}
int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *label;
	label = gtk_label_new ("改变窗体大小后，显示窗体尺寸");
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_POPUP);

	gtk_window_set_title(GTK_WINDOW(window), "构件尺寸演示");
	gtk_widget_set_size_request(window, 200, 200);
	gtk_container_add (GTK_CONTAINER (window), label);
	gtk_widget_show(label);
	gtk_widget_show(window);
	g_signal_connect((gpointer) window, "size-allocate",
							G_CALLBACK(set_label),
							NULL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
