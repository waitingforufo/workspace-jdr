#pragma once

#include "JDRDemoWindow.g.h"

namespace winrt::Bloom::implementation
{
    struct JDRDemoWindow : JDRDemoWindowT<JDRDemoWindow>
    {
        JDRDemoWindow();

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Bloom::factory_implementation
{
    struct JDRDemoWindow : JDRDemoWindowT<JDRDemoWindow, implementation::JDRDemoWindow>
    {
    };
}
