#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
 
void destroy(GtkWidget *button, gpointer data)
{
	gtk_widget_destroy (button);
}

void make_label(GtkWidget *button, GtkWidget *window)
{
	GtkWidget *label;
	label = gtk_label_new("按钮已被删除");
	gtk_widget_show(label);
	gtk_container_add (GTK_CONTAINER (window), label);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "destroy信号演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete-event",
					G_CALLBACK(gtk_main_quit), NULL);
	GtkWidget *button;
	button = gtk_button_new_with_label ("删除本按钮");
	gtk_widget_show (button);
	gtk_container_add (GTK_CONTAINER (window), button);
	g_signal_connect(G_OBJECT(button), "clicked",
					G_CALLBACK(destroy), NULL);
	g_signal_connect(G_OBJECT(button), "destroy",
						G_CALLBACK(make_label), (gpointer) window);
	gtk_main();
	return 0;
}
