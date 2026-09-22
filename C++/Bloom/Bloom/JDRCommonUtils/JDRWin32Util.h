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
		static void SetStartupPlacement(
			winrt::Microsoft::UI::Xaml::Window const& window, 
			int32_t posX, 
			int32_t posY, 
			int32_t width, 
			int32_t height);

		/// <summary>
		/// 从指定元素的资源开始向上查找指定key的资源定义
		/// ※从一个控件开始向父级，再向App找资源，可以自己走视觉树。
		/// 
		/// <para>
		///   e.g.: 调用方法
		/// </para>
		/// <para>
		///   // 向上查找资源例子 例子：XAML里定义了 x:Name="myButton"
		///   auto resObj = ::Bloom::JDRCommonUtils::JDRWin32Util::TryFindResource(myButton(), L"MainWindowCardPadding");
		///   if (resObj)
		///   {
		///       auto padding = winrt::unbox_value<winrt::Microsoft::UI::Xaml::Thickness>(resObj);
		///   }
		/// </para>
		/// </summary>
		/// <param name="startElement">查找资源的起点元素（指定XAML里的某个元素， 必须是 FrameworkElement类型）</param>
		/// <param name="resourceKey">查找的资源key</param>
		/// <returns>nullptr:查找失败； 以外：指定key的资源对象</returns>
		static winrt::Windows::Foundation::IInspectable TryFindResource(
			winrt::Microsoft::UI::Xaml::FrameworkElement const& startElement,
			winrt::hstring const& resourceKey);

	};

}// end namespace