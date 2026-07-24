#include "pch.h"
#include "JDRWin32Util.h"

#include <microsoft.ui.xaml.window.h>  // IWindowNative接口定义

namespace JDRCommonUtils
{
	/// <summary>
	/// 获取WinUI3窗口类实例的HWND句柄
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