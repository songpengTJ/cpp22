#include <gtk/gtk.h>
static void font_dialog_response(GtkFontSelectionDialog *dialog,
                                       gint response,
                                       gpointer data)
                                        	// 处理字体选择对话框按钮按下事件
{
   gchar *font;
   GtkWidget *message;
   switch (response) {
   case (GTK_RESPONSE_APPLY):
   case (GTK_RESPONSE_OK):		// 当gtk-apply或gtk-ok按钮按下时处理
      font = gtk_font_selection_dialog_get_font_name(dialog);
       								// 获取字体选择对话框所选择字体名
      message = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              font);	// 创建一个新对话框显示字体名
      gtk_window_set_title(GTK_WINDOW(message),"所选择字体");
      gtk_dialog_run(GTK_DIALOG(message));
      gtk_widget_destroy(message);
      g_free(font);
      break;
   default:
      gtk_widget_destroy(GTK_WIDGET(dialog));	// 删除字体选择对话框
   }
   if (response == GTK_RESPONSE_OK)
      gtk_widget_destroy(GTK_WIDGET(dialog));
   gtk_main_quit();								// 退出GTK+主循环
}
int main(int argc, char *argv[]) {
   gtk_init(&argc, &argv);
   GtkWidget *dialog;
   dialog = gtk_font_selection_dialog_new ("请选择字体");
   												// 创建字体选择对话框
   gtk_font_selection_dialog_set_font_name(GTK_FONT_SELECTION_DIALOG 37	(dialog),
                                         "Sans Bold Italic 12");
                                          	// 设置对话框字体名称
   gtk_font_selection_dialog_set_preview_text 41	(GTK_FONT_SELECTION_DIALOG (dialog),
                                           "感受GTK+开发的乐趣");
                                            	// 设置字体预览文本
   g_signal_connect(G_OBJECT (dialog), "response",
                        G_CALLBACK (font_dialog_response),
	                        NULL);				// 监听对话框中按钮按下事件
   gtk_widget_show_all(dialog);
   gtk_main();
   return 0;
}
