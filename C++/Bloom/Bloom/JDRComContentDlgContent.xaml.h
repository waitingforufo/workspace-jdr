#pragma once

#include "JDRComContentDlgContent.g.h"

#include "JDRComContentDlgTypes.h"

namespace winrt::Bloom::implementation
{
    struct JDRComContentDlgContent : JDRComContentDlgContentT<JDRComContentDlgContent>
    {
        JDRComContentDlgContent() = default;

        void Initialize(std::wstring_view message, ::Bloom::JDRComContentDlgArgs const& args);

        Bloom::JDRComContentDlgResult CollectResult(
            winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult dialogResult);

    private:
        void appendTextLine(std::wstring const& text);
        void appendCheckBox(std::wstring const& text, bool isChecked);
        void appendRadioGroup(::Bloom::JDRComContentDlgItem const& group, int groupIndex);

        struct ItemRef {
            ::Bloom::JDRComContentDlgItemType Type{ ::Bloom::JDRComContentDlgItemType::Text };
            winrt::Microsoft::UI::Xaml::Controls::CheckBox CheckBox{ nullptr };
            std::vector<winrt::Microsoft::UI::Xaml::Controls::RadioButton> Radios;
        };

        std::vector<ItemRef> m_itemRefs;

    };
}//end namespace

namespace winrt::Bloom::factory_implementation
{
    struct JDRComContentDlgContent : JDRComContentDlgContentT<JDRComContentDlgContent, implementation::JDRComContentDlgContent>
    {
    };
}//end namespace
