#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
#include <stdio.h>

struct WIDGET_SET {
	GtkWidget *button;
	GtkWidget *label;
	gulong *signal_id;
};

void label_const(GtkWidget *button,
		           GtkLabel *label) {
	char citem[100];
	static int i = 0;
	sprintf(citem, "计数按钮按下次数为：%d", ++i);
	gtk_label_set_label(label, citem);
}

// void disconn_dialog(GtkWidget *togglebutton, GtkWindow *window) {
	// const char *label;
	// if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
		// label = "信号断开";
	// else
		// label = "信号连接";
	// GtkWidget *dialog;
	// dialog = gtk_message_dialog_new(window, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
			// GTK_BUTTONS_OK, label);
	// gtk_window_set_title(GTK_WINDOW(dialog), "消息对话框");
	// gtk_dialog_run(GTK_DIALOG(dialog));
	// gtk_widget_destroy(dialog);
// }

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

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "回调函数执行顺序演示");
	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	GtkWidget *button;
	gulong signal_id;
	button = gtk_button_new_with_label("计数");
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

	GtkWidget *togglebutton;
	togglebutton = gtk_toggle_button_new_with_label ("信号连接");
	gtk_widget_show (togglebutton);
	gtk_box_pack_start (GTK_BOX (vbox), togglebutton, FALSE, FALSE, 0);

	GtkWidget *label;
	label = gtk_label_new ("计数按钮按下次数为：0");
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

	signal_id = g_signal_connect((gpointer) button, "clicked", G_CALLBACK(label_const),
					(gpointer) label);

	struct WIDGET_SET widget_set;
	widget_set.button = button;
	widget_set.label = label;
	widget_set.signal_id = &signal_id;
	g_signal_connect((gpointer) togglebutton, "clicked", G_CALLBACK(disconn_dialog),
				(gpointer) window);
	// g_signal_connect((gpointer) togglebutton, "clicked", G_CALLBACK(close_const),
			// (gpointer) &widget_set);
	gtk_main();
	return 0;
}
