#include "pch.h"

#include "JDRComContentDlg.h"
#include "JDRComContentDlg.g.cpp"

//#include "JDRComContentDlgView.xaml.h"
#include "winrt/Bloom.h"

namespace winrt::Bloom::implementation
{
	winrt::Windows::Foundation::IAsyncOperation<
		winrt::Windows::Foundation::Collections::IVector<int32_t> >
		JDRComContentDlg::ShowAsync(winrt::hstring const& title,
			                        winrt::hstring const& message,
			                        winrt::Windows::Foundation::Collections::IVector<Bloom::JDRComContentDlgItem> items,
			                        winrt::hstring const& primaryButtonText,
			                        winrt::hstring const& secondaryButtonText,
			                        winrt::hstring const& closeButtonText,
			                        winrt::Microsoft::UI::Xaml::XamlRoot const& parentXamlRoot)
	{

		winrt::Windows::Foundation::IAsyncOperation<
			winrt::Windows::Foundation::Collections::IVector<int32_t> > ret;

		

		winrt::Microsoft::UI::Xaml::Controls::ContentDialog dlg;

		// WinUI3桌面应用必须显式设置XamlRoot，否则ShowAsync()会抛出异常
		// 但窗口应用可以如下取
		// winrt::Microsoft::UI::Xaml::Window::Current() : winrt::Microsoft::UI::Xaml::Window
		// winrt::Microsoft::UI::Xaml::Window::Current().Content().XamlRoot();
		// 
		// 多窗口应用建议把XamlRoot作为参数传入
		dlg.XamlRoot(parentXamlRoot);

		dlg.Title(winrt::box_value(title));  // 确认窗口标题

		dlg.PrimaryButtonText(primaryButtonText);
		dlg.SecondaryButtonText(secondaryButtonText);
		dlg.CloseButtonText(closeButtonText);

		dlg.DefaultButton(winrt::Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);

		// UI部分
		//Bloom::JDRComContentDlgView content =
		//	winrt::make<Bloom::implementation::JDRComContentDlg>();  // 直接用结构体值类型自行生成投影类型， NG
		Bloom::JDRComContentDlgView content = Bloom::JDRComContentDlgView();  // 使用投影类型

		content.SetMsg(message);

		if (items)
		{
			content.SetItems(items);
		}
		else
		{
			// 设定空列表，防止nullptr
			content.SetItems(winrt::single_threaded_vector<Bloom::JDRComContentDlgItem>());
		}//end if

		dlg.Content(content);

		co_await dlg.ShowAsync();

		// 对话框关闭后读取选择状态
		co_return content.GetSelection();
	}

}//end namespace