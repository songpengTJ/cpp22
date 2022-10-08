…
   spinbutton1_adj = gtk_adjustment_new (2009, 1986, 2086, 1, 10, 10);
   													// 创建调整对象
   spinbutton1 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton1_adj), 1, 
   0);												// 创建微调按钮
   gtk_widget_show (spinbutton1);
   spinbutton2_adj = gtk_adjustment_new (1, 1, 12, 1, 10, 10);
   spinbutton2 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton2_adj), 1, 
   0);
   gtk_widget_show (spinbutton2);
   spinbutton3_adj = gtk_adjustment_new (1, 1, 31, 1, 10, 10);
   spinbutton3 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton3_adj), 1, 
   0);
   label1 = gtk_label_new ("年");
   gtk_widget_show (label1);
   label2 = gtk_label_new ("月");
   gtk_widget_show (label2);
   label3 = gtk_label_new ("日");
   gtk_widget_show (label3);
…
