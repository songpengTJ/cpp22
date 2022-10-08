int link_del_all(link_t *mlink)
{
   node_t *tmp;						// 临时用于保存链表首端的节点
   if (mlink->length > 0) {			// 判断链表是否为空
      do {
         tmp = mlink->np;			// 指向链表首端节点
         mlink->np = tmp->p;			// 将链表入口指向下一个节点
         free(tmp);					// 释放原先链表首端的节点
      } while(mlink->np);			// 判断链表是否为空
      mlink->length = 0;
   }
   return 0;
}
