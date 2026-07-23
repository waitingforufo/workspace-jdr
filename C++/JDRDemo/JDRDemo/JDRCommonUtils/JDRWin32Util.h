#pragma once

namespace JDRCommonUtils
{
	/// <summary>
	/// 与Win32交互相关的功能函数类
	/// </summary>
	class JDRWin32Util
	{
	public:
		/// <summary>
		/// 获取WinUI3窗口的HWND句柄
		/// </summary>
		/// <param name="window">WinUI3窗口类</param>
		/// <returns>HWND句柄</returns>
		HWND GetWindowHwnd(winrt::Microsoft::UI::Xaml::Window const& window);
	};

}// end namespace


