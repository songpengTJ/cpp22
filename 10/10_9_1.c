
   unsigned int j;					// 用于排序的循环控制变量
   char *p_temp;						// 用于排序时交换指针列表中的数据

      puts("(5)按文件名排序");

         case 5: {					// 按文件名排序
            if (l > 1) {				// 在文件列表长度大于1时，才有排序的意义
               for(i = 0; i < l - 1; i++) {	// 从列表首单元到列表长减1单元循环
                  for(j = i + 1; j < l; j++) {// 从列表首单元加1到列表总长度循环
                     if (strcmp(p_list[i], p_list[j]) > 0) {
                     // 比较两个文件名字符串大小
                        p_temp = p_list[i];
                        // 如果前一个大于后一个，交换指向两个字符串的指针
                        p_list[i] = p_list[j];
                        p_list[j] = p_temp;
                     }
                  }
               }
            }
            break;
         }
