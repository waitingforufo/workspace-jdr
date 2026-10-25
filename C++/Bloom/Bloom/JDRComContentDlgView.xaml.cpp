#include "pch.h"

#include "JDRComContentDlgView.xaml.h"

#if __has_include("JDRComContentDlgView.g.cpp")
#include "JDRComContentDlgView.g.cpp"
#endif

namespace winrt::Bloom::implementation
{
	JDRComContentDlgView::JDRComContentDlgView()
	{
		InitializeComponent();
	}

	void JDRComContentDlgView::SetMsg(winrt::hstring const& msg)
	{
		MsgText().Text(msg);
	}

	void JDRComContentDlgView::SetItems(Windows::Foundation::Collections::IVector<
		                                    Bloom::JDRComContentDlgItem> const& items)
	{
		//TODO:JDR
	}

	Windows::Foundation::Collections::IVector<int32_t> JDRComContentDlgView::GetSelection()
	{
		std::vector<int32_t> ret;

		//TODO:JDR

		return winrt::single_threaded_vector<int32_t>(std::move(ret));
	}

}//end namespace
