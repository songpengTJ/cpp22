#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	gtk_rc_parse("./mainrc");
	GtkWidget *winNewplan;
	winNewplan = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(winNewplan), "RC文件演示");
	gtk_widget_set_name(GTK_WIDGET(winNewplan),"modelwindow");
	gtk_widget_show(winNewplan);
	g_signal_connect(G_OBJECT(winNewplan), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbMain;
	GtkWidget *hbTitle;
	GtkWidget *lbTitle;
	GtkWidget *enTitle;
	GtkWidget *btTitlemodel;
	GtkWidget *hbInure;
	GtkWidget *lbInure;
	GtkWidget *enInure;
	GtkWidget *btInure;
	GtkWidget *hbOutof;
	GtkWidget *lbOutof;
	GtkWidget *enOutof;
	GtkWidget *btOutof;
	GtkWidget *hbPriority;
	GtkWidget *lbPri;
	GtkWidget *rdExigence;
	GSList *rdExigence_group = NULL;
	GtkWidget *rdNormal;
	GtkWidget *rdRandom;
	GtkWidget *hbbPlan;
	GtkWidget *btCancel;
	GtkWidget *btOK;

	vbMain = gtk_vbox_new(FALSE, 0);
	gtk_widget_show(vbMain);
	gtk_container_add(GTK_CONTAINER(winNewplan), vbMain);

	hbTitle = gtk_hbox_new(FALSE, 0);
	gtk_widget_show(hbTitle);
	gtk_box_pack_start(GTK_BOX(vbMain), hbTitle, TRUE, TRUE, 0);

	lbTitle = gtk_label_new("Title");
	gtk_widget_show(lbTitle);
	gtk_box_pack_start(GTK_BOX(hbTitle), lbTitle, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbTitle, 200, 80);
	gtk_widget_set_name(GTK_WIDGET(lbTitle), "first");

	enTitle = gtk_entry_new();
	gtk_widget_show(enTitle);
	gtk_box_pack_start(GTK_BOX(hbTitle), enTitle, TRUE, TRUE, 0);
	gtk_entry_set_max_length(GTK_ENTRY(enTitle), 50);

	btTitlemodel = gtk_button_new_with_mnemonic("Create Plan by Model");
	gtk_widget_show(btTitlemodel);
	gtk_box_pack_start(GTK_BOX(hbTitle), btTitlemodel, FALSE, FALSE, 0);

	hbInure = gtk_hbox_new(FALSE, 0);
	gtk_widget_show(hbInure);
	gtk_box_pack_start(GTK_BOX(vbMain), hbInure, TRUE, TRUE, 0);

	lbInure = gtk_label_new("Inure Time");
	gtk_widget_show(lbInure);
	gtk_box_pack_start(GTK_BOX(hbInure), lbInure, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbInure, 200, 80);

	enInure = gtk_entry_new();
	gtk_widget_show(enInure);
	gtk_box_pack_start(GTK_BOX(hbInure), enInure, TRUE, TRUE, 0);
	gtk_editable_set_editable(GTK_EDITABLE(enInure), FALSE);

	btInure = gtk_button_new_from_stock("gtk-edit");
	gtk_widget_show(btInure);
	gtk_box_pack_start(GTK_BOX(hbInure), btInure, FALSE, FALSE, 0);
	GTK_WIDGET_SET_FLAGS(btInure, GTK_CAN_DEFAULT);

	hbOutof = gtk_hbox_new(FALSE, 0);
	gtk_widget_show(hbOutof);
	gtk_box_pack_start(GTK_BOX(vbMain), hbOutof, TRUE, TRUE, 0);

	lbOutof = gtk_label_new("Out Of Time");
	gtk_widget_show(lbOutof);
	gtk_box_pack_start(GTK_BOX(hbOutof), lbOutof, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbOutof, 200, 80);

	enOutof = gtk_entry_new();
	gtk_widget_show(enOutof);
	gtk_box_pack_start(GTK_BOX(hbOutof), enOutof, TRUE, TRUE, 0);
	gtk_editable_set_editable(GTK_EDITABLE(enOutof), FALSE);

	btOutof = gtk_button_new_from_stock("gtk-edit");
	gtk_widget_show(btOutof);
	gtk_box_pack_start(GTK_BOX(hbOutof), btOutof, FALSE, FALSE, 0);
	GTK_WIDGET_SET_FLAGS(btOutof, GTK_CAN_DEFAULT);

	hbPriority = gtk_hbox_new(FALSE, 0);
	gtk_widget_show(hbPriority);
	gtk_box_pack_start(GTK_BOX(vbMain), hbPriority, TRUE, TRUE, 0);

	lbPri = gtk_label_new("Priority");
	gtk_widget_show(lbPri);
	gtk_box_pack_start(GTK_BOX(hbPriority), lbPri, FALSE, FALSE, 0);
	gtk_widget_set_size_request(lbPri, 200, 80);

	rdExigence = gtk_radio_button_new_with_mnemonic(NULL, "Exigence");
	gtk_widget_show(rdExigence);
	gtk_box_pack_start(GTK_BOX(hbPriority), rdExigence, FALSE, FALSE, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(rdExigence), rdExigence_group);
	rdExigence_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rdExigence));

	rdNormal = gtk_radio_button_new_with_mnemonic(NULL, "Normal");
	gtk_widget_show(rdNormal);
	gtk_box_pack_start(GTK_BOX(hbPriority), rdNormal, FALSE, FALSE, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(rdNormal), rdExigence_group);
	rdExigence_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rdNormal));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rdNormal), TRUE);

	rdRandom = gtk_radio_button_new_with_mnemonic(NULL, "Random");
	gtk_widget_show(rdRandom);
	gtk_box_pack_start(GTK_BOX(hbPriority), rdRandom, FALSE, FALSE, 0);
	gtk_radio_button_set_group(GTK_RADIO_BUTTON(rdRandom), rdExigence_group);
	rdExigence_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rdRandom));

	hbbPlan = gtk_hbutton_box_new();
	gtk_widget_show(hbbPlan);
	gtk_box_pack_start(GTK_BOX(vbMain), hbbPlan, FALSE, FALSE, 0);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(hbbPlan), GTK_BUTTONBOX_END);

	btCancel = gtk_button_new_from_stock("gtk-cancel");
	gtk_widget_show(btCancel);
	gtk_container_add(GTK_CONTAINER(hbbPlan), btCancel);
	GTK_WIDGET_SET_FLAGS(btCancel, GTK_CAN_DEFAULT);

	btOK = gtk_button_new_from_stock("gtk-ok");
	gtk_widget_show(btOK);
	gtk_container_add(GTK_CONTAINER(hbbPlan), btOK);
	GTK_WIDGET_SET_FLAGS(btOK, GTK_CAN_DEFAULT);

	gtk_widget_show_all(GTK_WIDGET(winNewplan));
	gtk_main();
	return 0;
}
