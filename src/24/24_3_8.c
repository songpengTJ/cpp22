#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "分栏窗体构件演示");
	gtk_widget_show(window);

	GtkWidget *vpaned1;
		vpaned1 = gtk_viewport_new (NULL, NULL);
		gtk_widget_show (vpaned1);
		gtk_container_add (GTK_CONTAINER (window), vpaned1);

	GtkWidget *image;
	image = gtk_image_new_from_file("/home/Shizhe/图片/22_6.tif");
	gtk_widget_show(image);
	gtk_container_add (GTK_CONTAINER (vpaned1), image);


	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
