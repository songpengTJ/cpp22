int is_mp3(const char *name)
{
   int l;
   if (!name) {								// 判断指针是否执行NULL
      printf("文件名指针错误\n");
      return 0;
   }
   l = strlen(name);						// 获得文件名的长度
   if (l < 5) {								// 判断文件名字符串是否有意义
      printf("输入的文件名有误\n ");
      return 0;
   }
   l -= 4;									// 计算距离后缀名的偏移量
   if (strcmp(name + l, ".mp3") && strcmp(name + l, ".MP3")) {		
	// 判断后缀名是否为媒体文件名
      return 0;
   }
   return 1;
}



int link_add_dir(link_t *mlink, const char *dir)
{
   DIR *dp; 								// 定义子目录流指针
   struct dirent *entry; 				// 定义dirent结构指针保存后续目录
   struct stat statbuf; 				// 定义statbuf结构保存文件属性
   if((dp = opendir(dir)) == NULL) { 	// 打开目录，获得子目录流指针，判断
											// 操作是否成功
      printf("无法打开该目录");
      return 0;
   }
   chdir(dir); 								// 切换到当前目录中去
   while((entry = readdir(dp)) != NULL) { 	// 获取下一级目录信息，如果未结
                      							// 束则循环
      lstat(entry->d_name, &statbuf); 		// 获取下一级成员属性
      if(S_IFDIR & statbuf.st_mode) { 		// 判断下一级成员是否是目录
         if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) ==0)
            continue; 						// 如果获得的成员是符号“.”和“..”，跳过本次循环
         link_add_dir(mlink, entry->d_name);// 递归调用自身，扫描下一级目录
                                                   // 的内容
      }
      else {
         if(is_mp3(entry->d_name))			// 判断当前文件是否为媒体文件
            link_add(mlink, entry->d_name);	// 添加该文件到媒体库链表
      }
   }
   chdir("..");								// 回到上一级目录
   closedir(dp); 							// 关闭子目录流
   return 1;
}
