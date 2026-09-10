#include "pch.h"
#include "JDRGlobalXaml.h"
#include "Common.JDRGlobalXaml.g.cpp"  // C++/WinRT要求包含生成的 .g.cpp以链接工厂实现

namespace winrt::Bloom::Common::implementation
{
	Bloom::Common::JDRGlobalXaml JDRGlobalXaml::getInstance()
	{
		// C++11起 static 局部变量初始化是线程安全的
		static Bloom::Common::JDRGlobalXaml instance{                   // 返回的是投影类型 Bloom::Commom::JDRGlobalXaml
			winrt::make<Bloom::Common::implementation::JDRGlobalXaml>()  // Bloom::Common::implementation下的实现类
		};
		return instance;
	}

	int32_t JDRGlobalXaml::Cnt() const
	{
		return m_cnt;
	}

	void JDRGlobalXaml::Cnt(int32_t value)
	{
		if (m_cnt != value)
		{
			m_cnt = value;
			
			// 触发书香变更通知，UI自动更新
			m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Cnt" });
		}
	}

	winrt::event_token JDRGlobalXaml::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void JDRGlobalXaml::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
}