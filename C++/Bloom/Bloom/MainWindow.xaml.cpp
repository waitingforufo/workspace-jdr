#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "JDRCommonUtils/JDRWin32Util.h"

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

    void MainWindow::myButton_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                                    winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto jdrGlobalXaml = Bloom::Common::JDRGlobalXaml::getInstance();
        jdrGlobalXaml.Cnt(jdrGlobalXaml.Cnt() + 1);  // 修改属性，UI自动更新
    }
}
