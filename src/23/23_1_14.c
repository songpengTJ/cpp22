#include <gtk-2.0/gtk/gtk.h>
int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *window1;
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show (window1);

	GtkWidget *colordio;
	colordio = gtk_file_chooser_dialog_new("文件选择对话框",
			                                 GTK_WINDOW(window1),
			                                  GTK_FILE_CHOOSER_ACTION_OPEN,
			                                  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			                                  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			                                  NULL);
	gtk_widget_show(colordio);
	gtk_main ();
	return 0;
}
