#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include "Common/JDRGlobal.h"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Bloom::implementation
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        // 应用启动时，主动获取一次全局实例，完成全局初始化
        //JDRDemo::Common::JDRGlobal* pGlobal = JDRDemo::Common::JDRGlobal::GetInstance();  // 有的是winrt::JDRDemo，有的是 ::JDRDemo。 只有JDRDemo::xxx 啥也找不到
        ::Bloom::Common::JDRGlobal* pGlobal = ::Bloom::Common::JDRGlobal::GetInstance();
        pGlobal->SetGlobalSetting(100);  // 示例：初始化一些全局配置

        // 创建并激活主窗口MainWindow.xaml
        window = make<MainWindow>();
        window.Activate();
    }
}
