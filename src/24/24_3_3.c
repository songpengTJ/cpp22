#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

void change_image(GtkFileChooserButton *filebutton,
//	GdkEvent *event,
		GtkImage *image) {
	gtk_image_set_from_file(image, gtk_file_chooser_get_filename(
			GTK_FILE_CHOOSER(filebutton)));
}

int  main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "布局容器构件演示");
	gtk_widget_show(window);

	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_widget_show(vbox);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	GtkWidget *scrolledwindow;
	scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_show (scrolledwindow);
	gtk_box_pack_start (GTK_BOX (vbox), scrolledwindow, TRUE, TRUE, 0);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow), GTK_SHADOW_IN);

	GtkWidget *layout;
	layout = gtk_layout_new (NULL, NULL);
	gtk_widget_show (layout);
	gtk_container_add (GTK_CONTAINER (scrolledwindow), layout);
	gtk_layout_set_size (GTK_LAYOUT (layout), 600, 600);
	GTK_ADJUSTMENT (GTK_LAYOUT (layout)->hadjustment)->step_increment = 10;
	GTK_ADJUSTMENT (GTK_LAYOUT (layout)->vadjustment)->step_increment = 10;

	GtkWidget *image;
	image = gtk_image_new();
	gtk_widget_show (image);
	gtk_layout_put (GTK_LAYOUT (layout), image, 0, 0);

	GtkWidget *filebutton;
		filebutton = gtk_file_chooser_button_new("打开图片文件", GTK_FILE_CHOOSER_ACTION_OPEN);
			gtk_widget_show (filebutton);
			gtk_box_pack_start (GTK_BOX (vbox), filebutton, FALSE, FALSE, 0);

			g_signal_connect(G_OBJECT(window), "delete_event",
					G_CALLBACK(gtk_main_quit), NULL);
			g_signal_connect(G_OBJECT(filebutton), "file-set",
					G_CALLBACK(change_image), (gpointer) image);
			gtk_main();
			return 0;
		}
