#pragma once
#include "../../JDRComContentDlgTypes.h"

#include "../../JDRComContentDlgResult.h"

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Windows.Foundation.h"

#include <string_view>

namespace Bloom::Common::Dialog
{
	class JDRComContentDlg {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="title">确认对话框标题</param>
		/// <param name="message">确认对话框信息</param>
		/// <param name="args">显示其他信息</param>
		/// <param name="primaryButtonText">主按钮文字</param>
		/// <param name="secondaryButtonText">次按钮文字</param>
		/// <param name="closeButtonText">关闭按钮文字</param>
		/// <param name="xamlRoot"></param>
		/// <returns></returns>
		static winrt::Windows::Foundation::IAsyncOperation<winrt::Bloom::IJDRComContentDlgResult> ShowAsync(
			std::wstring_view title,
			std::wstring_view message,
			Bloom::JDRComContentDlgArgs const& args,
			std::wstring_view primaryButtonText,
			std::wstring_view secondaryButtonText,
			std::wstring_view closeButtonText,
			winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
		);
	};
}
