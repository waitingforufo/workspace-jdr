#pragma once
//#include "pch.h"
#include "Common.Dialog.JDRCheckItem.g.h"

namespace winrt::Bloom::Common::Dialog::implementation
{
	struct JDRCheckItem : JDRCheckItemT<JDRCheckItem>
	{
		JDRCheckItem() = default;

		// CheckBox旁边显示的文字属性
		winrt::hstring Text();
		void Text(winrt::hstring const& value);

		// 选中状态属性
		bool IsChecked();
		void IsChecked(bool value);

	private:
		// CheckBox旁边显示的文字
		winrt::hstring m_text;

		// 选中状态
		bool m_isChecked{ false };

	};
}

namespace winrt::Bloom::Common::Dialog::factory_implementation
{
	struct JDRCheckItem : JDRCheckItemT<JDRCheckItem, implementation::JDRCheckItem>
	{ };
}
