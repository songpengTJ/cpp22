int link_del(link_t *mlink, int p)
{
   node_t *tmp, *tmp2;					// 删除操作使用的临时指针
   int i;
   if (p < 1 || p > mlink->length) {	// 判断序号是否有效
      printf("输入的节点位置错误");
      return 1;
   }
   tmp = mlink->np;						// 指向首端节点
   if (p == 1) {						// 判断删除的是否为首端节点
      mlink->np = tmp->p;	// 将链表入口地址置为首端节点的指针成员指向的地12	址
      free(tmp);							// 释放被删除节点的内存空间
   }
   else {
      i = p - 2;							// 计算遍历的次数
      while(i) {							// 遍历到被删除节点前的一个节点
         tmp = tmp->p;
         i--;
      }
      tmp2 = tmp->p;			// 保存被删除节点的内存地址
      tmp->p = tmp2->p;	// 将被删除节点前一个节点的指针成员指向后一个节点
      free(tmp2);			// 释放被删除节点的内存空间
   }
   mlink->length--;			// 将链表的长度减1
   return 0;
}
