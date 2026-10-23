#pragma once

// 注意： .h里包含 .g.h !! 
#include "Library.g.h"

// 引用其他 idl的runtimeclass的时候， 必须包含实现文件的头文件。 例如 Bloom/Book.h(手写的idl里的runtimeclass的实现类头文件)
// 注意：使用的时候，要用投影类型 Bloom::Book， 而不是 winrt::Bloom::implementation::Book(runtimeclass实现值类型结构体）
#include "Book.h"

/*
* 这里定义的 Library 是 idl里定义的 runtimeclass。
* 使用的时候不会包含这个头文件， 而是包含投影头文件， 使用投影类型 Bloom::Library（而不是 winrt::Bloom::implementation::Library 结构体值类型）
* ※ Bloom::Library 是COM投影类型， 在 winrt/Bloom.h里定义。
* 
* ■使用方法
* 1. 包含头文件
* 
*   // 聚合投影头文件，包含 Bloom::Book, Bloom::Library
*   #include <winrt/Bloom.h>
* 
* 2. 使用投影类 Bloom::Book, Bloom::Library
* 
*   // 创建Book
*   Bloom::Book book1{ L"书籍1", L"作者1" };
*   Bloom::Book book2{ L"书籍2", L"作者2" };
*  
*   // 创建Library
*   Bloom::Library lib{ L"北京图书馆" };
* 
*   // 设置FeaturedBook - 直接传入投影类型 Book
*   lib.FeaturedBook(book1);
*  
*  // 通过方法添加Book
*  lib.AddBook(book1);
*  lib.AddBook(book2);
*  
*  // 读取成员Book
*  Bloom::Book featured = lib.FeaturedBook();
*  printf("\n\n※※ Featured: %ls\n", featured.Title().c_str());
*  
*  // 遍历library中的所有Book
*  for (Bloom::Book const& book : lib.GetAllBooks())
*  {
*      printf("\n\n ※※ Book: %ls - %ls\n", book.Title().c_str(), book.Author().c_str());
*  }
* 
*/
namespace winrt::Bloom::implementation
{
	/// <summary>
	/// 在Library的实现类中，Book成员使用投影类型 Bloom::Book（本质是指向COM对象的智能指针），而不是 implementation::Book值类型。
	/// </summary>
	struct Library : LibraryT<Library>
	{
		Library() = default;
		Library(winrt::hstring const& name)
			: m_name(name) { }

		winrt::hstring Name() const { return m_name; }
		void Name(winrt::hstring const& value) { m_name = value; }

		// 返回投影类型Book（智能指针）
		Bloom::Book FeaturedBook() const { return m_featuredBook; }
		void FeaturedBook(Bloom::Book const& value) { m_featuredBook = value; }

		// 返回投影类型Book作为参数
		void AddBook(Bloom::Book const& book)
		{
			m_books.Append(book);  // IVector<Book> 底层是winrt集合
		}

		winrt::Windows::Foundation::Collections::IVector<Bloom::Book> GetAllBooks() const
		{
			return m_books;
		}

	private:
		winrt::hstring m_name;
		Bloom::Book m_featuredBook{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<Bloom::Book> 
			m_books{ winrt::single_threaded_vector<Bloom::Book>() };
	};

}

namespace winrt::Bloom::factory_implementation
{
	struct Library : LibraryT< Library, implementation::Library>{};
}
