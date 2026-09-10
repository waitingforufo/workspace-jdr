#pragma once
#include "pch.h"
#include "Common.JDRGlobalXaml.g.h"  // MIDL生成，无需路径前缀(Generated Files已在包含路径中）

namespace winrt::Bloom::Common::implementation
{
	struct JDRGlobalXaml : JDRGlobalXamlT<JDRGlobalXaml>
	{
		JDRGlobalXaml() = default;

		// 单例访问
		static Bloom::Common::JDRGlobalXaml getInstance();

		// Cnt属性
		int32_t Cnt() const;
		void Cnt(int32_t value);

		// INotifyPropertyChanged实现
		winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;

	private:
		int32_t m_cnt{ 0 };

		winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::Bloom::Common::factory_implementation
{
	struct JDRGlobalXaml : JDRGlobalXamlT<JDRGlobalXaml, implementation::JDRGlobalXaml>
	{

	};
}
