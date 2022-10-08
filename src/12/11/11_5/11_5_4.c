typedef enum _find_cond find_cond;
enum _find_cond {
   BY_TITLE,							// 按标题查找
   BY_ARTIST, 						// 按艺术家查找
   BY_ABLUM, 						// 按专辑查找
   BY_GENRE, 						// 按流派查找
   BY_FILEPATH						// 按文件名查找
};
int link_find(link_t *mlink,		// 链表指针
           find_cond t,				// 查找条件
           const char *str2,			// 查找字符串
           node_t **res)				// 保存查找结果的动态数组指针
{
   if (*res) {						// 判断结果动态数组的指针是否指向NULL
      free(*res);					// 释放该数组的内存空间
      *res = NULL;					// 将指针指向NULL
   }
   int i, l;
   int count = 0;					// 用于保存找到匹配项目的数量
   const char *str1;					// 指向链表节点数据结构中的字符串
   node_t *tmp, **jump, **jump2;		// 遍历时所使用的指针和访问动态数组的指针
   if (!mlink->length) {			// 判断链表是否为空
      printf("媒体库为空，无法查找\n");
      return 0;
   }
   if (str2)							// 判断查找字符串指针是否为NULL
      l = strlen(str2);
   else {
      printf("查找字符串地址有误\n");
      return 0;
   }
   if (!l) {							// 判断查找字符串长度是否为0
      printf("查找字符串长度为0\n");
      return 0;
   }
   tmp = mlink->np;					// 指向链表首端节点
   node_t *tmp_link = (node_t *)malloc(sizeof(node_t *) * mlink->length);
   // 创建临时用于保存查找结果的动态数组，数组长度与链表长度相同
   jump = &tmp_link;				// 用指针指向动态数组首地址
   while(tmp) {						// 遍历链表
      switch(t) {					// 选择查询条件
         case BY_TITLE:
            str1 = tmp->item.title;	// 读取标题信息
            break;
         case BY_ARTIST:
            str1 = tmp->item.atrist;	// 读取艺术家信息
            break;
         case BY_ABLUM:
            str1 = tmp->item.album;	// 读取专辑信息
            break;
         case BY_GENRE:
            str1 = tmp->item.genre;	// 读取流派信息
            break;
         case BY_FILEPATH:
            str1 = tmp->item.filepath;	// 读取文件名信息
            break;
         default:
            printf("查找条件出错");
            free(tmp_link);
            return 0;
      }
      if (str1 && strlen(str1)) {
         if (hazy_find(str1, str2)) {// 匹配字符串，如果成功则指向判断体内的代码
	            *(jump + count) = tmp;	// 将匹配的链表节点地址保存在临时数组中
            count++;					// 查找结果自增1
         }
      }
      tmp = tmp->p;					// 指向下一个节点
   }
   *res = (node_t *)malloc(sizeof(node_t *) * count);
									// 依据匹配的数量为查询结果动态数组分配内存
   jump2 = res;						// 用指针指向动态数组首地址
   for(i = 0; i < count; i++)
      *(jump2 + 0) = *(jump + 0);	// 将临时数组内的数据复制到结果数组
   free(tmp_link);					// 释放临时数组的内存空间
   return count;					// 返回结果数
}
