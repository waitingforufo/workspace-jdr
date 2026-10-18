#include "pch.h"

#include "JDRComContentDlgContent.xaml.h"

#if __has_include("JDRComContentDlgContent.g.cpp")
#include "JDRComContentDlgContent.g.cpp"
#endif

#include "JDRComContentDlgResult.h"

#include <utility>

#include <winrt/Microsoft.UI.Text.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::Bloom::implementation
{
    void JDRComContentDlgContent::Initialize(std::wstring_view message, ::Bloom::JDRComContentDlgArgs const& args)
    {
        MessageText().Text(winrt::hstring{ message });

        auto host = ItemHost();
        host.Children().Clear();

        this->m_itemRefs.clear();
        this->m_itemRefs.reserve(args.Items.size());

        int radioGrpIdx = 0;
        for (auto const& item : args.Items)
        {
            switch (item.Type)
            {
            case ::Bloom::JDRComContentDlgItemType::Text:
                appendTextLine(item.Text);
                break;

            case ::Bloom::JDRComContentDlgItemType::CheckBox:
                appendCheckBox(item.Text, item.IsChecked);
                break;

            case ::Bloom::JDRComContentDlgItemType::RadioGroup:
                appendRadioGroup(item, radioGrpIdx++);
                break;

            default:
                this->m_itemRefs.push_back(ItemRef{});  // 占位，保证索引对齐
                break;
            }
        }//end for
    }

    Bloom::JDRComContentDlgResult JDRComContentDlgContent::CollectResult(
        winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult dialogResult)
    {
        //1. 用runtimeclass投影创建结果对象
        auto rst = winrt::make<winrt::Bloom::implementation::JDRComContentDlgResult>();
        rst.DialogResult(dialogResult);

        //2. 动态构建Status(长度=m_itemRefs.size())
        std::vector<int32_t> status;
        status.reserve(m_itemRefs.size());

        for (auto const& ref : m_itemRefs)
        {
            switch (ref.Type)
            {
            case ::Bloom::JDRComContentDlgItemType::Text:
                status.push_back(-1);
                break;

            case ::Bloom::JDRComContentDlgItemType::CheckBox:
            {
                auto isChecked = ref.CheckBox.IsChecked();
                status.push_back(((isChecked != nullptr) && isChecked.GetBoolean()) ? 1 : -1);
                break;
            }

            case ::Bloom::JDRComContentDlgItemType::RadioGroup:
            {
                int32_t selected = -1;
                for (size_t i = 0; i < ref.Radios.size(); ++i)
                {
                    auto v = ref.Radios[i].IsChecked();
                    if ((v != nullptr) && v.GetBoolean())
                    {
                        selected = static_cast<int32_t>(i);
                        break;
                    }//end if
                }//end for

                status.push_back(selected);
                break;
            }

            default:
                status.push_back(-1);
                break;
            }//end switch
        }//end for

        // 3. 转为IVector赋给runtimeclass属性（长度动态）
        rst.Status(winrt::single_threaded_observable_vector<int32_t>(std::move(status)));
        return rst;
    }

    void JDRComContentDlgContent::appendTextLine(std::wstring const& text)
    {
        winrt::Microsoft::UI::Xaml::Controls::TextBlock tb;
        tb.Text(winrt::hstring{ text });
        tb.TextWrapping(TextWrapping::Wrap);
        ItemHost().Children().Append(tb);

        ItemRef ref;
        ref.Type = ::Bloom::JDRComContentDlgItemType::Text;
        m_itemRefs.push_back(std::move(ref));
    }

    void JDRComContentDlgContent::appendCheckBox(std::wstring const& text, bool isChecked)
    {
        Controls::CheckBox cb;
        cb.Content(box_value(hstring{ text }));
        cb.IsChecked(isChecked);
        ItemHost().Children().Append(cb);

        ItemRef ref;
        ref.Type = ::Bloom::JDRComContentDlgItemType::CheckBox;
        ref.CheckBox = cb;
        m_itemRefs.push_back(std::move(ref));
    }

    void JDRComContentDlgContent::appendRadioGroup(::Bloom::JDRComContentDlgItem const& group, int groupIndex)
    {
        auto grpName = hstring{L"JDRRadioGrp_" + std::to_wstring(groupIndex)};

        Controls::StackPanel panel;
        panel.Spacing(4);

        if (!group.Text.empty())
        {
            Controls::TextBlock header;
            header.Text(hstring{ group.Text });
            header.FontWeight(winrt::Microsoft::UI::Text::FontWeights::SemiBold());
            header.Margin({ 0,4,0,2 });
            panel.Children().Append(header);
        }

        ItemRef ref;
        ref.Type = ::Bloom::JDRComContentDlgItemType::RadioGroup;
        ref.Radios.reserve(group.Children.size());

        for (auto const& child : group.Children)
        {
            Controls::RadioButton rb;
            rb.Content(box_value(hstring{ child.Text }));
            rb.GroupName(grpName);
            rb.IsChecked(child.IsChecked);
            panel.Children().Append(rb);

            ref.Radios.push_back(rb);
        }//end for

        ItemHost().Children().Append(panel);
        m_itemRefs.push_back(std::move(ref));
    }

}//end namespace
