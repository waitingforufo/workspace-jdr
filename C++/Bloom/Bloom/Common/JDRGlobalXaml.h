/* 
* ■JDRGlobalXaml
*   全局共通单例类（属性可以在Xaml里用 {x:Bind}绑定，且自动监听属性值变化
*   
* ■实例生成方法
*   1.包含头文件
*       #include "Common/JDRGlobalXaml.h"
* 
*   2.生成单例实例
*       Bloom::Common::JDRGlobalXaml jdrGlobalXamlInst = Bloom::Common::JDRGlobalXaml::GetInstance();
*       or
*       auto jdrGlobalXamlInst = Bloom::Common::JDRGlobalXaml::GetInstance();
* 
* ■在 XAML里用 {x:Bind}绑定属性的方法
*   原理： 1. JDRGlobalXaml 用 JDRGlobalXaml.idl文件来声明runtimeclass， 在这个runtimeclass里暴露出来的属性都可以在 XAML里进行绑定。
*            ※想在XAMl里绑定的属性，先在 JDRGlobalXaml.idl里暴露出来。
*         2. 在任何窗口 XAML的 idl文件里，包含 JDRGlobalXaml.idl里的runtimeclass， 即可绑定 JDRGloalXaml类里的属性。
*            例如， 要在 MainWindow.xaml 里绑定 JDRGlobalXaml的属性，可以
*              ① MainWindow.idl
*                   import "Commom\\JDRGlobalXaml.idl"
* 
*                   namespace Bloom
*                   {
*                       [default_interface]
*                       runtimeclass MainWindow : Microsoft.UI.Xaml.Window
*                       {
*                           MainWindow();
* 
*                           Bloom.Common.JDRGlobalXaml GlobalXaml{ get; };  // 用 GlobalXaml的名字将 JDRGlobalXaml的实例暴露给 MainWindow.Xaml去使用
*                       }
*                   }
* 
*              ② MainWindow.xaml.h
*                   ...
*                   #include "Common/JDRGlobalXaml.h"  // 包含头文件
* 
*                   namespace winrt::Bloom::implementation
*                   {
*                       struct MainWindow : MainWindowT<MainWindow>
*                       {
*                           MainWindow();
* 
*                           Bloom::Common::JDRGlobalXaml GlobalXaml() const;  // runtimeclass里定义的 GlobalXaml{ get; }的实现函数。属性 GlobalXaml的 getter
*                       }
*                   }
* 
*              ③ MainWindow.xaml.cpp
*                   ...
*                   
*                   namespace winrt::Bloom::Implementation
*                   {
*                       MainWindow::MainWindow()
*                       {
*                           InitializeComponent();  // 初始化 XAML控件
*                       }
* 
*                       Bloom::Common::JDRGlobalXaml MainWindow::GlobalXaml() const  // 属性 GlobalXaml 的 getter函数
*                       {
*                           return Bloom::Common::JDRGlobalXaml::getInstance();  // 生成单例实例
*                       }
*                   }
* 
*              ※ 以上代码，就可以在 MainWindow.xaml 里 用 {x:Bind}来绑定 全局单例类实例(JDRGlobalXaml）了，用 GlobalXaml这个名字。
* 
*              ④ MainWindow.xaml
*                   <?xml version="1.0" encoding="utf-8"?>
*                   <window
*                       x:Class="Bloom.MainWindow"
*                       ...
*                       xmlns:local="using:Bloom"
*                       ...
*                   >
*
*                       <StackPanel Orientation="Vertical"
*                                   HorizontalAlignment="Center"
*                                   VerticalAlignment="Center">
* 
*                           <!-- 绑定到代码隐藏类的 GlobalXaml属性。Mode=OneWay必须，因为默认是 OneTime -->
*                           <TextBlock Text="{x:Bind GlobalXaml.Cnt, Mode=OneWay}"
*                                      FontSize="24" />
*                           
*                           <Button x:Name="myButton"
*                                   Content="Incrememt"
*                                   Click="myButton_Click" />
* 　　　　　　            </StackPanel>
*                   </window>
* 
*              ⑤ 用例： myButton_Click()函数里可以修改 GlobalXaml.Cnt属性值，更新会自动反应到 XAML里。
*                 
*                 ...
*                 auto jdrGlobalXaml = Bloom::Common::JDRGlobalXaml::GetInstance();
* 
*                 jdrGlobalXaml.Cnt( jdrGlobalXaml.Cnt() + 1 );
* 
*/
#pragma once
#include "pch.h"
#include "Common.JDRGlobalXaml.g.h"  // MIDL生成，无需路径前缀(Generated Files已在包含路径中）

namespace winrt::Bloom::Common::implementation
{
	/// <summary>
	/// 全局共通单例类（属性可以在 XAML 里直接绑定）
	/// </summary>
	struct JDRGlobalXaml : JDRGlobalXamlT<JDRGlobalXaml>
	{
		JDRGlobalXaml() = default;

		// 单例实例取得
		static Bloom::Common::JDRGlobalXaml getInstance();

		/// <summary>
		/// Cnt属性 - getter
		/// </summary>
		/// <returns></returns>
		int32_t Cnt() const;

		/// <summary>
		/// Cnt属性 - setter
		/// </summary>
		/// <param name="value"></param>
		void Cnt(int32_t value);

		/// <summary>
		/// INotifyPropertyChanged实现
		/// </summary>
		/// <param name="handler"></param>
		/// <returns></returns>
		winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;

	private:
		/// <summary>
		/// click次数计数器
		/// </summary>
		int32_t m_cnt{ 0 };

		/// <summary>
		/// 本单例实例的成员变量值变更通知事件
		/// </summary>
		winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::Bloom::Common::factory_implementation
{
	struct JDRGlobalXaml : JDRGlobalXamlT<JDRGlobalXaml, implementation::JDRGlobalXaml>
	{

	};
}
