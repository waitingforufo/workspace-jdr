#include "pch.h"
#include "JDRCheckItem.h"
#include "Common.Dialog.JDRCheckItem.g.cpp"

namespace winrt::Bloom::Common::Dialog::implementation
{

	winrt::hstring JDRCheckItem::Text()
	{
		return m_text;
	}

	void JDRCheckItem::Text(winrt::hstring const& value)
	{
		m_text = value;
	}

	bool JDRCheckItem::IsChecked() 
	{
		return m_isChecked;
	}

	void JDRCheckItem::IsChecked(bool value)
	{
		m_isChecked = value;
	}

}