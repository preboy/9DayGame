#pragma once
#include "LibCore/thread_base.h"
using namespace LibCore;

#include <XAudio2.h>
#include <xaudio2fx.h>

namespace LibSound
{
    // 原来的Xact3不行了，所以换XAudio2;


    // 从磁盘上加载一音乐文件的结构;
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