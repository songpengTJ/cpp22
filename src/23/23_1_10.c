GtkWidget *status_bar;						// 声明状态栏
// 压入堆栈按钮的回调函数
void push_item( GtkWidget *widget,gpointer data )
{
   static int count = 1;					// 定义static变量保存消息标识符
   char buff[20];							// 定义状态栏消息字符串
   g_snprintf (buff, 20, "字符串 %d", count++);		// 为字符串赋值
   gtk_statusbar_push (GTK_STATUSBAR (status_bar), GPOINTER_TO_INT (data), 
   buff);											// 压入堆栈
   return;
}

// 弹出堆栈按钮的回调函数
void pop_item( GtkWidget *widget,
               gpointer data )
{
   gtk_statusbar_pop (GTK_STATUSBAR (status_bar), GPOINTER_TO_INT (data));
   													// 弹出堆栈
   return;
}
// 程序主函数
int main( int argc,
        char *argv[] )
{
   GtkWidget *window;							// 声明窗体
   GtkWidget *button1, *button2;				// 声明2个按钮
   gint context_id;								// 声明变量，用以保存消息标识符
   …
   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);	// 创建位于顶层的新窗口
   vbox = gtk_vbox_new (FALSE, 1);					// 创建vbox容器
   status_bar = gtk_statusbar_new ();				// 创建状态栏
   …
   context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR (status_bar), 
                                          "状态栏示例");	// 获得上下文标识符
   button1 = gtk_button_new_with_label ("压入堆栈");	// 创建压入堆栈按钮
   g_signal_connect (G_OBJECT (button1), "clicked",
                     G_CALLBACK (push_item), GINT_TO_POINTER (context_id));
												// 捕获按钮信号，连接回调函数
   button2 = gtk_button_new_with_label ("弹出堆栈");	// 创建弹出堆栈按钮
   g_signal_connect (G_OBJECT (button2), "clicked",
                     G_CALLBACK (pop_item), GINT_TO_POINTER (context_id));
   …											//捕获按钮信号，连接回调函数
}
