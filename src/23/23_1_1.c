GtkWidget *vbox;									// 声明vbox容器
GtkWidget *radiobutton1, *radiobutton2, *radiobutton3;	// 声明单选按钮构件
GSList *radiobutton_group = NULL;					// 声明GSList链表
vbox = gtk_vbox_new (FALSE, 0);					// 创建vbox容器
gtk_container_add (GTK_CONTAINER (window), vbox);		// 将vbox装入窗体中
radiobutton1 = gtk_radio_button_new_with_mnemonic (NULL, "选项1");
													// 创建复选按钮
gtk_widget_show (radiobutton1);					// 显示复选按钮
gtk_box_pack_start (GTK_BOX (vbox), radiobutton1, FALSE, FALSE, 0);
													// 将按钮放置在vbox中
gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), 
radiobutton_group);									// 将链表加入按钮
radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON 
(radiobutton1));
													// 将按钮作为成员加入链表
Radiobutton2= gtk_radio_button_new_with_mnemonic (NULL, "选项2");
													// 创建复选按钮
…
