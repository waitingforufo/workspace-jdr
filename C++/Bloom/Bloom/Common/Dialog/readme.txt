========================================================================
■ 通用确认对话框 Bloom::Common::Dialog::ComConfirmDlg

 按钮：
   Yes
   No
========================================================================

========================================================================
■ 通用确认对话框 Bloom::Common::Dialog::JDRComConfirmDlg
 按钮：
   Yes
   No
   Cancel

1. 命名空间：
     Bloom::Common::Dialog， 
     类名：JDRComConfirmDlg
2. 基类：   
     ContentDialog (WinUI3 C++/WinRT)
3. 基础功能：
     Title，提示文本，Yes/No/Cancel三个按钮
4. 动态加载多个 CheckBox 选项（调用方传入选项列表，对话框自动生成 CheckBox)
5. 返回：
     点击的按钮结果 + 用户勾选的复选框集合
6. 工程目录：
     Commom/Dialog/JDRComConfirmDlg.*

设计思路：
  · 定义一个简单模型类 JDRCheckItem，保存选项文本，是否勾选状态
  · JDRComConfirmDlg 对外接收 IVector<JDRCheckItem> 选项集合
  · XAML内部放 ItmsControl，动态渲染每一条 CheckBox
  · 弹出对话框前传入选项列表； 关闭后同时返回 【按钮结果】+【勾选项】
           
========================================================================
