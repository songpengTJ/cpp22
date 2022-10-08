GtkWidget *dialog;									// 声明对话框
GtkWidget *label; 									// 声明标签
// 创建一个带有“取消”和“确定”按钮的对话框
dialog = gtk_dialog_new_with_buttons ("关闭窗体", 	// 对话框标题
                                    GTK_WINDOW(window),	// 父窗体
                                    GTK_DIALOG_MODAL,	// 设定对话框为模式窗体
                                    GTK_STOCK_CANCEL, 	// 创建取消按钮
                                    GTK_RESPONSE_REJECT,	// 指定取消按钮信号
                                    GTK_STOCK_OK, 	// 创建确定按钮
                                    GTK_RESPONSE_OK,	// 指定确定按钮信号
                                    NULL);			// 其它参数为空
label = gtk_label_new ("确认要关闭窗体吗?");		// 创建标签构件
gtk_box_pack_start_defaults (GTK_BOX (GTK_DIALOG (dialog)->vbox), 
                           label);					// 将标签构件放置到对话框内
gtk_widget_show_all (dialog);					// 显示对话框及其上所有界面构件
gint diologChoose;								// 创建一个变量
diologChoose = gtk_dialog_run (GTK_DIALOG (dialog));
												// 启动对话框并获取回值
if (diologChoose == GTK_RESPONSE_OK) {
   // 如果是“GTK_STOCK_OK”按钮被单击，关闭自身及父窗体
   gtk_widget_destroy(dialogCloseWindow);
   return FALSE;
}
else if (diologChoose == GTK_RESPONSE_ REJECT) {
   // 如果是“GTK_STOCK_CANCEL”被单击，仅关闭自身
   gtk_widget_destroy(dialogCloseWindow);
   return TRUE;
}
