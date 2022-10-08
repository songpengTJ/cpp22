#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "表组装演示");
	gtk_widget_show(window);

	GtkWidget *table;
	table = gtk_table_new(3, 4, FALSE);
	gtk_widget_show(table);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_table_set_row_spacings(GTK_TABLE(table), 10);
	gtk_table_set_col_spacings(GTK_TABLE(table), 10);

	GtkWidget *lbName;
	lbName = gtk_label_new("姓名");
	gtk_widget_show(lbName);
	gtk_table_attach(GTK_TABLE(table), lbName, 0, 1, 0, 1, (GtkAttachOptions)(
			GTK_FILL), (GtkAttachOptions)(0), 0, 0);
	gtk_widget_set_size_request(lbName, 60, 50);
	GtkWidget *entry1;
	entry1 = gtk_entry_new();
	gtk_widget_show(entry1);
	gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 0, 1, (GtkAttachOptions)(
			GTK_EXPAND | GTK_FILL), (GtkAttachOptions)(0), 0, 0);
	gtk_entry_set_invisible_char(GTK_ENTRY(entry1), 8226);

	GtkWidget *lbGender;
	lbGender = gtk_label_new("性别");
	gtk_widget_show(lbGender);
	gtk_table_attach(GTK_TABLE(table), lbGender, 0, 1, 1, 2,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);

	GSList *radiobutton1_group = NULL;
	GtkWidget *radiobutton1;
	radiobutton1 = gtk_radio_button_new_with_mnemonic(NULL, "男(_M)");
	gtk_widget_show(radiobutton1);
	gtk_table_attach(GTK_TABLE(table), radiobutton1, 1, 2, 1, 2,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(radiobutton1),
			radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(
			radiobutton1));
	GtkWidget *radiobutton2;
	radiobutton2 = gtk_radio_button_new_with_mnemonic(NULL, "女(_F)");
	gtk_widget_show(radiobutton2);
	gtk_table_attach(GTK_TABLE(table), radiobutton2, 2, 3, 1, 2,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(radiobutton2),
			radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(
			radiobutton2));

	GtkWidget *radiobutton3;
	radiobutton3 = gtk_radio_button_new_with_mnemonic(NULL, "保密(_S)");
	gtk_widget_show(radiobutton3);
	gtk_table_attach(GTK_TABLE(table), radiobutton3, 3, 4, 1, 2,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(radiobutton3),
			radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(
			radiobutton3));
	GtkWidget *buttonAP;
	buttonAP = gtk_button_new_from_stock("gtk-apply");
	gtk_widget_show(buttonAP);
	gtk_table_attach(GTK_TABLE(table), buttonAP, 1, 2, 2, 3,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);

	GtkWidget *buttonCE;
	buttonCE = gtk_button_new_from_stock("gtk-cancel");
	gtk_widget_show(buttonCE);
	gtk_table_attach(GTK_TABLE(table), buttonCE, 2, 3, 2, 3,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);

	GtkWidget *buttonOK;
	buttonOK = gtk_button_new_from_stock("gtk-ok");
	gtk_widget_show(buttonOK);
	gtk_table_attach(GTK_TABLE(table), buttonOK, 3, 4, 2, 3,
			(GtkAttachOptions)(GTK_FILL), (GtkAttachOptions)(0), 0, 0);

	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
