#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "比例框架构件演示");
	gtk_widget_show(window);

	GtkWidget *aspectframe;
	aspectframe = gtk_aspect_frame_new (NULL, 0.5, 0.5, 1.25, FALSE);
	gtk_widget_show (aspectframe);
	gtk_container_add (GTK_CONTAINER (window), aspectframe);
	gtk_container_set_border_width (GTK_CONTAINER (aspectframe), 6);

	GtkWidget *alignment;
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (aspectframe), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 7, 0, 12, 0);

	GtkWidget *drawingarea;
	drawingarea = gtk_drawing_area_new ();
	gtk_widget_show (drawingarea);
	gtk_container_add (GTK_CONTAINER (alignment), drawingarea);

	GtkWidget *label;
	label = gtk_label_new ("4 X 3");
	gtk_widget_show (label);
	gtk_frame_set_label_widget (GTK_FRAME (aspectframe), label);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
