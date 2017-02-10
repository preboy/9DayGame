#pragma once
#include <string>
using namespace std;

namespace LibEngine
{

    class TextPanel;

    // 带有格式的字符串， 多用于格式化的文本
    /*
    将<>之间的内容解析为设定的格式;
    键: 只能是以下几种情况，对应的键应该有对应格式的值，否则出错
    遇到错误是要报告的,
    如果原内容就是<>，则，需要在前面加上‘\’表示，如 \<这些东西是会显示出来的>

    <color=0xaabbggrr>
    <font=3>

    <color=0xaabbggrr font=3 fontSize=23>
    \<
    */
    class StringFormat
    {
    public:
        StringFormat();
       ~StringFormat();


       void                     SetText(const char* lpText);
       void                     AddText(const char* lpText);
       void                     ClearText();

       const string&            GetText()const;             
       string&                  GetText();

       void                     RenderText(TextPanel* textPanel)const;

    private:
       string                   m_strText;
    };
}
