int save_m3u(link_t *mlink, const char *file)
{
   FILE *fp;								// 创建文件流指针
   node_t *tmp;							// 用于遍历链表的指针
   if (!file) {							// 判断文件路径指针是否为NULL
      printf("文件链接错误\n");
      return 0;
   }
   if(creat(file, 0664) == -1) {		// 创建文件，无论该文件是否存在
      perror("创建文件失败");
      return 0;
   }
   fp = fopen(file,"rw+");				// 打开创建的文件
   tmp = mlink->np;
   if (fp != NULL) {
      fprintf(fp, "#EXTM3U\n");			// 输出M3U标识符到文件
      while(tmp) {						// 遍历链表
         fprintf(fp, "#EXTINF:%d,%s\n%s\n\n",
                     (int) tmp->item.record_time,
                     tmp->item.title,
                     tmp->item.filepath);	// 格式化输出列表中文件信息
         tmp = tmp->p;
      }
      fflush(fp);						// 立即将缓冲区待写入的数据写入文件
   }
   else {
      perror("打开文件失败");
      return 0;
   }
   if (fclose(fp) != -1)				// 关闭文件流指针
      printf("保存文件成功\n");
   else {
      perror("关闭文件");
      return 0;
   }
   return 1;
}
