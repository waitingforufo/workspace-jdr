# 一、什么是 IDL（MIDL3.0，WinRT IDL，C++/WinRT/WinUI3 使用）

`.idl` = **Microsoft Interface Definition Language，MIDL3.0**（现代简化版，不是老 COM 的 MIDL2）。

> 
> 作用：**语言中立的元数据描述文件，用来定义 WinRT 类型（runtimeclass、interface、struct、enum、delegate）**。
> 它不是 C++ 代码，**不写业务逻辑，只定义 API 契约**。
> 编译：`midl.exe` 读取`.idl`，输出 **`.winmd`（Windows Runtime Metadata，winmd 元数据）**。
> winmd 是核心：Xaml 编译器、x:Bind、cppwinrt.exe 全部依赖这个元数据。

> 
> 重点区分：
> 
> 
> - **runtimeclass**：引用类型（COM 对象，有引用计数，适合 x:Bind，支持属性变更通知，你前面一直在用）
> - **idl struct**：值类型（值拷贝，**没有 INotifyPropertyChanged，不能直接用 x:Bind 访问内部字段**，这就是你之前的疑问！）

# 二、整体文件结构

```
// 单行注释
/* 块注释 */
import "Other.idl"; // 导入其他idl文件，引用别的idl里定义的类型

namespace WinUi3Demo // WinRT元数据命名空间，非常关键
{
    // 特性 [xxx] 写在类型前面
    [特性]
    runtimeclass 类名 : 基类.接口
    {
        // 构造函数
        类名();
        类名(String name);

        // 属性
        String Name;          // 读写属性 get+set
        Int32 Age{ get; };    // 只读属性，只有getter

        // 静态属性
        static Int32 Count{ get; }

        // 方法
        void SayHello(String msg);

        // 事件
        event Windows.Foundation.EventHandler<String> MessageArrived;
    }

    // idl 结构体（值类型）
    struct MyPoint
    {
        Double X;
        Double Y;
    }

    // 枚举
    enum ColorType : Int32
    {
        Red = 1,
        Green = 2
    }

    // 接口
    interface IMyInterface
    {
        void DoWork();
    }

    // 委托（事件回调原型）
    delegate void MyCallback(Int32 value);
}
```

# 三、关键字详解 + 语法规则（MIDL3.0）

## 1. `import` 导入

作用：引入别的`.idl`，使用里面定义的类型。**不是 C++ #include，是元数据导入**。

```
import "DataPos.idl"; // 导入同目录下另一个idl，这样本文件可以使用DataPos
```

> 
> 你前面嵌套结构体例子：DataItem.idl 需要 import "DataPos.idl"; 才能写 `DataPos Pos;`

## 2. `namespace` 命名空间

```
namespace WinUi3Demo
{
}
```

✅ 这个就是**WinRT 元数据命名空间**，写入 winmd。

- XAML 里 `x:Class="WinUi3Demo.MainWindow"` 用的就是这个命名空间
- C++ 侧自动生成 `winrt::WinUi3Demo::implementation`

> 
> 命名空间可以多级：`namespace WinUi3Demo.SubNS`

## 3. `runtimeclass`（你最常用！WinUI3 界面绑定全部靠它）

```
[bindable]
runtimeclass DataItem
{
    DataItem();
    String Name;
    Int32 Age;
    WinUi3Demo.DataPos Pos;
}
```

语法：

```
[特性列表]
runtimeclass 名称 : 基类, IInterface1, IInterface2
{
    // 成员：构造函数、属性、静态属性、方法、事件
}
```

### 重要特性（attribute，放在 [] 里）

1. `[bindable]`：**x:Bind 必须！**
自动生成 `INotifyPropertyChanged`，属性变更可以触发 UI 刷新。**没有 [bindable]，x:Bind 虽然能编译，但属性变化不会自动通知 UI**。
2. `[default_interface]`：常用，标记默认接口。
3. `[activatable(1.0)]`：允许外部激活实例（普通 WinUI 窗口一般不需要手动写，写无参构造函数自动生成）

> 
> 继承示例（WinUI3 窗口 / 页面）

```
runtimeclass MainWindow : Microsoft.UI.Xaml.Window
{
    MainWindow();
    Windows.Foundation.Collections.IObservableVector<DataItem> ItemList{get;};
}
```

`Microsoft.UI.Xaml.Window` 是 WinUI3 内置 runtimeclass。

### runtimeclass 内部成员

#### ① 构造函数

```
DataItem(); // 无参构造
DataItem(String name, Int32 age); // 带参数构造
```

> 
> 在 idl 写构造函数，代表允许外部激活这个 runtimeclass。

#### ② 属性 Property（重点，x:Bind 绑定的就是这个）

```
String Name;                // 读写：get + set
Int32 Age{ get; };          // 只读，只有getter，不能set
static Int32 TotalCount{ get; }; // 静态只读属性
```

规则：

- 每个属性，midl 会生成 getter/setter；你在 implementation 的 h/cpp 里面实现。
- `[bindable]` 类，你在 setter 里调用`RaisePropertyChanged(L"属性名")`，触发 INotifyPropertyChanged。

#### ③ 方法 Method

```
void DoSomething(String param);
Boolean CheckValue(Int32 val);
```

返回值在前，参数列表，参数**不需要写 in/out**（MIDL3 简化了）。

#### ④ 事件 event

```
event Windows.Foundation.EventHandler<String> OnMessage;
```

事件类型是委托。Win 内置：`Windows.Foundation.EventHandler<T>`。

## 4. `struct`（idl 的值结构体，⚠️重点坑）

```
struct Point
{
    Double X;
    Double Y;
}
```

- idl 的`struct`：**值类型，栈拷贝，不是 COM 对象，没有 INotifyPropertyChanged**
- ❗**x:Bind 不能直接访问 struct 内部字段！** 这就是你之前问的核心：

> 
> 如果属性返回的是 idl struct `Point Pos;`，你写`{x:Bind Item.Pos.X}` → **Xaml 编译报错！**
> 因为 struct 不是 runtimeclass，没有属性 getter，只有字段；x:Bind 编译期只认 runtimeclass 的属性。
> 
> 
> > 
> > idl struct 只能整体赋值，不能在 x:Bind 链式访问内部成员。

> 
> idl struct 字段只能是基础类型、enum、其他 idl struct、String、IReference<T>。**不能放 runtimeclass**。

## 5. `enum` 枚举

```
enum MyEnum : Int32
{
    None = 0,
    Start = 1,
    Stop = 2
}
```

底层基础类型可选：`Int32` / `UInt32`。

## 6. `interface` WinRT 接口

```
interface IMyService
{
    void Run();
    String GetName();
}
```

接口里放方法、属性，**不能有构造函数、事件**。runtimeclass 可以继承（实现）多个 interface。

## 7. `delegate` 委托（事件回调函数原型）

```
delegate void MyDelegate(Int32 code, String msg);
```

事件 event 后面的类型就是委托。

# 四、内置基础类型（idl 直接可用）

表格

| idl 类型 | 说明 | C++/WinRT 映射 |
| --- | --- | --- |
| Boolean | 布尔 | bool |
| Int16 / Int32 / Int64 | 有符号整型 | int16_t, int32_t, int64_t |
| UInt8 / UInt16 / UInt32 / UInt64 | 无符号 | uint8_t ... |
| Single | float 32 位 | float |
| Double | double 64 位 | double |
| String | UTF16 字符串 | winrt::hstring |
| Object | IInspectable*，所有 WinRT 对象基类 | winrt::Windows::Foundation::IInspectable |
| Char16 | UTF16 字符 | wchar_t |
| Guid | GUID | winrt::guid |

## 泛型接口（idl 写法，集合你一直在用）

WinRT 泛型接口写法：`命名空间.接口<类型>`

```
// 可观察向量，用于x:Bind列表
Windows.Foundation.Collections.IObservableVector<WinUi3Demo.DataItem> ItemList{ get; };
```

常用：

- `IObservableVector<T>`：可观察动态数组（推荐 ItemsControl 绑定）
- `IVector<T>`：普通数组
- `IVectorView<T>`：只读视图

# 五、完整可编译综合示例（对应你前面嵌套 DataPos+DataItem 场景）

### DataPos.idl

```
namespace WinUi3Demo
{
    [bindable]
    runtimeclass DataPos
    {
        DataPos();
        Double X;
        Double Y;
    }
}
```

### DataItem.idl

```
import "DataPos.idl"; // 导入DataPos的元数据

namespace WinUi3Demo
{
    [bindable]
    runtimeclass DataItem
    {
        DataItem();
        String Name;
        Int32 Age;
        WinUi3Demo.DataPos Pos; // 嵌套runtimeclass，x:Bind可以链式访问 Pos.X Pos.Y
    }
}
```

### MainWindow.idl

```
import "DataItem.idl";

namespace WinUi3Demo
{
    runtimeclass MainWindow : Microsoft.UI.Xaml.Window
    {
        MainWindow();
        Windows.Foundation.Collections.IObservableVector<WinUi3Demo.DataItem> ItemList{ get; };
    }
}
```

# 六、idl 编译流程（和你前面的编译链串起来）

1. 项目所有`.idl`交给`midl.exe`（MIDL3 编译器）
2. midl 校验 idl 语法，生成**winmd 元数据文件**
3. 生成 C++ 存根代码（obj/Generated Files 里面的`.g.h`/`.g.cpp`）
4. winmd 提供类型元数据 → **XamlCompiler 编译 xaml、校验 x:Bind**
5. cppwinrt.exe 读取 winmd，生成 winrt 投影头文件（`winrt/WinUi3Demo.h`）
6. 你手写的`xxx.h/xxx.cpp`实现`winrt::WinUi3Demo::implementation::XXX`结构体

# 七、高频坑（WinUI3 C++/WinRT idl）

1. **idl struct ≠ runtimeclass**
struct 是值类型，**x:Bind 不能访问 struct 内部字段**；如果你要写`{x:Bind Item.Pos.X}`，Pos 必须是 runtimeclass，不是 idl struct。
2. 忘记`import "xxx.idl"`：引用别的 idl 里的 runtimeclass，不 import，midl 报找不到类型。
3. `[bindable]`漏写：x:Bind 能读初始值，但是属性修改后 UI 不会自动刷新（没有 INotifyPropertyChanged）。
4. 命名空间不一致：idl 的 namespace 必须和 C++ `winrt::XXX::implementation`中间段完全一致。
5. idl 里面**不能写普通 C++ struct**，idl 只认 idl 自己的`struct`关键字。
6. 泛型 IObservableVector<T>，T 必须是 winmd 里面存在的 runtimeclass 类型。

# 八、idl runtimeclass 和 idl struct 一句话对比

- `runtimeclass`：引用对象，COM，可`[bindable]`，支持 INotifyPropertyChanged，**x:Bind 支持链式访问属性**，适合 ViewModel、列表数据项。
- `struct`：值类型，拷贝传递，**没有属性变更通知，x:Bind 不能访问内部字段**，适合坐标、颜色这种纯静态小数据。