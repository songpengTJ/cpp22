int link_add(link_t *mlink, const char *file)
{
   node_t *endnode;
   node_t *mnode = (node_t *)malloc(sizeof(node_t));	// 为节点分配内存
   if (!mnode) {
      printf("分配内存失败\n");
      return 1;
   }
   if(read_tag_from_file(file, &mnode->item)) {	// 读取媒体文件信息
      printf("读取文件信息失败\n");
      free(mnode);									// 释放节点的内存
      return 1;
   }
   mnode->p = NULL;								// 将节点的指针置为NULL
   if (mlink->np) {								// 判断列表是否不为空
      endnode = link_to_end(mlink->np);			// 遍历到节点末端
      endnode->p = mnode; 						// 将末端节点指向当前节点
   }
   else
      mlink->np = mnode;							// 将链表入口指向当前节点
   mlink->length++;								// 链表个数的计数器自增
   return 0;
}
