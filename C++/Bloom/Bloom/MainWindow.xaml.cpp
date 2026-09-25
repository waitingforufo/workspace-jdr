#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "JDRCommonUtils/JDRWin32Util.h"
#include "Common/Dialog/ComConfirmDlg.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Bloom::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();  // 初始化XAML控件

        ::Bloom::JDRCommonUtils::JDRWin32Util::SetStartupPlacement( *this, 240, 160, 600, 400);
    }

    /// <summary>
    /// 供 {x:Bind} 使用的属性，返回全局单例(JDRGlobalXaml类型)
    /// </summary>
    /// <returns></returns>
    Bloom::Common::JDRGlobalXaml MainWindow::GlobalXaml() const
    {
        return Bloom::Common::JDRGlobalXaml::getInstance();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    fire_and_forget MainWindow::myButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,                           
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto jdrGlobalXaml = Bloom::Common::JDRGlobalXaml::getInstance();
        jdrGlobalXaml.Cnt(jdrGlobalXaml.Cnt() + 1);  // 修改属性，UI自动更新

        // 取得APP级别资源
        auto appResources = winrt::Microsoft::UI::Xaml::Application::Current().Resources();

        // x:Double -> double
        winrt::Windows::Foundation::IInspectable sizeObj = appResources.Lookup(winrt::box_value(L"BloomBodyFontSize"));
        double bodyFontSize = winrt::unbox_value<double>(sizeObj);

        // SolidColorBrush
        auto brushObj = appResources.Lookup(winrt::box_value(L"BloomPrimaryBrush"));
        auto primaryBrush = brushObj.as<winrt::Microsoft::UI::Xaml::Media::SolidColorBrush>();

        // 向上查找资源例子
        auto resObj = ::Bloom::JDRCommonUtils::JDRWin32Util::TryFindResource(myButton(), L"MainWindowCardPadding");
        if (resObj)
        {
            auto padding = winrt::unbox_value<winrt::Microsoft::UI::Xaml::Thickness>(resObj);
        }

        bool rst = false;

        // 调用全局确认对话框
        // 注意：调用方函数必须是 co_await 异步函数，或者使用 fire_and_forget
        bool confirmed = co_await ::Bloom::Common::Dialog::ComConfirmDlg::ShowAsync(
            RootStackPanel().XamlRoot(),              // 传入当前页面的 XamlRoot
            L"确认",                                  // 标题
            L"确认要进行此操作吗（数据可能无法回复）？"    // 内容
        );

        if (confirmed)
        {
            // 点击 Yes
            rst = true;
        }
        else
        {
            // 点击 No
            rst = false;
        }
    }
}
