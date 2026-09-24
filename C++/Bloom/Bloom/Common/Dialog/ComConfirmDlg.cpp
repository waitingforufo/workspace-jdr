#include "pch.h"
#include "ComConfirmDlg.h"

namespace Bloom::Common::Dialog
{
	winrt::Windows::Foundation::IAsyncOperation<bool> ComConfirmDlg::ShowAsync(
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot,
		winrt::hstring const& title,
		winrt::hstring const& content)
	{
		// 创建 ContentDialog实例
		winrt::Microsoft::UI::Xaml::Controls::ContentDialog dlg;

		// 设置 XamlRoot(WinUI3中必须设置，否则会抛出异常)
		dlg.XamlRoot(xamlRoot);

		// 这只标题和内容
		dlg.Title(winrt::box_value(title));
		dlg.Content(winrt::box_value(content));

		// 设置 Yes/No 按钮文本
		dlg.PrimaryButtonText(L"Yes");
		dlg.SecondaryButtonText(L"No");

		// 设置默认按钮为 Yes（按回车键触发）
		dlg.DefaultButton(winrt::Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);

		// 异步显示对话框并等待用户选择
		winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult result = co_await dlg.ShowAsync();

		// 根据返回值判断用户点击了哪个按钮
		// Primary = Yes, Secondary = No, None = 按ESC或其他方式关闭
		// 返回值： true:用户点击了Yes； false:用户点击了No或者按Esc关闭了对话框
		co_return (result == winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	}

}//end namespace