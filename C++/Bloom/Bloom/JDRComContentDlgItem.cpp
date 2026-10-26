#include "pch.h"

#include "JDRComContentDlgItem.h"
#include "JDRComContentDlgItem.g.cpp"

namespace winrt::Bloom::implementation
{
	JDRComContentDlgItem::JDRComContentDlgItem()
	{
		//由于没有 xaml， 所以也不会有InitlizeComponent()函数（初始化xaml文件定义组件的函数）
		//InitlizeComponent();

		// IVector属性必须初始化，否则默认是nullptr
		m_optList = winrt::single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();
	}

	Bloom::JDRComContentDlgItemType JDRComContentDlgItem::Type()
	{
		return m_type;
	}

	void JDRComContentDlgItem::Type(Bloom::JDRComContentDlgItemType value)
	{
		m_type = value;
	}

	winrt::hstring JDRComContentDlgItem::Text()
	{
		return this->m_text;
	}

	void JDRComContentDlgItem::Text(winrt::hstring const& value)
	{
		m_text = value;
	}

	winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItemOpt> JDRComContentDlgItem::OptList()
	{
		return m_optList;
	}

	void JDRComContentDlgItem::OptList(winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItemOpt> const& value)
	{
		m_optList = value;
	}

}//end namespace