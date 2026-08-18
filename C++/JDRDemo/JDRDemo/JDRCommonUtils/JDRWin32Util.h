#pragma once
#include "pch.h"  // 头文件里包含pch.h是合法的，用于支持IDE的代码提示和独立编译（推荐显式包含预编译头文件）

namespace JDRDemo::JDRCommonUtils
{
	/// <summary>
	/// 与Win32交互相关的功能函数类(包含Windows App SDK)
	/// </summary>
	class JDRWin32Util
	{
	public:
		/// <summary>
		/// 获取WinUI3窗口类实例的HWND句柄
		/// </summary>
		/// <param name="window">WinUI3窗口类实例</param>
		/// <returns>HWND句柄</returns>
		HWND GetWindowHwnd(winrt::Microsoft::UI::Xaml::Window const& window);
	};

}// end namespace


