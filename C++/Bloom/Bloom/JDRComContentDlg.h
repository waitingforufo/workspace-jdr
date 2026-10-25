#pragma once

#include "JDRComContentDlg.g.h"

namespace winrt::Bloom::implementation
{
	/// <summary>
	/// 通用确认框的全局通用单例类
	/// 
	/// 纯静态runtimeclass（没有实例成员，不生成实例）不需要实例成员，
	/// 实现就是 不继承任何基类（通常是 ：JDRComContentDlgT）的 普通struct，
	/// 静态成员函数直接实现
	/// </summary>
	struct JDRComContentDlg
	{
		/// <summary>
		/// 显示通用的确认对话框
		/// </summary>
		/// <param name="title">标题</param>
		/// <param name="message">确认信息</param>
		/// <param name="items">附加内容（包括纯文本信息，checkbox，radiobutton组）</param>
		/// <param name="primaryButtonText">主按钮显示文字</param>
		/// <param name="secondaryButtonText">次按钮显示文字</param>
		/// <param name="closeButtonText">关闭按钮显示文字</param>
		/// <param name="parentXamlRoot"></param>
		/// <returns></returns>
		static winrt::Windows::Foundation::IAsyncOperation<
			winrt::Windows::Foundation::Collections::IVector<int32_t> >
			ShowAsync(winrt::hstring const& title,
				      winrt::hstring const& message,
				      winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItem> items,
				      winrt::hstring const& primaryButtonText = winrt::hstring{L"YES"},
				      winrt::hstring const& secondaryButtonText = winrt::hstring{L"NO"},
				      winrt::hstring const& closeButtonText = winrt::hstring{L"CANCEL"},
				      winrt::Microsoft::UI::Xaml::XamlRoot const& parentXamlRoot = winrt::Microsoft::UI::Xaml::Window::Current().Content().XamlRoot());
	};

}//end namespace

// ★ 即使是纯静态 runtimeclass，factory_implementation 也不能省：
//   cppwinrt 生成的 JDRComContentDlg.g.cpp 会引用它来完成激活工厂注册
namespace winrt::Bloom::factory_implementation
{
	struct JDRComContentDlg : JDRComContentDlgT< JDRComContentDlg, implementation::JDRComContentDlg>
	{};
}//end namespace
