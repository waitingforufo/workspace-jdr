#pragma once

#include "JDRDemoUC.g.h"

namespace winrt::Bloom::implementation
{
    struct JDRDemoUC : JDRDemoUCT<JDRDemoUC>
    {
        JDRDemoUC();

        /// <summary>
        /// 供外部设置实例编号
        /// </summary>
        /// <param name="id"></param>
        void SetInstanceId(int32_t id);

        /// <summary>
        /// 按钮点击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void ActionButton_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                                winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };

}//end namespace

namespace winrt::Bloom::factory_implementation
{
    struct JDRDemoUC : JDRDemoUCT<JDRDemoUC, implementation::JDRDemoUC>
    {
    };

}//end namespace
