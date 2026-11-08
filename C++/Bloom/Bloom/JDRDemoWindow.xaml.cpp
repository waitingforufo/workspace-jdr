#include "pch.h"
#include "JDRDemoWindow.xaml.h"
#if __has_include("JDRDemoWindow.g.cpp")
#include "JDRDemoWindow.g.cpp"
#endif <algorithim>  // std::min, std::max

#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.Windows.Storage.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>

#include <winrt/Microsoft.Graphics.Canvas.h>
#include <winrt/Microsoft.Graphics.Canvas.Effects.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>

#include <winrt/Windows.Foundation.Numerics.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

using namespace std;
namespace winrt::Bloom::implementation
{

	JDRDemoWindow::JDRDemoWindow()
	{
		InitializeComponent();
		
		// this是 JDRDemoWindow，它继承自 Microsoft::UI::Xaml::Window
		// AppWindow 常用能力清单（你后面图形 / 窗口控制会用到）
		//	窗口标题：Title()
		//	大小：Resize() / ResizeClient()
		//	位置：Move() / MoveAndResize()
		//	标题栏自定义：appWin.TitleBar()
		//	窗口置顶、Z 序、最小化、全屏、弹窗 Presenter 模式
		//	设置窗口图标、任务栏图标
		winrt::Microsoft::UI::Windowing::AppWindow appWin = this->AppWindow();

		if (appWin)
		{
			appWin.Title(L"Bloom - JDRDemo窗口");
			appWin.Resize({ 800,600 });
		}

		// 初始化 ColorMatrixEffect 为单位矩阵（原色）
		m_matrix = {
			1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 1, 0
		};

		//
		ScaleSlider().Value( 1.0 );
		ScaleText().Text(L"1.0x");
	}

	void JDRDemoWindow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, 
		                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	winrt::fire_and_forget JDRDemoWindow::OpenImgBtn_Click(winrt::Windows::Foundation::IInspectable const& sender,
		                                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

		winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker{ this->AppWindow().Id() };

		picker.FileTypeFilter().ReplaceAll({ L".png", L".jpg", L".jpeg", L".bmp" });

		auto result = co_await picker.PickSingleFileAsync();
		if (!result) co_return;  // 取消选择

		// 新版API返回的是路径字符串，通过路径打开文件流
		winrt::hstring filePath = result.Path();

		// 通过路径转换为 StorageFile,再打开为随机访问流
		//auto f = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(filePath);
		//auto stream = co_await f.OpenReadAsync();

		// 加载为 CanvasBitmap (需要 ICanvasResourceCreator,这里用 CanvasControl)
		m_bitmap = co_await winrt::Microsoft::Graphics::Canvas::CanvasBitmap::LoadAsync(CanvasCntrl(), filePath);

		// 请求重绘
		CanvasCntrl().Invalidate();

		// 在还没有 co_await 的时候，先加一句，强制编译器将此函数作为携程处理，消除编译错误。
		// 等有了 co_await 后，这一句不需要（ 其实就是 void 返回值的强制携程版。 等价 void 函数末尾的 return）
		co_return;
	}

	void JDRDemoWindow::CanvasCntrl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
		                                 winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
	{
		if (!m_bitmap) return;

		auto ds = args.DrawingSession();

		// 适配缩放
		float fitScale = (std::min)(
			static_cast<float>(sender.Size().Width) / static_cast<float>(m_bitmap.Size().Width),
			static_cast<float>(sender.Size().Height) / static_cast<float>(m_bitmap.Size().Height)
		);
		float effectiveScale = m_scale * fitScale;

		// 局部效果器，生命周期完全在 Draw 内
		winrt::Microsoft::Graphics::Canvas::Effects::ScaleEffect scaleEffect;
		scaleEffect.Source(m_bitmap);
		scaleEffect.Scale( winrt::Windows::Foundation::Numerics::float2(effectiveScale, effectiveScale));

		// 颜色效果，以缩放后的输入为输出
		winrt::Microsoft::Graphics::Canvas::Effects::ColorMatrixEffect colorEffect;
		colorEffect.Source(scaleEffect);
		colorEffect.Source(m_bitmap);

		// 计算居中偏移(现在必为非负）
		float sw = static_cast<float>(m_bitmap.Size().Width) * effectiveScale;
		float sh = static_cast<float>(m_bitmap.Size().Height) * effectiveScale;
		float offsetX = (static_cast<float>(sender.Size().Width) - sw) / 2.0f;
		float offsetY = (static_cast<float>(sender.Size().Height) - sh) / 2.0f;

		// 绘制最终效果
		ds.DrawImage(colorEffect, offsetX, offsetY);
		//ds.DrawImage(m_bitmap, offsetX, offsetY);
		//ds.DrawImage(m_bitmap, 0, 0);
		
		//ds.DrawImage(m_bitmap);

	}

	void JDRDemoWindow::ScaleSlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, 
		                                         winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
	{
		// 判空保护：XAML解析期间可能为 nullptr
		if (!ScaleText())
		{
			return;
		}

		m_scale = static_cast<float>(e.NewValue());

		//ScaleText().Text(winrt::to_hstring(m_scale) + L"x");
		
		//wchar_t buffer[32]{};
		//swprint_f( buffer, L"%.2fx", m_scale );
		//ScaleText().Text(buffer);

		winrt::hstring tmpStr = winrt::hstring{ std::format(L"{:.2f}x", m_scale) };  // c++20
		ScaleText().Text(tmpStr);

		if (CanvasCntrl())
		{
			CanvasCntrl().Invalidate();
		}
	}

	void JDRDemoWindow::ColorEffectBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, 
		                                     winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		m_colorMode = (m_colorMode + 1) % 3;
		switch (m_colorMode)
		{
		case 0:  // 原色（单位矩阵)
			m_matrix = {
				1, 0, 0, 0, 0,
				0, 1, 0, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 0, 1, 0
			};
			break;

		case 1:  // 灰度（RGB三个输出通道都取亮度加权和）
			m_matrix = {
				0.299f, 0.587f, 0.114f, 0, 0,
				0.299f, 0.587f, 0.114f, 0, 0,
				0.299f, 0.587f, 0.114f, 0, 0,
				0,      0,      0,      1, 0
			};
			break;

		case 2:  // 红色调（增强红色通道，削弱蓝色通道）
			m_matrix = {
				1.5f, 0,    0,    0, 0,
				0,    0.8f, 0,    0, 0,
				0,    0,    0.8f, 0, 0,
				0,    0,    0,    1, 0
			};
			break;
		}//end switch

		if (CanvasCntrl())
		{
			CanvasCntrl().Invalidate();
		}//end if
	}

}//end namespace
