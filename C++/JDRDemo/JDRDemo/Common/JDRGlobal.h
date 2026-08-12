#pragma once
#include "pch.h"

namespace winrt::JDRDemo::Common
{
	/// <summary>
	/// 应用全局共同类（单例模式 Singleton Pattern)
	/// ※将单例的生命周期与应用程序绑定，并暴露一个静态的获取方法 - GetInstance() 。
	/// 
	/// 使用方法：
	///   应用启动时(App.xaml.cpp#OnLaunched())，主动获取一次全局实例，完成全局初始化 
	///     JDRDemo::Common::JDRGlobal* pGlobal = JDRDemo::Common::JDRGlobal::GetInstance();
	///     pGlobal->SetGlobalSetting(100);  // 示例：初始化一些全局配置
	/// 
	/// 
	/// 
	/// 
	/// 
	/// </summary>
	class JDRGlobal
	{
	public:
		// 禁止拷贝和赋值
		JDRGlobal(const JDRGlobal&) = delete;
		JDRGlobal& operator=(const JDRGlobal&) = delete;

		/// <summary>
		/// 获取JDRGlobal类实例的静态方法
		/// </summary>
		/// <returns></returns>
		static JDRGlobal* GetInstance();

		// 示例：定义全局需要的成员或方法
		int GetGlobalSetting() const
		{
			return this->m_globalSetting;
		}

		void SetGlobalSetting(int val)
		{
			this->m_globalSetting = val;
		}

	private:
		// 私有构造函数，防止外部直接实例化
		JDRGlobal() = default;

		int m_globalSetting = 0;

	};

}// end namespace


