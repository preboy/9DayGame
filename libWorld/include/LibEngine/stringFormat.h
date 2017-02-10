#pragma once
#include <string>
using namespace std;

namespace LibEngine
{

    class TextPanel;

    // ���и�ʽ���ַ����� �����ڸ�ʽ�����ı�
    /*
    ��<>֮������ݽ���Ϊ�趨�ĸ�ʽ;
    ��: ֻ�������¼����������Ӧ�ļ�Ӧ���ж�Ӧ��ʽ��ֵ���������
    ����������Ҫ�����,
    ���ԭ���ݾ���<>������Ҫ��ǰ����ϡ�\����ʾ���� \<��Щ�����ǻ���ʾ������>

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
