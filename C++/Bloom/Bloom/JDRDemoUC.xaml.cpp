#include "pch.h"
#include "JDRDemoUC.xaml.h"
#if __has_include("JDRDemoUC.g.cpp")
#include "JDRDemoUC.g.cpp"
#endif


namespace winrt::Bloom::implementation
{
	JDRDemoUC::JDRDemoUC()
	{
		InitializeComponent();
	}

	void JDRDemoUC::SetInstanceId(int32_t id)
	{
		// C++/WinRT中 x:Name 生成的是访问器函数，调用时必须加括号
		InstanceIdText().Text(L"Instance ID:" + winrt::to_hstring(id));
	}

	void JDRDemoUC::ActionButton_Click(winrt::Windows::Foundation::IInspectable const& sender,
		                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		TitleText().Text(L"已被点击！");
	}

}//end namespace
