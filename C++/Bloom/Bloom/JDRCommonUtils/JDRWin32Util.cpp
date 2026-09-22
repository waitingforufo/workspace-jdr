#include "pch.h"  // 必须包含！ 且必须是第一行！！ 绝对不可省略或挪动位置
///
/// C++开发中，永远不要依赖头文件来间接传递预编译头。把 #include "pch.h"放在每一个 .cpp文件的最顶端，是C++/WinRT开发中不可打破的铁律。
/// 

// 以下包含 1.自己的头文件； 2.其他工具类头文件
#include "JDRWin32Util.h"

#include <microsoft.ui.xaml.window.h>  // IWindowNative接口定义
#include <ShObjIdl.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>

namespace Bloom::JDRCommonUtils
{
	HWND JDRWin32Util::GetWindowHwnd(winrt::Microsoft::UI::Xaml::Window const& window)
	{
		//将Window对象查询为IWindowNative接口
		auto windowNative{ window.as<::IWindowNative>() };

		HWND hWnd{ nullptr };
		windowNative->get_WindowHandle(&hWnd);

		return hWnd;
	}

	void JDRWin32Util::SetStartupPlacement(
		winrt::Microsoft::UI::Xaml::Window const& window,
		int32_t posX,
		int32_t posY,
		int32_t width,
		int32_t height)
	{
		HWND hWnd{};
		hWnd = GetWindowHwnd(window);

		auto windowId = winrt::Microsoft::UI::GetWindowIdFromWindow(hWnd);
		auto appWindow = winrt::Microsoft::UI::Windowing::AppWindow::GetFromWindowId(windowId);

		winrt::Windows::Graphics::PointInt32 pos{ posX, posY };
		
		winrt::Windows::Graphics::SizeInt32 size{ width, height };

		appWindow.Move(pos);
		appWindow.Resize(size);

		return;
	}

	winrt::Windows::Foundation::IInspectable JDRWin32Util::TryFindResource(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& startElement,
		winrt::hstring const& resourceKey)
	{
		auto current = startElement;

		while (current)
		{
			auto dict = current.Resources();
			if (dict.HasKey(winrt::box_value(resourceKey)))
			{
				return dict.Lookup(winrt::box_value(resourceKey));
			}//end if

			// 当前元素里没有指定资源
			auto parent = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetParent(current);
			current = parent ? parent.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>() : nullptr;
		}//end while

		// 从当前元素向上查找都无的时候
		// 查找App级别资源

		auto appDict = winrt::Microsoft::UI::Xaml::Application::Current().Resources();
		if (appDict.HasKey(winrt::box_value(resourceKey)))
		{
			return appDict.Lookup(winrt::box_value(resourceKey));
		}//end if

		return nullptr;
	}

}//end namespace