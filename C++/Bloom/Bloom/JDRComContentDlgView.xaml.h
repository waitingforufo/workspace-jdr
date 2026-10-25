#pragma once

#include "JDRComContentDlgView.g.h"

#include <vector>
using namespace std;

namespace winrt::Bloom::implementation
{
    struct JDRComContentDlgView : JDRComContentDlgViewT<JDRComContentDlgView>
    {
        /// <summary>
        /// 无参构造函数
        /// </summary>
        JDRComContentDlgView();

        /// <summary>
        /// 设定确认信息
        /// </summary>
        /// <param name="msg"></param>
        void SetMsg(winrt::hstring const& msg);

        /// <summary>
        /// 设定确认对话框项目
        /// </summary>
        /// <param name="items"></param>
        void SetItems(Windows::Foundation::Collections::IVector<
                          Bloom::JDRComContentDlgItem> const& items);

        /// <summary>
        /// 取得选择结果
        /// </summary>
        /// <returns></returns>
        Windows::Foundation::Collections::IVector<int32_t> GetSelection();

    private:
        // m_rows与传入的JDRComContentDlgItem列表严格一一对应，保证结果数组顺序一致：
        //     TextBlock = 普通文字行
        //     CheckBox = 复选框
        //     StackPanem = 一个RadioButton组
        std::vector<Microsoft::UI::Xaml::FrameworkElement> m_rows;
    };
}

namespace winrt::Bloom::factory_implementation
{
    struct JDRComContentDlgView : JDRComContentDlgViewT<JDRComContentDlgView, implementation::JDRComContentDlgView>
    {
    };
}
