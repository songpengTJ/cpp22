void enter_callback(GtkWidget *widget,
                        GtkWidget *entry)				// 输入完成后的回调函数
{
   const gchar *entry_text;
   entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
                                                        	// 获得文本输入构件的内容
   printf("输入的内容为：%s\n", entry_text);
}
void entry_toggle_editable(GtkWidget *checkbutton,
                                GtkWidget *entry)
                           // 用复选框改变其可输入状态的回调函数
{
   gtk_editable_set_editable(GTK_EDITABLE(entry),
                                  GTK_TOGGLE_BUTTON(checkbutton)->active);
                             // 用复选按钮的值作为文本输入构件可输入状态
}
void entry_toggle_visibility(GtkWidget *checkbutton,
                             // 用复选按钮改变其文本回显状态
                        GtkWidget *entry)
{
   gtk_entry_set_visibility (GTK_ENTRY (entry),
                                        // 用复选按钮的值作为文本输入构件回显状态
                         GTK_TOGGLE_BUTTON (checkbutton)->active);	}
int main()
{
…
   GtkWidget *entry;
   GtkWidget *button;
   GtkWidget *check;
   gint tmp_pos;
…
   entry = gtk_entry_new();						// 创建文本输入构件
   gtk_entry_set_max_length(GTK_ENTRY (entry), 50);
                                             // 设置文本输入构件接纳文本最大长度
   g_signal_connect(G_OBJECT (entry), "activate",
                       G_CALLBACK (enter_callback),
                       entry);						// 失去焦点后调用回调函数
   gtk_entry_set_text(GTK_ENTRY(entry), "hello");
                      								// 修改文本输入构件中的文本
   tmp_pos = GTK_ENTRY (entry)->text_length;	// 获得文本输入构件中文本长度
   gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);
   												// 插入文本
   gtk_editable_select_region (GTK_EDITABLE (entry),
                            0, GTK_ENTRY (entry)->text_length);// 选择文本
   gtk_widget_show (entry);
…
   check = gtk_check_button_new_with_label("可编辑状态");	// 创建复选按钮
   g_signal_connect (G_OBJECT (check), "toggled",
                         G_CALLBACK(entry_toggle_editable), entry);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
   gtk_widget_show (check);
   check = gtk_check_button_new_with_label("回显状态");		// 创建复选按钮
   g_signal_connect(G_OBJECT(check), "toggled",
                       G_CALLBACK(entry_toggle_visibility), entry);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (check), TRUE);
   gtk_widget_show (check);
   button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);	// 创建按钮
   g_signal_connect_swapped (G_OBJECT (button), "clicked",
                                  G_CALLBACK (gtk_widget_destroy),window);
…
}
