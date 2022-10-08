#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "对齐构件演示");
	gtk_widget_show(window);

	GtkWidget *vbox;
	vbox = gtk_vbox_new(TRUE, 0);
	gtk_widget_set_size_request(vbox, 300, 300);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show(vbox);

	GtkWidget *alig1;
	alig1 = gtk_alignment_new(0,0,0,0);
	gtk_box_pack_start (GTK_BOX(vbox), alig1, FALSE, FALSE, 0);
	gtk_widget_show(alig1);

	GtkWidget *label1;
	label1 = gtk_label_new("左上对齐");
	gtk_widget_show(label1);
	gtk_container_add(GTK_CONTAINER(alig1), label1);

	GtkWidget *alig2;
	alig2 = gtk_alignment_new(1,0,0,0);
	gtk_box_pack_start (GTK_BOX(vbox), alig2, FALSE, FALSE, 0);
	gtk_widget_show(alig2);

	GtkWidget *label2;
	label2 = gtk_label_new("右上对齐");
	gtk_widget_show(label2);
	gtk_container_add(GTK_CONTAINER(alig2), label2);

	GtkWidget *alig3;
	alig3 = gtk_alignment_new(0,1,0,0);
	gtk_box_pack_start (GTK_BOX(vbox), alig3, FALSE, FALSE, 0);
	gtk_widget_show(alig3);

	GtkWidget *label3;
	label3 = gtk_label_new("左下对齐");
	gtk_widget_show(label3);
	gtk_container_add(GTK_CONTAINER(alig3), label3);

	GtkWidget * alig4;
	alig4 = gtk_alignment_new(1, 1, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), alig4, FALSE, FALSE, 0);
	gtk_widget_show(alig4);

	GtkWidget * label4;
	label4 = gtk_label_new("右下对齐");
	gtk_widget_show(label4);
	gtk_container_add(GTK_CONTAINER(alig4), label4);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
