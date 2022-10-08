#include <string.h>

int main(){
   
   char f_str[MAX_LENGTH] = {0};	// 用于定义查找字符串
   int find_mode = 0;				// 用于保存查找模式，默认为0，即完全匹配模式
   int res;							// 用于保存查找结果
   
         case 6: {
            int score = 0;			// 用于保存匹配项目的个数
            puts("请输入要查找的字符串：");
            puts("“=”开始表示完全匹配，“?”用于替代一个字符，“*”用于替代多个
            字符");
            scanf(GET_NAME, f_str);	// 用户输入查找字符串
            if (f_str[0] != '=')		// 判断是否是模糊查找模式
               find_mode = 1;
            else						// 如果是完全匹配模式，执行下列语句
               memmove(f_str, f_str + 1, strlen(f_str));
               // 去掉字符串中第一位的“=”符号
            for(i = 0; i < l; i++) {
               if (find_mode == 0) 	// 以完全匹配模式查找字符串
               if (strlen(p_list[i]) == strlen(f_str))
               // 用以比较两个字符串长度是否相等
                  else
                     res = 0;
               else
                  res = hazy_find(p_list[i], f_str);
                  // 以模糊查找模式查找字符串
               if (res != NULL) {
                  printf("%d : %s\n", i + 1, p_list[i]);	// 输出找到的字符串
                  score++;
               }
            }
            if (score < 1)
               puts("找不到匹配的项目");
         }
   
}




int hazy_find(const char *str1, const char *str2)
{
   const char *ct = "*?";				// 保存通配符
   int i, j = 0;						// 用于保存str1、str2的操作位置
   int l;								// 用于保存str2的长度
   int k;								// 用户保存查找时每次查找的长度
   char sec[MAX_FILE_LENGTH];			// 用户保存每次查找的字符串分段
   int res;								// 用于保存查找结果
   const char *res2;						// 用于保存查找结果
   l = strlen(str2);					// 取得str2字符串长度
   if (l < 1)
      return 0;				// 如果str2长度小于1，则认为没有匹配的字符串
   for (i = 0; i < l; i++) {			// 遍历字符串str2
      if (str2[i] == '?') {				// 遍历到通配符“?”
         j++;
      }
      else if (str2[i] == '*') {			// 遍历到通配符“*”
         while(!(k = strcspn(str2 + i + 1, ct))) {
         // 取得距离下一个通配符的长度，如果为0则执行循环体
            if (*(str2 + i + 1))	// 判断下一个符号是不是字符串结束符（ASCII码为0）
               i++;				// 如果下一个符号也是通配符，则跳过
            else
               return 1;	// 如果下一个符号是字符串结束符，认为已有匹配字符串
         }
         strncpy(sec, str2 + i +1, k);	// 将通配符之间的字符串复制到sec数组
         sec[k] = '\0';					// 为数组加入字符串结束符
         res2 = strstr(str1 + j, sec);	// 在项目中查找字符串片段
         if (!res2)
            return 0;						// 找不到该片段，认为不匹配
         i += k;							// 将str1的操作位置后移
         j += strlen(str1 + j) - strlen(res2) + k;	// 将str2的操作位置后移
      }
      else {								// 遍历到其它字符
         k = strcspn(str2 + i, ct);		// 取得到下个通配符号间的长度
         res = strncmp(str1 +j, str2 + i, k);  // 比较两个字符串指定长度的内容
         if (res)
            return 0;						// 不相同时，认为不匹配
         else
            i += k - 1;					// 将str1的操作位置后移
            j += k;						// 将str2的操作位置后移
      }
   }
   return 1;								// 没有产生不匹配的情况
}
