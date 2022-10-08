#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "按钮盒构件演示");
	gtk_widget_show(window);

	GtkWidget *vbox1;
	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_container_add (GTK_CONTAINER (window), vbox1);

	GtkWidget *hbuttonbox1;
	hbuttonbox1 = gtk_hbutton_box_new ();
	gtk_widget_show (hbuttonbox1);
	gtk_box_pack_start (GTK_BOX (vbox1), hbuttonbox1, FALSE, TRUE, 0);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox1), GTK_BUTTONBOX_START);

	GtkWidget *button1;
	button1 = gtk_button_new ();
	gtk_widget_show (button1);
	gtk_container_add (GTK_CONTAINER (hbuttonbox1), button1);
	GTK_WIDGET_SET_FLAGS (button1, GTK_CAN_DEFAULT);

	GtkWidget *image1;
	image1 = gtk_image_new_from_stock ("gtk-new", GTK_ICON_SIZE_BUTTON);
	gtk_widget_show (image1);
	gtk_container_add (GTK_CONTAINER (button1), image1);

	GtkWidget *button2;
	button2 = gtk_button_new ();
	gtk_widget_show (button2);
	gtk_container_add (GTK_CONTAINER (hbuttonbox1), button2);
	GTK_WIDGET_SET_FLAGS (button2, GTK_CAN_DEFAULT);

	GtkWidget *image2;
	image2 = gtk_image_new_from_stock ("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_widget_show (image2);
	gtk_container_add (GTK_CONTAINER (button2), image2);

	GtkWidget *button3;
	button3 = gtk_button_new ();
	gtk_widget_show (button3);
	gtk_container_add (GTK_CONTAINER (hbuttonbox1), button3);
	GTK_WIDGET_SET_FLAGS (button3, GTK_CAN_DEFAULT);

	GtkWidget *image3;
	image3 = gtk_image_new_from_stock ("gtk-save", GTK_ICON_SIZE_BUTTON);
	gtk_widget_show (image3);
	gtk_container_add (GTK_CONTAINER (button3), image3);

	GtkWidget *hbox1;
	hbox1 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox1);
	gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

	GtkWidget *vbuttonbox1;
	vbuttonbox1 = gtk_vbutton_box_new ();
	gtk_widget_show (vbuttonbox1);
	gtk_box_pack_start (GTK_BOX (hbox1), vbuttonbox1, FALSE, TRUE, 0);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (vbuttonbox1), GTK_BUTTONBOX_SPREAD);

	GtkWidget *button4;
	button4 = gtk_button_new_from_stock ("gtk-cdrom");
	gtk_widget_show (button4);
	gtk_container_add (GTK_CONTAINER (vbuttonbox1), button4);
	gtk_widget_set_size_request (button4, 116, 88);
	GTK_WIDGET_SET_FLAGS (button4, GTK_CAN_DEFAULT);

	GtkWidget *button5;
	button5 = gtk_button_new_from_stock ("gtk-harddisk");
	gtk_widget_show (button5);
	gtk_container_add (GTK_CONTAINER (vbuttonbox1), button5);
	GTK_WIDGET_SET_FLAGS (button5, GTK_CAN_DEFAULT);

	GtkWidget *button6;
	button6 = gtk_button_new_from_stock ("gtk-floppy");
	gtk_widget_show (button6);
	gtk_container_add (GTK_CONTAINER (vbuttonbox1), button6);
	GTK_WIDGET_SET_FLAGS (button6, GTK_CAN_DEFAULT);

	GtkWidget *hbuttonbox2;
	hbuttonbox2 = gtk_hbutton_box_new ();
	gtk_widget_show (hbuttonbox2);
	gtk_box_pack_end (GTK_BOX (hbox1), hbuttonbox2, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox2), 10);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox2), GTK_BUTTONBOX_END);
	gtk_box_set_spacing (GTK_BOX (hbuttonbox2), 10);

	GtkWidget *button7;
	button7 = gtk_button_new_from_stock ("gtk-apply");
	gtk_widget_show (button7);
	gtk_container_add (GTK_CONTAINER (hbuttonbox2), button7);
	GTK_WIDGET_SET_FLAGS (button7, GTK_CAN_DEFAULT);

	GtkWidget *button8;
	button8 = gtk_button_new_from_stock ("gtk-cancel");
	gtk_widget_show (button8);
	gtk_container_add (GTK_CONTAINER (hbuttonbox2), button8);
	GTK_WIDGET_SET_FLAGS (button8, GTK_CAN_DEFAULT);

	GtkWidget *button9;
	button9 = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (button9);
	gtk_container_add (GTK_CONTAINER (hbuttonbox2), button9);
	GTK_WIDGET_SET_FLAGS (button9, GTK_CAN_DEFAULT);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
