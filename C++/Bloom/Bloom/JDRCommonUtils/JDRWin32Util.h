#pragma once
#include "pch.h"  // 头文件里包含pch.h是合法的，用于支持IDE的代码提示和独立编译（推荐显式包含预编译头文件）

namespace Bloom::JDRCommonUtils
{
	/// <summary>
	/// 与Win32交互相关的功能函数类(包含Windows App SDK)
	/// </summary>
	class JDRWin32Util
	{
	public:
		
		/// <summary>
		/// 获取WinUI3窗口类实例的HWND句柄
		/// ※静态函数
		/// 
		/// <para>
		/// e.g.:调用方法
		/// </para>
		/// <para>
		///   // 在继承了 winrt::Microsoft::UI::Xaml::Window类的 XAML后台代码（CPP）里调用如下代码取得XAML（WinUI）的窗体对象（Window类）
		/// 
		///   #include "JDRCommonUtils/JDRWin32Util.h"
		/// 
		///   auto currWindow = winrt::Microsoft::UI::Xaml::Window::Current();
		///   if( !currWindow )
		///   {
		///     return;
		///   }
		/// 
		///   // 取得HWND句柄
		///   HWND curHWnd = ::Bloom::JDRCommonUtils::JDRWin32Util::GetWindowHwnd( currWindow );
		/// </para>
		/// </summary>
		/// <param name="window">WinUI3窗口类实例</param>
		/// <returns>HWND句柄</returns>
		static HWND GetWindowHwnd(winrt::Microsoft::UI::Xaml::Window const& window);

		/// <summary>
		/// XAML窗口的启动位置，大小设置
		/// ※静态函数
		/// 
		/// <para>
		///   e.g.:调用方法
		/// </para>
		/// <para>
		///     // 在继承了 winrt::Microsoft::UI::Xaml::Window类的 XAML后台代码（CPP）里(目的是想轻松取得Window类）
		/// 
		///       #include "JDRCommonUtils/JDRWin32Util.h"
		/// 
		///       MainWindow::MainWindow()
		///       {
		///           InitializeComponent();  // 初始化XAML控件
		/// 
		///           // 建议在XAML窗体的构造函数里调用，这样在XAML窗体形成时（还没有显示）设定好位置，大小
		///           ::Bloom::JDRCommonUtils::JDRWin32Util::SetStartupPlacement( *this, 240, 160, 600, 400);
		///       }
		/// </para>
		/// </summary>
		/// <param name="window">目标XAML窗体</param>
		/// <param name="posX">启动位置X坐标</param>
		/// <param name="posY">启动位置Y坐标</param>
		/// <param name="width">窗口宽度</param>
		/// <param name="height">窗口高度</param>
		static void SetStartupPlacement(winrt::Microsoft::UI::Xaml::Window const& window, 
			                     int32_t posX, 
			                     int32_t posY, 
			                     int32_t width, 
			                     int32_t height);
	};

}// end namespace