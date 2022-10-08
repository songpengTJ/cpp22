#define GET_NAME "%255s"	// 用于scanf()函数输入文件名，说明输入字符串的长度

   int select_value;		// 用于接收键盘输入的菜单选择
   char exit_switch = 1;	// 用于控制程序主操作循环的退出
   l = 0;					// 初始化列表长度
   do {						// 开始主操作循环
      puts("请选择操作命令：");
      puts("(1)添加新文件");
      puts("(2)删除列表中的文件");
      puts("(3)打印播放列表");
      puts("(4)退出程序");
      scanf("%1d", &select_value);		// 输入的菜单选择
      getchar();							// 吸收多余的输入字符
      switch (select_value) {
         case 1: {						// 添加新文件
            if (l < MAX_LENGTH){			// 判断列表是否已满
               puts("请输入文件名：");
               for(i = 0; i < MAX_LENGTH; i++){
               							// 在列表中循环，查找文件名列表中的空位
                  if(!f_list[i][0]){		// 二维字符数组行首为0则表示是空位
                     while (!scanf(GET_NAME, f_list[i])){
                     						// 输入文件名，并判断文件名是否有效
                        puts("请输入正确的文件名！");
                     }
                     p_list[l++] = f_list[i];
                     // 将指针列表所对应的单元，指向文件名存放的内存地址
                     break;
                  }
               }
            }
            else {
               puts("文件列表已满！");
            }
            break;
         }
         case 2: {					// 删除列表中的文件
            puts("请输入文件编号：");
            scanf("%u", &i);
            if(i > 0 && i <= l) {
            // 判断编号是否有效，有效的编码应在1至总长度之间
               *p_list[--i] = NULL;	// 通过指针间接引用文件列表，将目标文件名删除
               while(i < l - 1); {	// 循环，从列表中删除的位置到列表结束
                  p_list[i] = p_list[i + 1];
                  // 将游标所指向的指针列表后的元素向前挪进1位
                  i++;
               }
               l--;					// 列表长度减1
            }
            else
               puts("您所输入的文件编号不存在！");
            break;
         }
         case 3: {					// 打印播放列表
            for(i = 0; i < l; i++)	// 循环遍历列表
               printf("%d : %s\n", i + 1, p_list[i]);
               // 通过指针列表间接引用文件名列表，输出文件名
            break;
         }
         case 4: {					// 退出程序
            exit_switch = 0;			// 将程序主操作循环退出标记置0
         }
      }
   } while(exit_switch);			// 如果主操作循环退出标记不为0，继续执行循环
   return EXIT_SUCCESS;
}
