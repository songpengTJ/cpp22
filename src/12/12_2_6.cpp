int main () {
   float a, b;
   cin >> a >> b;					// 输入变量a和b
   try								// 执行代码段try
   {
      if (b == 0)
         throw b;	// 如果b为0，throw语句将b的值抛出，终止try代码段执行
      cout << a / b << endl;
   } 
   catch (float n)	// 如果throw语句执行，接受throw语句抛出的值
   {
      cout << "出错是因为b = " << n << endl;
   }
   return 0;
}   
