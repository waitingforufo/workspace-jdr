#include "pch.h"
#include "JDRGlobal.h"

namespace winrt::JDRDemo::Common
{
	/// <summary>
	/// 获取JDRGlobal类实例的静态方法
	/// </summary>
	/// <returns></returns>
	JDRGlobal* JDRGlobal::GetInstance()
	{
		// 使用C++11的Magic Statics保证线程安全的懒汉式单例
		// 首次调用时自动实例化，应用退出时自动销毁
		static JDRGlobal singletonInstance;

		return &singletonInstance;
	}

}//end namespace