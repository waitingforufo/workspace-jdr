
■ JDRDemoWindow 的显示

// 1.聚合投影头文件
#include <winrt/Bloom.h>

// 2.调用 JDRDemoWindow (投影类型：winrt::Bloom::
winrt::Bloom::JDRDemoWindow demoWindow{ nullptr };
demoWindow = winrt::Bloom::JDRDemoWindow();

demoWindow.Activate();