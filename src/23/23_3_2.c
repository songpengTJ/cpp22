#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <glib-2.0/glib.h>
GtkWidget *create_menu4(void) {
	GtkWidget *menu4;
	GtkWidget *copy1;
	GtkWidget *cut1;
	GtkWidget *delete1;
	GtkAccelGroup *accel_group;

	accel_group = gtk_accel_group_new();

	menu4 = gtk_menu_new();

	copy1 = gtk_menu_item_new_with_mnemonic("复制");
	gtk_widget_show(copy1);
	gtk_container_add(GTK_CONTAINER(menu4), copy1);
	gtk_widget_add_accelerator(copy1, "activate", accel_group, GDK_c,
			(GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	cut1 = gtk_menu_item_new_with_mnemonic("剪切");
	gtk_widget_show(cut1);
	gtk_container_add(GTK_CONTAINER(menu4), cut1);
	gtk_widget_add_accelerator(cut1, "activate", accel_group, GDK_x,
			(GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	delete1 = gtk_menu_item_new_with_mnemonic("删除");
	gtk_widget_show(delete1);
	gtk_container_add(GTK_CONTAINER(menu4), delete1);
	gtk_widget_add_accelerator(delete1, "activate", accel_group, GDK_F4,
			(GdkModifierType) 0, GTK_ACCEL_VISIBLE);

	gtk_menu_set_accel_group(GTK_MENU(menu4), accel_group);

	return menu4;
}

static gint button_press(GtkWidget *widget, GdkEvent *event) {
	if (event->type == GDK_BUTTON_PRESS) {
		GdkEventButton *bevent = (GdkEventButton *) event;
		gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL,
				bevent->button, bevent->time);
		return TRUE;
	}
	return FALSE;
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *window1;
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "弹出菜单演示");
	gtk_widget_show(window1);
	g_signal_connect(G_OBJECT(window1), "delete_event", G_CALLBACK(
			gtk_main_quit), NULL);

	GtkWidget *menu;
	menu = create_menu4();

	GtkWidget *button;
	button = gtk_button_new_with_label("弹出");
	g_signal_connect_swapped(G_OBJECT(button), "event",
			G_CALLBACK(button_press), menu);
	gtk_container_add(GTK_CONTAINER(window1), button);
	gtk_widget_show(button);
	gtk_main();
	return 0;
}
