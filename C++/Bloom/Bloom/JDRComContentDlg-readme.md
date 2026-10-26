
#include <winrt/Bloom.h>

fire_and_forget MainWindow::myButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,                           
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

        // JDRComContentDlg调用示例 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        // 确认对话框显式项目列表
        auto items = winrt::single_threaded_vector<Bloom::JDRComContentDlgItem>();

        // 1.普通文字行
        auto tmpItem = Bloom::JDRComContentDlgItem();
        tmpItem.Type(Bloom::JDRComContentDlgItemType::Text);
        tmpItem.Text(L"请选择以下配置项：");

        items.Append(tmpItem);

        // 2.第一个ChecBox(默认选中)
        tmpItem = Bloom::JDRComContentDlgItem();
        tmpItem.Type(Bloom::JDRComContentDlgItemType::CheckBox);

        auto tmpOpt = Bloom::JDRComContentDlgItemOpt();
        tmpOpt.Text = L"开机自动启动";
        tmpOpt.IsChecked = true;

        auto tmpOptList = winrt::single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();
        tmpOptList.Append(tmpOpt);

        tmpItem.List(tmpOptList);
        items.Append(tmpItem);

        // 3.一个RadioButton组（3个选项，默认选中第一个(index=0))
        tmpItem = Bloom::JDRComContentDlgItem();
        tmpItem.Type(Bloom::JDRComContentDlgItemType::RadioButtonGroup);
        tmpItem.Text(L"下载路径");

        tmpOptList = winrt::single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();

        tmpOpt = Bloom::JDRComContentDlgItemOpt();
        tmpOpt.Text = L"默认路径";
        tmpOpt.IsChecked = true;
        tmpOptList.Append(tmpOpt);

        tmpOpt = Bloom::JDRComContentDlgItemOpt();
        tmpOpt.Text = L"自定义路径";
        tmpOpt.IsChecked = false;
        tmpOptList.Append(tmpOpt);

        tmpOpt = Bloom::JDRComContentDlgItemOpt();
        tmpOpt.Text = L"每次询问";
        tmpOpt.IsChecked = false;
        tmpOptList.Append(tmpOpt);

        tmpItem.List(tmpOptList);
        items.Append(tmpItem);

        // 4.第二个CheckBox（默认不选中）
        tmpItem = Bloom::JDRComContentDlgItem();
        tmpItem.Type(Bloom::JDRComContentDlgItemType::CheckBox);

        tmpOpt = Bloom::JDRComContentDlgItemOpt();
        tmpOpt.Text = L"完成后通知我";
        tmpOpt.IsChecked = false;

        tmpOptList = winrt::single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();
        tmpOptList.Append(tmpOpt);

        tmpItem.List(tmpOptList);
        items.Append(tmpItem);

        // XamlRoot取得
        auto xamlRoot = winrt::Microsoft::UI::Xaml::Window::Current().Content().XamlRoot();

        // 5.调用确认对话框
        auto result = co_await Bloom::JDRComContentDlg::ShowAsync(L"设置",
                                                                  L"请确认以下选项：",
                                                                  items,
                                                                  L"确定",
                                                                  L"取消",
                                                                  L"忽略",
                                                                  xamlRoot);

        // 6.解析结果（与传入items一一对应）
        // result.GetAt(0) == -1     -> 文字行，无意义
        // result.GetAt(1) == 1      -> 第一个CheckBox被选中（-1：未选中）
        // result.GetAt(2) == 0/1/2  -> RadioButton组中被选中项的索引(-1:未选中任何项）
        // result.GetAt(3) == -1     -> 第二个CheckBox未选中

        // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        co_return;

}










---------------------------------------------------------------------------------





[全局弹窗单例 - Kimi](https://www.kimi.com/chat/1a165fd5-6702-8a19-8000-09e56979d3e3?chat_enter_method=history)

调用示例
cpp
#include "pch.h"
#include "JDRComContentDlg.h"
#include "JDRComContentDlgItem.h"
#include <winrt/Windows.Foundation.Collections.h>

using namespace winrt;
using namespace Windows::Foundation::Collections;

winrt::fire_and_forget MainWindow::ShowTestDlg()
{
    // ---- 1. 普通文字行 ----
    auto rowText = Bloom::JDRComContentDlgItem();
    rowText.Type(Bloom::JDRComContentDlgItemType::String);
    rowText.Text(L"请选择以下配置项：");

    // ---- 2. 第一个 CheckBox（默认选中） ----
    Bloom::JDRComContentDlgItemOpt optCb1;
    optCb1.Text = L"开机自动启动";
    optCb1.IsChecked = true;

    auto cbList1 = single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();
    cbList1.Append(optCb1);

    auto itemCb1 = Bloom::JDRComContentDlgItem();
    itemCb1.Type(Bloom::JDRComContentDlgItemType::CheckBox);
    itemCb1.Text(L"开机自动启动");
    itemCb1.List(cbList1);

    // ---- 3. 一个 RadioButton 组（3 个选项，默认选中第 0 个） ----
    auto opts = single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();

    Bloom::JDRComContentDlgItemOpt optR0;
    optR0.Text = L"默认路径";   optR0.IsChecked = true;  opts.Append(optR0);

    Bloom::JDRComContentDlgItemOpt optR1;
    optR1.Text = L"自定义路径"; optR1.IsChecked = false; opts.Append(optR1);

    Bloom::JDRComContentDlgItemOpt optR2;
    optR2.Text = L"每次询问";   optR2.IsChecked = false; opts.Append(optR2);

    auto itemGroup = Bloom::JDRComContentDlgItem();
    itemGroup.Type(Bloom::JDRComContentDlgItemType::RadioButtonGroup);
    itemGroup.Text(L"下载路径");
    itemGroup.List(opts);

    // ---- 4. 第二个 CheckBox（默认不选中），顺序任意 ----
    Bloom::JDRComContentDlgItemOpt optCb2;
    optCb2.Text = L"完成后通知我";
    optCb2.IsChecked = false;

    auto cbList2 = single_threaded_vector<Bloom::JDRComContentDlgItemOpt>();
    cbList2.Append(optCb2);

    auto itemCb2 = Bloom::JDRComContentDlgItem();
    itemCb2.Type(Bloom::JDRComContentDlgItemType::CheckBox);
    itemCb2.Text(L"完成后通知我");
    itemCb2.List(cbList2);

    // ---- 5. 直接组 IVector ----
    auto items = single_threaded_vector<Bloom::JDRComContentDlgItem>();
    items.Append(rowText);
    items.Append(itemCb1);
    items.Append(itemGroup);
    items.Append(itemCb2);

    // ---- 6. 弹出 ----
    auto result = co_await Bloom::JDRComContentDlg::ShowAsync(
        L"设置", L"请确认以下选项：", items, L"确定", L"取消", L"忽略");

    // ---- 7. 解析结果（与传入 items 一一对应） ----
    // result.GetAt(0) == -1    -> 文字行，无意义
    // result.GetAt(1) == 1     -> 第一个 CheckBox 被选中（-1 表示未选中）
    // result.GetAt(2) == 0/1/2 -> RadioButton 组中被选中项的索引（-1 表示无选择）
    // result.GetAt(3) == -1    -> 第二个 CheckBox 未选中
}
经验总结（我记下了）：在 C++/WinRT XAML 工程里，只要 .idl 里声明了 runtimeclass，就必须提供对应的 factory_implementation 特化，与这个类有没有实例成员无关——因为激活工厂注册代码是 cppwinrt 自动生成、统一引用 factory_implementation::<类名> 的。静态类的差别只在于 implementation 侧是不继承基类的普通 struct，而不是 XXX : XXXT<XXX>。

