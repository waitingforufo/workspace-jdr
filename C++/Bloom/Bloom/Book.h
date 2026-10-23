#pragma once
#include "Book.g.h"

namespace winrt::Bloom::implementation
{

	struct Book : BookT<Book>
	{
		Book() = default;
		Book(winrt::hstring const& title, winrt::hstring const& author)
			: m_title(title), m_author(author) { }

		winrt::hstring Title() const { return m_title; }
		void Title(winrt::hstring const& value) { m_title = value; }

		winrt::hstring Author() const { return m_author; }
		void Author(winrt::hstring const& value) { m_author = value; }

	private:
		winrt::hstring m_title;
		winrt::hstring m_author;
	};

};

namespace winrt::Bloom::factory_implementation
{

	struct Book : BookT<Book, implementation::Book>{};

}

