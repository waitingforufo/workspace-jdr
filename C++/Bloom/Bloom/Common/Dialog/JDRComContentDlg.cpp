#include "pch.h"

#include "JDRComContentDlg.h"

#include "JDRComContentDlgContent.g.h"
#include "JDRComContentDlgResult.g.h"

#include <atomic>

using namespace winrt::Microsoft::UI::Xaml;

namespace Bloom::Common::Dialog
{
	static std::atomic_bool s_isShowing{ false };

	winrt::Windows::Foundation::IAsyncOperation<winrt::Bloom::JDRComContentDlgResult>
		JDRComContentDlg::ShowAsync(
			std::wstring_view title,
			std::wstring_view message,
			Bloom::JDRComContentDlgArgs const& args,
			std::wstring_view primaryButtonText,
			std::wstring_view secondaryButtonText,
			std::wstring_view closeButtonText,
			winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
		)
	{
		bool expected = false;

		if (!s_isShowing.compare_exchange_strong(expected, true))
		{
			// 防重入：返回空结果(DialogResult=None, Status为空集合)
			winrt::Bloom::JDRComContentDlgResult empty = winrt::Bloom::JDRComContentDlgResult{};

			empty.DialogResult(Controls::ContentDialogResult::None);
			empty.Status(winrt::single_threaded_vector<int32_t>());

			co_return empty;
		}//end if

		try {

			winrt::Bloom::JDRComContentDlgContent contentDlgContent{};

			contentDlgContent.Initialize(message, args);

			Controls::ContentDialog dialog{};

			dialog.Title(winrt::box_value(winrt::hstring{ title }));
			dialog.Content(contentDlgContent);

			dialog.XamlRoot(xamlRoot);                    // WinUI 3 必须设置

			if (!primaryButtonText.empty())
				dialog.PrimaryButtonText(winrt::hstring{primaryButtonText});
			if (!secondaryButtonText.empty())
				dialog.SecondaryButtonText(winrt::hstring{ secondaryButtonText });
			if (!closeButtonText.empty())
				dialog.CloseButtonText(winrt::hstring{ closeButtonText });

			dialog.DefaultButton(Controls::ContentDialogButton::Primary);

			auto dialogResult = co_await dialog.ShowAsync();
			auto result = contentDlgContent.CollectResult(dialogResult);

			s_isShowing = false;
			co_return result;
		}
		catch (...)
		{
			s_isShowing = false;
			throw;
		}//end try
	}

}//end namespace