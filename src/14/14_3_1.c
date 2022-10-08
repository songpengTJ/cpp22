int load_m3u(link_t *mlink, const char *file)
{
   char str[MAX_PATH_LENGTH];			// 用于保存读取的字符串
   link_del_all(mlink);					// 清空链表
   if (!file) {							// 判断文件指针是否为NULL
      printf("文件链接错误\n");
      return 0;
   }
   FILE *fp = fopen(file, "r");			// 以只读方式打开文件
   if(fp != NULL) {
      fgets(str, MAX_PATH_LENGTH, fp);	// 读取文件的第1行
if(strncmp(str, "#EXTM3U", 7)) {	// 判断文件的第1行是否包含M3U标识符
         printf("该文件不是播放列表文件\n");
         return 0;
      }
   }
   else {
      printf("错误代码：%d", ferror(fp));
      perror("打开文件错误\n");
   }
   while(!feof(fp)) {				// 在没有遇到文件终结符时执行循环体
      fgets(str, MAX_PATH_LENGTH, fp);	// 读取一行字符串
      str[strlen(str) - 1] = '\0';	// 将读入的换行符替换为字符串结束符
      if (is_mp3(str))					// 判断读入的字符串是否为MP3文件
         link_add(mlink, str);			// 加入到播放列表
   }
   fclose(fp);							// 关闭文件流
   return 1;
}
