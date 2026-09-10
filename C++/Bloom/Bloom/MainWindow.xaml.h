#pragma once
#include "pch.h"

#include "MainWindow.g.h"
#include "Common/JDRGlobalXaml.h"  // 包含单例头文件

namespace winrt::Bloom::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        /// <summary>
        /// 
        /// </summary>
        MainWindow();

        /// <summary>
        /// 供 {x:Bind} 使用的属性，返回全局单例(JDRGlobalXaml类型)
        /// </summary>
        /// <returns></returns>
        Bloom::Common::JDRGlobalXaml GlobalXaml() const;

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void myButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Bloom::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
