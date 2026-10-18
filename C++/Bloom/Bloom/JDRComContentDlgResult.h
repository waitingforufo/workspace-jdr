#pragma once
#include "JDRComContentDlgResult.g.h"  // MIDL自动生成，无需手动创建

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::Bloom::implementation
{
	struct JDRComContentDlgResult : JDRComContentDlgResultT<JDRComContentDlgResult>
	{
		JDRComContentDlgResult() = default;

		winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult DialogResult()
		{
			return m_dialogResult;
		}

		void DialogResult(winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult const& value)
		{
			m_dialogResult = value;
		}

		winrt::Windows::Foundation::Collections::IVector<int32_t> Status()
		{
			return m_status;
		}

		void Status(winrt::Windows::Foundation::Collections::IVector<int32_t> const& value)
		{
			m_status = value;
		}

	private:
		winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult
			m_dialogResult{winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult::None};

		winrt::Windows::Foundation::Collections::IVector<int32_t>
			m_status{ winrt::single_threaded_vector<int32_t>() };  // 默认非空集合，非nullptr
	};
}

namespace winrt::Bloom::factory_implementation
{
	struct JDRComContentDlgResult : JDRComContentDlgResultT< JDRComContentDlgResult,implementation::JDRComContentDlgResult>
	{ };
}