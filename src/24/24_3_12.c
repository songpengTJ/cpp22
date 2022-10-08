#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdio.h>

void rotate_book(GtkButton *button, GtkNotebook *notebook) {
	gtk_notebook_set_tab_pos(notebook, (notebook->tab_pos + 1) % 4);
}

void tabsborder_book(GtkButton *button, GtkNotebook *notebook) {
	gint tval = FALSE;
	gint bval = FALSE;
	if (notebook->show_tabs == 0)
		tval = TRUE;
	if (notebook->show_border == 0)
		bval = TRUE;

	gtk_notebook_set_show_tabs(notebook, tval);
	gtk_notebook_set_show_border(notebook, bval);
}

void remove_book(GtkButton *button, GtkNotebook *notebook) {
	gint page;

	page = gtk_notebook_get_current_page(notebook);
	gtk_notebook_remove_page(notebook, page);
	gtk_widget_queue_draw(GTK_WIDGET(notebook));
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "笔记本构件演示");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	gtk_widget_show(window);

	int i;
	char bufferf[32];
	char bufferl[32];

	GtkWidget *button;
	GtkWidget *table;
	GtkWidget *notebook;
	GtkWidget *frame;
	GtkWidget *label;
	GtkWidget *checkbutton;
	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 15);
	gtk_widget_show(vbox);

	table = gtk_table_new(3, 6, FALSE);
	gtk_container_add(GTK_CONTAINER(window), table);

	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);
	gtk_table_attach_defaults(GTK_TABLE(table), notebook, 0, 6, 0, 1);
	gtk_widget_show(notebook);

	for (i = 0; i < 5; i++) {
		sprintf(bufferf, "选项卡 %d", i + 1);
		sprintf(bufferl, "选项卡 %d", i + 1);

		frame = gtk_frame_new(bufferf);
		gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
		gtk_widget_set_size_request(frame, 100, 75);
		gtk_widget_show(frame);

		label = gtk_label_new(bufferf);
		gtk_container_add(GTK_CONTAINER(frame), label);
		gtk_widget_show(label);

		label = gtk_label_new(bufferl);
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
	}

	checkbutton = gtk_check_button_new_with_label("Check me please!");
	gtk_widget_set_size_request(checkbutton, 100, 75);
	gtk_widget_show(checkbutton);

	label = gtk_label_new("插入页");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), checkbutton, label, 2);

	for (i = 0; i < 5; i++) {
		sprintf(bufferf, "反向添加的选项卡 %d", i + 1);
		sprintf(bufferl, "反向添加的选项卡 %d", i + 1);

		frame = gtk_frame_new(bufferf);
		gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
		gtk_widget_set_size_request(frame, 100, 75);
		gtk_widget_show(frame);

		label = gtk_label_new(bufferf);
		gtk_container_add(GTK_CONTAINER(frame), label);
		gtk_widget_show(label);

		label = gtk_label_new(bufferl);
		gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook), frame, label);
	}

	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 3);

	button = gtk_button_new_with_label("关闭");
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit),
			NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("下翻页");
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(
			gtk_notebook_next_page), notebook);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("上翻页");
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(
			gtk_notebook_prev_page), notebook);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("改变标签位置");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(rotate_book),
			notebook);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("显示/隐藏边框");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(tabsborder_book),
			notebook);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("删除选项卡");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(remove_book),
			notebook);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 6, 1, 2);
	gtk_widget_show(button);

	gtk_widget_show(table);


	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
