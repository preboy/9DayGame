#include "stdafx.h"
#include "LibGraphics/stringFormat.h"
#include "LibGraphics/TextureFont.h"

namespace LibGraphics
{
    StringFormat::StringFormat()
    {

    }

    StringFormat::~StringFormat()
    {

    }

    void StringFormat::SetText(const char* lpText)
    {
        m_strText = lpText;
    }

    void StringFormat::AddText(const char* lpText)
    {
        m_strText.append(lpText);
    }

    void StringFormat::ClearText()
    {
        m_strText.clear();
    }

    const string& StringFormat::GetText()const
    {
        return m_strText;
    }

    string& StringFormat::GetText()
    {
        return m_strText;
    }

    void StringFormat::RenderText(TextPanel* textPanel)const
    {
        const char* lpText = m_strText.c_str();

        // "<color=0xaabbggrr>��ҩ<color=0xaabbggrr>��Ƥ<color=0xaabbggrr>��Ȼ��,�����е���Ʒ<Item={a=-23, b=23, b=23, name=����, }>"
        // �����顿

        textPanel->RenderString(m_strText.c_str(), nullptr);
    }


}
