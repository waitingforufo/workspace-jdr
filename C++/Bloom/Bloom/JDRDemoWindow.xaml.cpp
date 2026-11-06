#include "pch.h"
#include "JDRDemoWindow.xaml.h"
#if __has_include("JDRDemoWindow.g.cpp")
#include "JDRDemoWindow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Windowing.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Bloom::implementation
{

	JDRDemoWindow::JDRDemoWindow()
	{
		InitializeComponent();
		
		// this是 JDRDemoWindow，它继承自 Microsoft::UI::Xaml::Window
		// AppWindow 常用能力清单（你后面图形 / 窗口控制会用到）
		//	窗口标题：Title()
		//	大小：Resize() / ResizeClient()
		//	位置：Move() / MoveAndResize()
		//	标题栏自定义：appWin.TitleBar()
		//	窗口置顶、Z 序、最小化、全屏、弹窗 Presenter 模式
		//	设置窗口图标、任务栏图标
		winrt::Microsoft::UI::Windowing::AppWindow appWin = this->AppWindow();

		if (appWin)
		{
			appWin.Title(L"Bloom - JDRDemo窗口");
			appWin.Resize({ 800,600 });
		}
	}


}

void winrt::Bloom::implementation::JDRDemoWindow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}
