int main(int argc, char *argv[])
{
   GtkWidget *dialog;
   gchar *filename;
   gint result;
   gtk_init(&argc, &argv);
   dialog = gtk_file_chooser_dialog_new("创建新目录",// 对话框标题
              NULL,									 // 未指定父窗口
              GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,	 // 类型为创建目录对话框
              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,	 // 加入一个CANCEL按钮
              GTK_STOCK_OK, GTK_RESPONSE_OK,			 // 加入一个OK按钮
              NULL);									 // 加入按钮结束
   result = gtk_dialog_run(GTK_DIALOG (dialog));	 // 运行对话框
   if (result == GTK_RESPONSE_OK)			// 判断按下的按钮是否是OK
   {
                                                 // 获得对话框中选择的文件名
      filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
      g_print ("已创建一个新目录： %s\n", filename);
   }
   gtk_widget_destroy (dialog);					// 结束对话框
   return 0;
}
