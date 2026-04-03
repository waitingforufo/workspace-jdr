#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

//::IWindowNativeと::IInitializeWithWindowを使うのにmicrosoft.ui.xaml.window.h、Shobjidl.hが必要
//MessageDialogを使うのにWindows.UI.Popups.hが必要
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.UI.Popups.h>
#include <Shobjidl.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PicViewer::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    HWND MainWindow::getHwnd() {
        auto windowNative{ this->m_inner.as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);

        return hWnd;
    }

    void MainWindow::Open_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        //ContentDialogはwinrt::Microsoft...となる。必要なのはXamlRoot
        Microsoft::UI::Xaml::Controls::ContentDialog isenddialog{};
        isenddialog.XamlRoot(this->Content().XamlRoot());
        isenddialog.Title(box_value(L"Do you want to close?"));
        isenddialog.PrimaryButtonText(L"Yes");
        isenddialog.SecondaryButtonText(L"No");
        isenddialog.CloseButtonText(L"Cancel");

        auto result = co_await isenddialog.ShowAsync();

        if (result == Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary)
        {
            //アプリ終了
            Application::Current().Exit();
        }
        else if (result == Microsoft::UI::Xaml::Controls::ContentDialogResult::Secondary)
        {
            //MessageDialogはwinrt::Windows...となる。必要なのはHWND
            auto showdialog{ Windows::UI::Popups::MessageDialog(L"Continue without closing this application") };
            showdialog.as<::IInitializeWithWindow>()->Initialize(getHwnd());

            co_await showdialog.ShowAsync();
        }
    }

}//end namespace




