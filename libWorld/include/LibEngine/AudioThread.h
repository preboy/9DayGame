#pragma once
#include "LibCore/thread_base.h"
using namespace LibCore;

#include <XAudio2.h>
#include <xaudio2fx.h>

namespace LibSound
{
    // ԭ����Xact3�����ˣ����Ի�XAudio2;


    // �Ӵ����ϼ���һ�����ļ��Ľṹ;
    class WaveFile
    {
    public:

        friend class AudioThread;

        WaveFile();
        ~WaveFile();

        bool Load();
        void UnLoad();
    };

    class AudioThread : public thread_base
    {
    public:
        AudioThread();
       ~AudioThread();

    protected:

        virtual bool        Run();
        virtual bool        OnThreadEnter();
        virtual void        OnThreadLeave();
    };

}