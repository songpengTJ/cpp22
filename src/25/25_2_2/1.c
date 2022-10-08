#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
 
gint delete_event(GtkWidget *window, GdkEvent *event, gpointer data)
{
	gtk_widget_hide(window);
	return TRUE;
}

void window2_sh(GtkWidget *button, GtkWidget *window)
{
	gboolean visibel;
	g_object_get(window, "visible", &visibel, NULL);
	if(visibel)
		gtk_widget_hide (window);
	else
		gtk_widget_show (window);
}

void window2_show(GtkWidget *window, GtkLabel *label)
{
	gtk_label_set_label(label, "子窗体显示");
}
void window2_hide(GtkWidget *window, GtkLabel *label)
{
	gtk_label_set_label(label, "子窗体隐藏");
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "show/hide信号演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete-event",
					G_CALLBACK(gtk_main_quit), NULL);
	GtkWidget *window2;
	window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window2), "子窗体");
	g_signal_connect(G_OBJECT(window2), "delete-event",
						  G_CALLBACK(delete_event), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkWidget *label;
	label = gtk_label_new("");
	gtk_widget_show(label);
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

	GtkWidget *button;
	button = gtk_button_new_with_label ("显示/隐藏子窗体");
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(button), "clicked",
					     G_CALLBACK(window2_sh), (gpointer) window2);
	g_signal_connect(G_OBJECT(window2), "show",
					     G_CALLBACK(window2_show), (gpointer) label);
	g_signal_connect(G_OBJECT(window2), "hide",
					     G_CALLBACK(window2_hide), (gpointer) label);
	gtk_main();
	return 0;
}
