#include "pch.h"

#include "JDRComContentDlgView.xaml.h"

#if __has_include("JDRComContentDlgView.g.cpp")
#include "JDRComContentDlgView.g.cpp"
#endif

#include <winrt/Microsoft.UI.Text.h>

namespace winrt::Bloom::implementation
{
	JDRComContentDlgView::JDRComContentDlgView()
	{
		InitializeComponent();
	}

	void JDRComContentDlgView::SetMsg(winrt::hstring const& msg)
	{
		MsgText().Text(msg);
	}

	void JDRComContentDlgView::SetItems(Windows::Foundation::Collections::IVector<
		                                    Bloom::JDRComContentDlgItem> const& items)
	{
		ItemsHost().Children().Clear();
		m_rows.clear();

		int groupIndex = 0;

		for(auto const& item : items)
		{
			switch (item.Type())
			{
			case Bloom::JDRComContentDlgItemType::Text:  // 普通文字信息
			{
				winrt::Microsoft::UI::Xaml::Controls::TextBlock tb;
				tb.Text(item.Text());
				tb.TextWrapping(winrt::Microsoft::UI::Xaml::TextWrapping::Wrap);

				ItemsHost().Children().Append(tb);  // 添加到显示树
				m_rows.push_back(tb);               // 控件保存，取得选中结果用
				break;
			}
			case Bloom::JDRComContentDlgItemType::CheckBox:  // 复选框
			{
				// 如果复选框数据不存在，什么也不生成
				if (item.List() && item.List().Size() == 0)
					break;

				winrt::Microsoft::UI::Xaml::Controls::CheckBox cb;

				// 从列表里选择第一个元素，用来生成CheckBox
				//if (item.List() && item.List().Size() > 0)
				//{
					auto tmp = item.List().GetAt(0);
					cb.Content(winrt::box_value(tmp.Text));  // struct成员直接用点访问，没有括号
					cb.IsChecked(tmp.IsChecked);
				//}

				ItemsHost().Children().Append(cb);
				m_rows.push_back(cb);
				break;
			}
			case Bloom::JDRComContentDlgItemType::RadioButtonGroup:  // 单选钮组
			{
				// 如果单选钮组数据不存在，什么也不生成
				if (item.List() && item.List().Size() == 0)
					break;

				winrt::Microsoft::UI::Xaml::Controls::StackPanel panel;
				panel.Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation::Vertical);
				panel.Spacing(4);

				// 生成点旋钮组标题
				winrt::Microsoft::UI::Xaml::Controls::TextBlock title;
				title.Text(item.Text());
				title.FontWeight(winrt::Microsoft::UI::Text::FontWeights::SemiBold());
				panel.Children().Append(title);

				// 生成单选钮组
				// 每组RadioButton用唯一GroupName：保证组内互斥，组与组之间互不影响
				winrt::hstring groupName = L"JDRRadioGroup" + winrt::to_hstring(groupIndex++);

				for (auto const& opt : item.List())
				{
					winrt::Microsoft::UI::Xaml::Controls::RadioButton rb;
					rb.Content(winrt::box_value(opt.Text));
					rb.IsChecked(opt.IsChecked);
					rb.GroupName(groupName);

					panel.Children().Append(rb);
				}

				ItemsHost().Children().Append(panel);
				m_rows.push_back(panel);
				break;
			}
			}//end switch
		}//end for

		return;
	}

	Windows::Foundation::Collections::IVector<int32_t> JDRComContentDlgView::GetSelection()
	{
		std::vector<int32_t> ret;
		ret.reserve(m_rows.size());  // 预留m_rows元素个的空间

		for (auto const& row : m_rows)
		{
			if (auto cb = row.try_as<winrt::Microsoft::UI::Xaml::Controls::CheckBox>())
			{
				// 复选框： 选中：1； 未选中：-1

				ret.push_back(cb.IsChecked().Value() ? 1 : -1);
			}
			else if (auto panel = row.try_as<winrt::Microsoft::UI::Xaml::Controls::Panel>())
			{
				// 单选组： 返回被选中的RadioButton索引值(0..N-1)，未选择为 -1

				int32_t selectedIdx = -1;
				auto children = panel.Children();

				for (uint32_t i = 0; i < children.Size(); i++)
				{
					if (auto rb = children.GetAt(i).try_as<winrt::Microsoft::UI::Xaml::Controls::RadioButton>())
					{
						if (rb.IsChecked().Value())
						{
							// 一组单选钮里只有一个选中，所以找到选中元素即停止查找
							selectedIdx = i;
							break;
						}
					}//end if
				}//end for

				ret.push_back(selectedIdx);
			}
			else
			{
				// 普通文字行

				ret.push_back(-1);
			}//end if
		}//end for

		return winrt::single_threaded_vector<int32_t>(std::move(ret));
	}

}//end namespace
