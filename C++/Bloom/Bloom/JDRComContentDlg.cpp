#include "pch.h"

#include "JDRComContentDlg.h"
#include "JDRComContentDlg.g.cpp"

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

		//TODO:JDR


		// winrt::Microsoft::UI::Xaml::Window::Current() : winrt::Microsoft::UI::Xaml::Window
		// winrt::Microsoft::UI::Xaml::Window::Current().Content().XamlRoot();

		return ret;
	}

}//end namespace