#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "框架构件演示");
	gtk_widget_show(window);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkWidget *frame1;
	frame1 = gtk_frame_new (NULL);
	gtk_widget_show (frame1);
	gtk_box_pack_start (GTK_BOX (vbox), frame1, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (frame1), 5);

	GtkWidget *alignment1;
	alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment1);
	gtk_container_add (GTK_CONTAINER (frame1), alignment1);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment1), 0, 0, 12, 0);

	GtkWidget *hbox1;
	hbox1 = gtk_hbox_new (TRUE, 0);
	gtk_widget_show (hbox1);
	gtk_container_add (GTK_CONTAINER (alignment1), hbox1);

	GtkWidget *checkbutton1;
	checkbutton1 = gtk_check_button_new_with_mnemonic ("复选按钮 1");
	gtk_widget_show (checkbutton1);
	gtk_box_pack_start (GTK_BOX (hbox1), checkbutton1, FALSE, FALSE, 0);

	GtkWidget *checkbutton2;
	checkbutton2 = gtk_check_button_new_with_mnemonic ("复选按钮 2");
	gtk_widget_show (checkbutton2);
	gtk_box_pack_start (GTK_BOX (hbox1), checkbutton2, FALSE, FALSE, 0);

	GtkWidget *label1;
	label1 = gtk_label_new ("3D内阴影边框");
	gtk_widget_show (label1);
	gtk_frame_set_label_widget (GTK_FRAME (frame1), label1);
	gtk_label_set_use_markup (GTK_LABEL (label1), TRUE);

	GtkWidget *frame2;
	frame2 = gtk_frame_new (NULL);
	gtk_widget_show (frame2);
	gtk_box_pack_start (GTK_BOX (vbox), frame2, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (frame2), 3);
	gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_ETCHED_OUT);

	GtkWidget *alignment2;
	alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment2);
	gtk_container_add (GTK_CONTAINER (frame2), alignment2);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment2), 0, 0, 12, 0);

	GtkWidget *hbox2;
	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_container_add (GTK_CONTAINER (alignment2), hbox2);

	GSList *radiobutton1_group = NULL;
	GtkWidget *radiobutton1;
	radiobutton1 = gtk_radio_button_new_with_mnemonic (NULL, "单选按钮 1");
	gtk_widget_show (radiobutton1);
	gtk_box_pack_start (GTK_BOX (hbox2), radiobutton1, FALSE, FALSE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1));

	GtkWidget *radiobutton2;
	radiobutton2 = gtk_radio_button_new_with_mnemonic (NULL, "单选按钮 2");
	gtk_widget_show (radiobutton2);
	gtk_box_pack_start (GTK_BOX (hbox2), radiobutton2, FALSE, FALSE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton2), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton2));

	GtkWidget *radiobutton3;
	radiobutton3 = gtk_radio_button_new_with_mnemonic (NULL, "单选按钮 3");
	gtk_widget_show (radiobutton3);
	gtk_box_pack_start (GTK_BOX (hbox2), radiobutton3, FALSE, FALSE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton3), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton3));


	GtkWidget *label2;
	label2 = gtk_label_new ("3D外阴影边框");
	gtk_widget_show (label2);
	gtk_frame_set_label_widget (GTK_FRAME (frame2), label2);
	gtk_label_set_use_markup (GTK_LABEL (label2), TRUE);

	GtkWidget *hbox3;
	hbox3 = gtk_hbox_new (TRUE, 0);
	gtk_widget_show (hbox3);
	gtk_box_pack_start (GTK_BOX (vbox), hbox3, FALSE, FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (hbox3), 8);

	GtkWidget *button;
	button = gtk_button_new_from_stock ("gtk-quit");
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (hbox3), button, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
