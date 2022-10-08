#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "滚动条窗体构件演示");
	gtk_widget_show(window);

	GtkWidget *scrolled_window;

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);


	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_container_add (GTK_CONTAINER (window), scrolled_window);
	gtk_widget_show (scrolled_window);

	GtkWidget *table;

	table = gtk_table_new (10, 10, FALSE);

	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
	gtk_table_set_col_spacings (GTK_TABLE (table), 10);

	gtk_scrolled_window_add_with_viewport (
			GTK_SCROLLED_WINDOW (scrolled_window), table);
	gtk_widget_show (table);

	GtkWidget *button;
	int i, j;
	char buffer[32];

	for (i = 0; i < 10; i++)
	for (j = 0; j < 10; j++) {
		sprintf (buffer, "button (%d,%d)\n", i, j);
		button = gtk_toggle_button_new_with_label (buffer);
		gtk_table_attach_defaults (GTK_TABLE (table), button,
				i, i+1, j, j+1);
		gtk_widget_show (button);
	}

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
