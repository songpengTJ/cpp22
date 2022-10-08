#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
 
struct WIDGET_SET {
	GtkWidget *button;
	GtkWidget *label;
	gulong *signal_id;
};

void label_const(GtkButton *button, GtkLabel *label) {
	char citem[100];
	static int i = 0;
	sprintf(citem, "计数按钮按下次数为：%d", ++i);
	gtk_label_set_label(label, citem);
}

void close_const(GtkWidget *togglebutton,
	              struct WIDGET_SET *widget_set)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   	gtk_button_set_label(GTK_BUTTON(togglebutton),
   			                        "信号断开");
   	g_signal_handler_disconnect((gpointer) widget_set->button,
   		                          *widget_set->signal_id);
	}
	else {
		gtk_button_set_label(GTK_BUTTON(togglebutton),
		   			                        "信号连接");
		*widget_set->signal_id = g_signal_connect((gpointer) widget_set->button, "clicked", G_CALLBACK(label_const),
							(gpointer) widget_set->label);
	}
}

gboolean activate_accel(GtkWidget *button, gint signal_id)
{
	return TRUE;
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "连接和断开信号演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkAccelGroup *accel_group;
	accel_group = gtk_accel_group_new ();
	GtkWidget *button;
	gulong signal_id;
	button = gtk_button_new_with_label("计数  CTRL + A");
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
	gtk_widget_add_accelerator (button, "clicked", accel_group,
	                              GDK_A, (GdkModifierType) GDK_CONTROL_MASK,
	                              GTK_ACCEL_VISIBLE);

	GtkWidget *togglebutton;
	togglebutton = gtk_toggle_button_new_with_label ("信号连接");
	gtk_widget_show (togglebutton);
	gtk_box_pack_start (GTK_BOX (vbox), togglebutton, TRUE, TRUE, 0);
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

	GtkWidget *label;
	label = gtk_label_new ("计数按钮按下次数为：0");
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

	signal_id = g_signal_connect((gpointer) button, "clicked", G_CALLBACK(label_const),
					(gpointer) label);

	struct WIDGET_SET widget_set;
	widget_set.button = button;
	widget_set.label = label;
	widget_set.signal_id = &signal_id;

	g_signal_connect((gpointer) togglebutton, "clicked", G_CALLBACK(close_const),
			(gpointer) &widget_set);
	gtk_widget_can_activate_accel(button, signal_id);
	g_signal_connect((gpointer) button, "can-activate-accel",
			G_CALLBACK(activate_accel), NULL);
	gtk_main();
	return 0;
}
