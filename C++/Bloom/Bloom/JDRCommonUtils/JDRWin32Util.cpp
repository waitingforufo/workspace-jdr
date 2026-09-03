#include "pch.h"  // 必须包含！ 且必须是第一行！！ 绝对不可省略或挪动位置
///
/// C++开发中，永远不要依赖头文件来间接传递预编译头。把 #include "pch.h"放在每一个 .cpp文件的最顶端，是C++/WinRT开发中不可打破的铁律。
/// 

// 以下包含 1.自己的头文件； 2.其他工具类头文件
#include "JDRWin32Util.h"

#include <microsoft.ui.xaml.window.h>  // IWindowNative接口定义

namespace Bloom::JDRCommonUtils
{
	/// <summary>
	/// 获取WinUI3窗口类实例的HWND句柄
	/// 
	/// e.g.:调用方法
	///   // 在继承了 winrt::Microsoft::UI::Xaml::Window类的 XAML后台代码（CPP）里调用如下代码取得XAML（WinUI）的窗体对象（Window类）
	///   auto currWindow = winrt::Microsoft::UI::Xaml::Window::Current();
	///   if( !currWindow )
	///   {
	///     return;
	///   }
	/// 
	///   // 取得HWND句柄
	///   HWND curHWnd = JDRWin32Util::GetWindowHwnd( currWindow );
	///   
	/// </summary>
	/// <param name="window">WinUI3窗口类实例</param>
	/// <returns>HWND句柄</returns>
	HWND JDRWin32Util::GetWindowHwnd(winrt::Microsoft::UI::Xaml::Window const& window)
	{
		//将Window对象查询为IWindowNative接口
		auto windowNative{ window.as<::IWindowNative>() };

		HWND hWnd{ nullptr };
		windowNative->get_WindowHandle(&hWnd);

		return hWnd;
	}

}//end namespace