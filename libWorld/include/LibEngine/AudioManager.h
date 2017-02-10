#pragma once

#include <xaudio2.h>
#include <xaudio2fx.h>

namespace LibSound
{

    //-------------------struct--------------------------------------------------
#pragma pack(push, 1)
    typedef struct _RIFF_HEADER 
    { 
        char        RiffID[4];  // 'R','I','F','F' 
        DWORD       RiffSize; 
        char        RiffFormat[4]; // 'W','A','V','E' 
    }RIFF_HEADER; 
#pragma pack(pop)

    #pragma pack(push, 1)
    typedef struct _FMT_BLOCK_HEADER
    { 
        char        FmtID[4]; // 'f','m','t',' ' 
        DWORD       FmtSize; 
    }FMT_BLOCK_HEADER;

#pragma pack(push, 1)
    typedef struct _FMT_BLOCK
    { 
        WORD        FormatTag; 
        WORD        Channels; 
        DWORD       SamplesPerSec; 
        DWORD       AvgBytesPerSec; 
        WORD        BlockAlign; 
        WORD        BitsPerSample; 
        WORD        cbSize;
    }FMT_BLOCK; 
#pragma pack(pop)

#pragma pack(push, 1)
    typedef  struct _FACT_BLOCK 
    { 
        char        FactID[4]; // 'f','a','c','t' 
        DWORD       FactSize; 
        DWORD       FactData; 
    }FACT_BLOCK; 
#pragma pack(pop)

#pragma pack(push, 1)
    typedef struct _DATA_BLOCK 
    { 
        char        DataID[4]; // 'd','a','t','a' 
        DWORD       DataSize; 
    }DATA_BLOCK; 
#pragma pack(pop)

#pragma pack(push, 1)
    typedef  struct _DPDS_HEADER
    { 
        char        dpdsID[4]; // 'f','a','c','t' 
        DWORD       dpdsSize; 
    }DPDS_HEADER; 
#pragma pack(pop)

#pragma pack(push, 1)
    typedef struct _WAVE_HEADER
    { 
        RIFF_HEADER        riff_header; 
        FMT_BLOCK          fmt_block; 
        FACT_BLOCK         fact_block; 
        DATA_BLOCK         data_block; 
    }WAVE_HEADER;          
#pragma pack(pop)

    //----------------------------interface-------------------------------------

    // 实现接口的回调函数;
    struct SXAudio2VoiceCallback : public IXAudio2VoiceCallback
    {
        virtual void WINAPI OnVoiceProcessingPassStart(UINT32 BytesRequired);
        virtual void WINAPI OnVoiceProcessingPassEnd();
        virtual void WINAPI OnStreamEnd();
        virtual void WINAPI OnBufferStart(void* pBufferContext);
        virtual void WINAPI OnBufferEnd  (void* pBufferContext);
        virtual void WINAPI OnLoopEnd    (void* pBufferContext);
        virtual void WINAPI OnVoiceError (void* pBufferContext, HRESULT Error);
    };

    struct SXAudio2EngineCallback : public IXAudio2EngineCallback
    {
        virtual void WINAPI OnProcessingPassStart();
        virtual void WINAPI OnProcessingPassEnd();
        virtual void WINAPI OnCriticalError(HRESULT Error);
    };


    //----------------------------class-------------------------------------

    class AudioManager
    {
        // 播放背景音乐;
        class BackMusic
        {
        public:
            BackMusic();
            ~BackMusic();

            bool  Init();
            void  Release();

            bool  PlayWaveFile(const char* pWaveFile, IXAudio2* pAudio2);

            bool  Pause(bool bPause);

            IXAudio2SourceVoice*        m_pSourceVoice;
            IXAudio2VoiceCallback*      m_pfVoiceCallBack;
            BYTE*                       m_pbWaveData;
            BYTE*                       m_pbWMADecoder;
        };

    public:
        AudioManager();
       ~AudioManager();
       
       bool     Init();
       void     Release();

       bool     PlayBackGroundMusic(const char* pWaveFile);
       bool     PauseBackGroundMusic(bool pause);

    private:
        IXAudio2*                   m_pAudio2;
        IXAudio2MasteringVoice*     m_pMasterVoice;
        IXAudio2EngineCallback*     m_pfEngineCallBack;

        BackMusic                   m_backMusic;
    };

}