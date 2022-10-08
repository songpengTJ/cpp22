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
	vpaned1 = gtk_vpaned_new ();
	gtk_widget_show (vpaned1);
	gtk_container_add (GTK_CONTAINER (window), vpaned1);
	gtk_paned_set_position (GTK_PANED (vpaned1), 0);

	GtkWidget *scrolledwindow1;
	scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow1);
	gtk_paned_pack1 (GTK_PANED (vpaned1), scrolledwindow1, FALSE, TRUE);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

	GtkWidget *textview1;
	textview1 = gtk_text_view_new ();
	gtk_widget_show (textview1);
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), textview1);

	GtkWidget *scrolledwindow2;
	scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow2);
	gtk_paned_pack2 (GTK_PANED (vpaned1), scrolledwindow2, TRUE, TRUE);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_SHADOW_IN);

	GtkWidget *textview2;
	textview2 = gtk_text_view_new ();
	gtk_widget_show (textview2);
	gtk_container_add (GTK_CONTAINER (scrolledwindow2), textview2);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
