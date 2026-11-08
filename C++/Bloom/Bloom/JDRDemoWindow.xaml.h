#pragma once

#include "JDRDemoWindow.g.h"

namespace winrt::Bloom::implementation
{
    struct JDRDemoWindow : JDRDemoWindowT<JDRDemoWindow>
    {
        JDRDemoWindow();

        /// <summary>
        /// 关闭窗口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                          winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// <summary>
        /// 打开本地图片文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// <returns>
        ///   winrt::fire_and_forget : 意味着是携程函数，函数体内必须有 co_await 或 co_return。
        ///                            ✳只要函数体中出现了 co_await， 编译器就会正确的识别为 携程函数。 
        /// 
        ///       ■ 如果函数体中确实不需要 co_await ， 那么它本身就是一个同步函数，完全不需要使用 fire_and_forget。 将返回类型改回 void 即可。
        ///       ■ 如果希望保留 fire_and_forget 的声明形式，但函数体中暂时还没有 co_await，可以在函数末尾显式加一句 co_return，强制编译器将其视为携程。
        /// </returns>
        winrt::fire_and_forget OpenImgBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                                                winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// <summary>
        /// 画图
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        void CanvasCntrl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
                              winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args);

        /// <summary>
        /// slider值变换
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void ScaleSlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, 
                                      winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);

        /// <summary>
        /// 切换颜色效果
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void ColorEffectBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        // Win2D 位图资源
        winrt::Microsoft::Graphics::Canvas::CanvasBitmap m_bitmap{ nullptr };

        // 颜色矩阵效果（复用同一个实例，就修改矩阵）
        //winrt::Microsoft::Graphics::Canvas::Effects::ColorMatrixEffect m_colorEffect{ nullptr };
        winrt::Microsoft::Graphics::Canvas::Effects::Matrix5x4 m_matrix{
            1,0,0,0,0,
            0,1,0,0,0,
            0,0,1,0,0,
            0,0,0,1,0
        };

        // 状态
        float m_scale{ 1.0f };

        // 0:原色; 1:灰度；2:红色调
        int m_colorMode{ 0 };
    };
}

namespace winrt::Bloom::factory_implementation
{
    struct JDRDemoWindow : JDRDemoWindowT<JDRDemoWindow, implementation::JDRDemoWindow>
    {
    };
}
