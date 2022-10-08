#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

static void label_const(GtkWidget *eventbox) {
	static int i = 0;
	static char citem[100];
	sprintf(citem, "标签单击的次数：%d", ++i);
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK, citem);
	gtk_window_set_title(GTK_WINDOW(dialog), "单击次数");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "事件盒演示");
	gtk_widget_show(window);

	GtkWidget *eventbox;
	eventbox = gtk_event_box_new();
	gtk_widget_show(eventbox);
	gtk_container_add(GTK_CONTAINER(window), eventbox);

	GtkWidget *label;
	label = gtk_label_new("请用鼠标单击标签");
	gtk_widget_show(label);
	gtk_container_add(GTK_CONTAINER(eventbox), label);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect((gpointer) eventbox, "button_press_event", G_CALLBACK(
			label_const), NULL);
	gtk_main();
	return 0;
}
