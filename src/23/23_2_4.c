#include <gtk/gtk.h>
static void button_clicked(GtkButton *button, GtkWindow *parent)
// 按钮按下的回调函数
{
   GtkWidget *dialog;
   dialog = gtk_message_dialog_new(parent,
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,
                                        "按钮被按下！");		// 创建消息对话框
   gtk_window_set_title(GTK_WINDOW(dialog), "消息对话框");// 设置对话框标题
   gtk_dialog_run(GTK_DIALOG(dialog));					// 显示对话框
   gtk_widget_destroy(dialog);							// 删除对话框
}
int main(int argc, char *argv[])
{
   GtkWidget *window;
   GtkWidget *button;
   gtk_init(&argc, &argv);
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "消息对话框示例");
   gtk_container_set_border_width(GTK_CONTAINER(window), 10);
   g_signal_connect(G_OBJECT(window), "delete_event",
                       G_CALLBACK(gtk_main_quit), NULL);
   button = gtk_button_new_with_label("打开消息对话框");	// 创建按钮
   g_signal_connect(G_OBJECT(button), "clicked",
                       G_CALLBACK(button_clicked),
                      (gpointer) window);
   gtk_container_add(GTK_CONTAINER(window), button);
   gtk_widget_show_all(window);
   gtk_main();
   return 0;
}
