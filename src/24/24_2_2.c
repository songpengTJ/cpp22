#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "组装盒演示");
	gtk_widget_show(window);

	GtkWidget *topvbox;
	topvbox = gtk_vbox_new(FALSE, 0);
	gtk_widget_show(topvbox);
	gtk_container_add(GTK_CONTAINER(window), topvbox);

	GtkWidget *hbox1;
	hbox1 = gtk_hbox_new(FALSE, 15);
	gtk_widget_show(hbox1);
	gtk_box_pack_start(GTK_BOX(topvbox), hbox1, TRUE, TRUE, 0);

	GtkWidget *lbName;
	lbName = gtk_label_new("姓名");
	gtk_widget_show(lbName);
	gtk_box_pack_start(GTK_BOX(hbox1), lbName, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbName, 60, -1);

	GtkWidget *entry1;
	entry1 = gtk_entry_new();
	gtk_widget_show(entry1);
	gtk_box_pack_start(GTK_BOX(hbox1), entry1, TRUE, TRUE, 0);
	gtk_entry_set_invisible_char(GTK_ENTRY(entry1), 8226);

	GtkWidget *hbox2;
	hbox2 = gtk_hbox_new(FALSE, 15);
	gtk_widget_show(hbox2);
	gtk_box_pack_start(GTK_BOX(topvbox), hbox2, TRUE, TRUE, 0);

	GtkWidget *lbGender;
	lbGender = gtk_label_new("性别");
	gtk_widget_show(lbGender);
	gtk_box_pack_start(GTK_BOX(hbox2), lbGender, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbGender, 60, -1);

	GSList *radiobutton1_group = NULL;
	GtkWidget *radiobutton1;
	radiobutton1 = gtk_radio_button_new_with_mnemonic(NULL, "男(_M)");
	gtk_widget_show(radiobutton1);
	gtk_box_pack_start(GTK_BOX(hbox2), radiobutton1, FALSE, FALSE, 15);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(radiobutton1),
			radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(
			radiobutton1));

	GtkWidget *radiobutton2;
	radiobutton2 = gtk_radio_button_new_with_mnemonic(NULL, "女(_F)");
	gtk_widget_show(radiobutton2);
	gtk_box_pack_start(GTK_BOX(hbox2), radiobutton2, FALSE, FALSE, 15);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(radiobutton2),
			radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(
			radiobutton2));

	GtkWidget *button;
	button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
	gtk_widget_show(button);
	gtk_box_pack_start(GTK_BOX(topvbox), button, FALSE, FALSE, 0);
	gtk_widget_set_size_request(button, 60, -1);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
