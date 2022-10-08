#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
 
gint delete_event( GtkWidget *window,
                   GdkEvent  *event,
		             gpointer   data ){


   GtkWidget *dialogCloseWindow;
   GtkWidget *lbClose;
   GtkWidget *imgClose;
   GtkWidget *hbClose;

   gint diologChoose;

   dialogCloseWindow = gtk_dialog_new_with_buttons ("退出程序对话框",
                                                    GTK_WINDOW(window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_REJECT,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK,
                                                    NULL);
   gtk_widget_set_name(GTK_WIDGET(dialogCloseWindow),"modelwindow");
   lbClose = gtk_label_new ("是否要退出程序？");

   imgClose = gtk_image_new_from_stock (GTK_STOCK_DIALOG_INFO,
                                        GTK_ICON_SIZE_DIALOG);

   hbClose = gtk_hbox_new (FALSE, 5);
   gtk_container_set_border_width (GTK_CONTAINER (hbClose), 10);
   gtk_box_pack_start_defaults (GTK_BOX (hbClose), imgClose);
   gtk_box_pack_start_defaults (GTK_BOX (hbClose), lbClose);

   gtk_box_pack_start_defaults (GTK_BOX (GTK_DIALOG (dialogCloseWindow)->vbox),
                                hbClose);
   gtk_widget_show_all (dialogCloseWindow);

   diologChoose = gtk_dialog_run (GTK_DIALOG (dialogCloseWindow));

   if (diologChoose == GTK_RESPONSE_OK) {
   	gtk_widget_destroy(dialogCloseWindow);
   	return FALSE;
   }
   else{
   	gtk_widget_destroy(dialogCloseWindow);
   	return TRUE;
   }

}

void destroy(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "回调函数演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);

	g_signal_connect(G_OBJECT(window), "destroy",
				G_CALLBACK(destroy), NULL);
	gtk_main();
	return 0;
}
