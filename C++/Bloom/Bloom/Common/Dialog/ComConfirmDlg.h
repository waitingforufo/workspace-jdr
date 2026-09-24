#pragma once
#include "pch.h"

/*
* 全局通用确认对话框
* ■ 关键注意事项
*   1. 头文件命名控件：
*        所有XAML相关头文件必须使用 winrt/Microsoft.UI.Xaml.*， 绝对不能使用 winrt/Windows.UI.Xaml.*（这个是UWP的，会导致编译错误或运行时异常）
*   2. XamlRoot 必须设置：
*        WinUI3 中的 ContentDialog 在调用 ShowAsync()之前必须设置 XamlRoot 属性，否则会抛出 Element not found 异常。
*   3. 异步调用：
*        ShowAsync()是异步方法，调用方需要使用 co_await 等待结果。在事件处理程序中使用 fire_and_forget 来包装异步操作。
*   4. 返回时映射
*      · ContentDialogResult::Primary    -> 点击Yes
*      · ContentDialogResult::Secondary  -> 点击No
*      · ContentDialogResult::None       -> 按ESC或通过其他方式关闭
*   5. 一次只能显示一个对话框：
*        WinUI3中每个线程同时只能打开一个 ContentDialog，尝试同时打开多个会抛出异常。
* 
*/
namespace Bloom::Common::Dialog
{
	struct ComConfirmDlg
	{
		/// <summary>
		/// 确认对话框(Yes/No型）（全局通用）
		/// ※静态方法
		/// <para>有固定2个按钮，Yes和No。 Yes表示同意；No表示不同意。</para>
		/// 
		/// <para>
		/// WinUI3中实现通用确认对话框，核心是使用 ContentDialog 控件，并通过一个静态辅助类来封装。
		/// 注意： ContentDialog 必须设置 XamlRoot 才能显示，所以需要在调用时传入当前页面的根元素。
		/// </para>
		/// 
		/// <para>
		/// ■调用方法
		/// ① 包含头文件
		///      #include "Common/Dialog/ComConfirmDlg.h"
		/// 
		/// ② 调用此对话框的事件函数返回值改成 fire_and_forget
		///      fire_and_forget MainWindow::myButton_Click(...)
		///      { ... }
		/// 
		/// ③ 调用此对话框
		/// 
		///      // 调用全局确认对话框
		///      // 注意：调用方函数必须是 co_await 异步函数，或者使用 fire_and_forget
		///      bool confirmed = co_await ::Bloom::Common::Dialog::ComConfirmDlg::ShowAsync(
		///          RootStackPanel().XamlRoot(),           // 传入当前页面的 XamlRoot
		///          L"确认",                                // 标题
		///          L"确定要进行此操作吗（数据可能无法恢复）？"  // 内容
		///      );
		/// 
		///      if (confirmed)
		///      {
		///          // 点击 Yes
		///          rst = true;
		///      }
		///      else
		///      {
		///          // 点击 No
		///          rst = false;
		///      }
		/// 
		/// </para>
		/// </summary>
		/// <param name="xamlRoot">对话框页面的 XamlRoot(用于定位对话框的宿主)
		///                        e.g.: x:Name="RootStackPanel"时：  
		///                          RootStackPanel().XamlRoot()来取得</param>
		/// <param name="title">对话框标题</param>
		/// <param name="content">对话框内容</param>
		/// <returns>true: 用户点击Yes； false: 用户点击No</returns>
		static winrt::Windows::Foundation::IAsyncOperation<bool> ShowAsync(
			winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot,
			winrt::hstring const& title,
			winrt::hstring const& content);
	};
}