#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
 
void button_press(GtkEventBox *ebox,
		GdkEventButton *event,
		GtkLabel *label) {
	const char *citem;
	switch(event->type) {
	case GDK_BUTTON_PRESS: citem = "单击";
	break;
	case GDK_2BUTTON_PRESS: citem = "双击";
	break;
	case GDK_3BUTTON_PRESS: citem = "三击";
	                          break;
	default: citem = "未知操作";
	}
	gtk_label_set_label(label, citem);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "连接和断开信号演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *ebox;
	ebox = gtk_event_box_new ();
	gtk_widget_show (ebox);
	gtk_container_add (GTK_CONTAINER (window), ebox);

	GtkWidget *label;
	label = gtk_label_new ("请使用鼠标点击窗体");
	gtk_widget_show (label);
	gtk_container_add (GTK_CONTAINER (ebox), label);

	GtkWidget *inputdialog;
	inputdialog = gtk_input_dialog_new();
	gtk_dialog_run(GTK_DIALOG(inputdialog));

	g_signal_connect((gpointer) ebox, "button-press-event",
			G_CALLBACK(button_press), (gpointer) label);
	gtk_main();
	return 0;
}
