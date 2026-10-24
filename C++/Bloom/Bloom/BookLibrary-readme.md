
 ### 这里定义的 Library 是 **idl里定义的 runtimeclass**。
 ### 使用的时候不会包含这个头文件， 而是包含投影头文件， 使用投影类型 Bloom::Library（而不是 winrt::Bloom::implementation::Library 结构体值类型）
 ### ※ Bloom::Library 是COM投影类型， 在 winrt/Bloom.h里定义。
 
 # ■使用方法
 ### 1. 包含头文件
 
   // 聚合投影头文件，包含 Bloom::Book, Bloom::Library  
   ```c
   #include <winrt/Bloom.h>
   ```
 
 ### 2. 使用投影类 Bloom::Book, Bloom::Library
 
 ```c
   // 创建Book  
   Bloom::Book book1{ L"书籍1", L"作者1" };
   Bloom::Book book2{ L"书籍2", L"作者2" };
  
   // 创建Library
   Bloom::Library lib{ L"北京图书馆" };
 
   // 设置FeaturedBook - 直接传入投影类型 Book
   lib.FeaturedBook(book1);
  
  // 通过方法添加Book
  lib.AddBook(book1);
  lib.AddBook(book2);
  
  // 读取成员Book
  Bloom::Book featured = lib.FeaturedBook();
  printf("\n\n※※ Featured: %ls\n", featured.Title().c_str());
  
  // 遍历library中的所有Book
  for (Bloom::Book const& book : lib.GetAllBooks())
  {
      printf("\n\n ※※ Book: %ls - %ls\n", book.Title().c_str(), book.Author().c_str());
  }
  ```

 
