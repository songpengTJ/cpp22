#include <gtk-2.0/gtk/gtk.h>
int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *window1;
	GtkWidget *fixed1;
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show (window1);

	fixed1 = gtk_fixed_new ();
	gtk_widget_show (fixed1);
	gtk_container_add (GTK_CONTAINER (window1), fixed1);

	GtkWidget *combo1;
	GList *combo1_items = NULL;
	GtkWidget *combo_entry1;

	combo1 = gtk_combo_new ();
	g_object_set_data (G_OBJECT (GTK_COMBO (combo1)->popwin),
	                     "GladeParentKey", combo1);
	gtk_widget_show (combo1);
	gtk_fixed_put (GTK_FIXED (fixed1), combo1, 5, 5);
	gtk_widget_set_size_request (combo1, 187, 27);
	gtk_combo_set_use_arrows_always (GTK_COMBO (combo1), TRUE);
	combo1_items = g_list_append (combo1_items, "字符串 1");
	combo1_items = g_list_append (combo1_items, "字符串 2");
	combo1_items = g_list_append (combo1_items, "字符串 3");
	combo1_items = g_list_append (combo1_items, "字符串 4");
	gtk_combo_set_popdown_strings (GTK_COMBO (combo1), combo1_items);
	g_list_free (combo1_items);
	combo_entry1 = GTK_COMBO (combo1)->entry;
	gtk_widget_show (combo_entry1);

	gtk_main ();
	return 0;
}
