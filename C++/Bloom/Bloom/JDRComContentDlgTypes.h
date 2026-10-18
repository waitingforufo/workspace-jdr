#pragma once
#include <string>
#include <vector>

namespace Bloom 
{
	/// <summary>
	/// 对话框项目类型
	/// </summary>
	enum class JDRComContentDlgItemType : int
	{
		Text = 1,       // 普通文字行
		CheckBox = 2,   // 单个Checkbox
		RadioGroup = 3  // 一组RadioButton
	};

	/// <summary>
	/// 单选钮的类型
	/// </summary>
	struct JDRComContentDlgRadioItem
	{
		std::wstring Text;
		bool IsChecked = false;
	};

	/// <summary>
	/// 对话框项目结构体
	/// </summary>
	struct JDRComContentDlgItem
	{
		// 类型
		JDRComContentDlgItemType Type = JDRComContentDlgItemType::Text;

		/// <summary>
		/// Type=Text:       文字行内容
		/// Type=CheckBox:   Checkbox本体
		/// Type=RadioGroup: 单选钮组名
		/// </summary>
		std::wstring Text;

		// 仅Type=CheckBox时候有效
		bool IsChecked = false;

		// 仅Type=RadioGroup时候有效
		std::vector<JDRComContentDlgRadioItem> Children;
	};

	struct JDRComContentDlgArgs
	{
		std::vector<JDRComContentDlgItem> Items;
	};
}