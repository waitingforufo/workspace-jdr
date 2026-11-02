# 在 MainWindow 的 XAML 中静态嵌入多个实例

### ■ 1/2 在 MainWindow.xaml 顶部声明 xmlns:local="using:Bloom"，然后在容器中直接放置多个 <local:JDRDemoUC />
```xml
<Window
    x:Class="Bloom.MainWindow"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:Bloom">

    <ScrollViewer>
        <StackPanel x:Name="UcContainer" Padding="20" Spacing="6">
            <!-- 静态嵌入 3 个实例演示 -->
            <local:JDRDemoUC />
            <local:JDRDemoUC />
            <local:JDRDemoUC />
        </StackPanel>
    </ScrollViewer>
</Window>
```  

### 在 XAML 中声明时，XAML 加载器会调用 JDRDemoUC 的默认构造函数（无参），因此 IDL 中必须提供 JDRDemoUC() 这样的无参构造函数。

### ■ 1/2  在 C++ 代码中动态创建 5 个 / 10 个实例
静态写法适合数量固定的场景；如果数量是运行时决定的（例如从配置读取、用户选择），就需要在 C++ 中动态创建。前提是容器（这里是 StackPanel）有一个 x:Name，本例中为 UcContainer。  

#### 1.头文件声明
在 MainWindow.xaml.h 的 MainWindow 结构体中增加初始化函数：

```cpp
// MainWindow.xaml.h
#pragma once
#include "MainWindow.g.h"

namespace winrt::Bloom::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void CreateJDRDemoUCs(int32_t count);
    };
}
```  

#### 2.C++实现
```cpp
// MainWindow.xaml.cpp
#include "pch.h"
#include "MainWindow.xaml.h"
//#include "JDRDemoUC.xaml.h"   // 必须包含，以使用 JDRDemoUC 类型

#include "winrt/Bloom.h"  // Bloom::xxx的投影类型头文件

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::Bloom::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        CreateJDRDemoUCs(5);   // 示例：嵌入 5 个；改成 10 就是 10 个
    }

    void MainWindow::CreateJDRDemoUCs(int32_t count)
    {
        // 清空已有子元素（防止重复调用造成叠加）
        UcContainer().Children().Clear();

        for (int32_t i = 0; i < count; ++i)
        {
            // 方式一：直接通过投影类型构造（推荐，走激活工厂）
            Bloom::JDRDemoUC uc;
            uc.SetInstanceId(i);
            UcContainer().Children().Append(uc);

            // 方式二（等价）：
            // auto impl = winrt::make<winrt::Bloom::implementation::JDRDemoUC>();
            // impl.SetInstanceId(i);
            // UcContainer().Children().Append(impl);
        }
    }
}
```  

#### 关键点：

Children() 返回 UIElementCollection，其类型是 Microsoft.UI.Xaml.Controls.UIElementCollection，Append(UIElement const&) 是标准方法。  

Children().Clear() 会释放集合内的所有引用，对应的 JDRDemoUC 实例会被 GC 回收（如果没有其他引用）。  

每次循环都调用 Bloom::JDRDemoUC uc; 生成一个独立实例，各自拥有自己的 XAML 子树和状态。  

SetInstanceId(i) 展示如何通过公开方法把循环索引注入到控件内部。  

如果需要在 XAML 中初始化完后再动态追加（例如按钮点击后添加更多），只需把 CreateJDRDemoUCs 改为 public 并在按钮 Click 里调用即可：  

```cpp
void MainWindow::OnAddMoreClick(
    IInspectable const&, RoutedEventArgs const&)
{
    for (int i = 0; i < 5; ++i)
    {
        Bloom::JDRDemoUC uc;
        uc.SetInstanceId(static_cast<int32_t>(UcContainer().Children().Size()));
        UcContainer().Children().Append(uc);
    }
}
```  


