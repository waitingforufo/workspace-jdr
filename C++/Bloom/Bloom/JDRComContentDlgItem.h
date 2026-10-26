#pragma once

#include "JDRComContentDlgItem.g.h"

namespace winrt::Bloom::implementation
{
	/// <summary>
	/// 确认对话框的显示项目
	/// </summary>
	struct JDRComContentDlgItem : JDRComContentDlgItemT<JDRComContentDlgItem>
	{
		JDRComContentDlgItem();

		// 项目类型
		Bloom::JDRComContentDlgItemType Type();
		void Type(Bloom::JDRComContentDlgItemType value);

		// Type=Text:             要显示的单行信息内容; 
		// Type=CheckBox:         忽略; 
		// Type=RadioButtonGroup: 单选组的标题
		winrt::hstring Text();
		void Text(winrt::hstring const& value);

		// Type=Text:             忽略
		// Type=CheckBox:         仅有一个元素，指定单行CheckBox的标题与默认选中状态
		// Type=RadioButtonGroup: 多个元素，每个元素指定单行RadioButton的标题与默认选中状态
		winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItemOpt> OptList();
		void OptList(winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItemOpt> const& value);

	private:
		Bloom::JDRComContentDlgItemType m_type{ Bloom::JDRComContentDlgItemType::Text };
		winrt::hstring m_text{ L"" };
		winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItemOpt> m_optList{nullptr};
	};
}//end namespace

namespace winrt::Bloom::factory_implementation
{
	struct JDRComContentDlgItem : JDRComContentDlgItemT< JDRComContentDlgItem, implementation::JDRComContentDlgItem>{};
}//end namespace