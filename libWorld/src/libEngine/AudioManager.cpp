#include "stdafx.h"
#include "LibEngine/AudioManager.h"

using namespace LibSound;

#include<stdio.h>

AudioManager::BackMusic::BackMusic()
{
    m_pSourceVoice          = nullptr;
    m_pfVoiceCallBack       = nullptr;
    m_pbWaveData            = nullptr;
    m_pbWMADecoder          = nullptr;
}

AudioManager::BackMusic::~BackMusic()
{
    Release();
}

bool AudioManager::BackMusic::Init()
{
    m_pfVoiceCallBack = new SXAudio2VoiceCallback;
    return true;
}

void AudioManager::BackMusic::Release()
{
    if(m_pSourceVoice)
    {
        m_pSourceVoice->Stop();
        m_pSourceVoice->DestroyVoice();
        m_pSourceVoice = nullptr;
    }

    SAFE_DELETE(m_pfVoiceCallBack);

    SAFE_FREE(m_pbWaveData);
    SAFE_FREE(m_pbWMADecoder);
}

bool AudioManager::BackMusic::PlayWaveFile(const char* pWaveFile, IXAudio2* pAudio2)
{
    if(m_pSourceVoice)
    {
        m_pSourceVoice->Stop();
        m_pSourceVoice->DestroyVoice();
        m_pSourceVoice = nullptr;
    }
    
    SAFE_FREE(m_pbWaveData);
    SAFE_FREE(m_pbWMADecoder);
    
    FILE* file = NULL;
    if(fopen_s(&file, pWaveFile, "rb"))
    {
        // file open failed.
        return false;
    }

    RIFF_HEADER        riff_header  = {0}; 
    FMT_BLOCK_HEADER   fmt_header   = {0};
    FMT_BLOCK          fmt_block    = {0}; 
    FACT_BLOCK         fact_block   = {0};
    DATA_BLOCK         data_block   = {0};
    DPDS_HEADER        dpds_header  = {0};

    // WAVE_HEADER waveHeader;
    size_t nlen = fread(&riff_header, 1, sizeof(RIFF_HEADER), file);
    if(nlen != sizeof(RIFF_HEADER) || _strnicmp(riff_header.RiffID, "RIFF", 4) != 0)
        return false;

    // 处理wav音频文件;
    if(_strnicmp(riff_header.RiffFormat, "WAVE", 4) == 0)
    {
        nlen = fread(&fmt_header, 1, sizeof(FMT_BLOCK_HEADER), file);
        if(nlen != sizeof(FMT_BLOCK_HEADER))
            return false;

        nlen = fread(&fmt_block, 1, fmt_header.FmtSize, file);
        if(nlen != fmt_header.FmtSize)
            return false;

        char szID[4] = {0};
        nlen = fread(&szID[0], 1, 4, file);
        if(nlen != 4)
            return false;

        fseek(file, -4, SEEK_CUR);

         if(_strnicmp(szID, "fact", 4) == 0)
         {
            nlen = fread(&fact_block, 1, sizeof(FACT_BLOCK), file);
            if(nlen != sizeof(FACT_BLOCK))
                return false;
         }

        nlen = fread(&data_block, 1, sizeof(DATA_BLOCK), file);
        if(nlen != sizeof(DATA_BLOCK))
            return false;
    }
    else if(_strnicmp(riff_header.RiffFormat, "XWMA", 4) == 0)
    {
        nlen = fread(&fmt_header, 1, sizeof(FMT_BLOCK_HEADER), file);
        if(nlen != sizeof(FMT_BLOCK_HEADER))
            return false;

        nlen = fread(&fmt_block, 1, fmt_header.FmtSize, file);
        if(nlen != fmt_header.FmtSize)
            return false;

        nlen = fread(&dpds_header, 1, sizeof(DPDS_HEADER), file);
        if(nlen != sizeof(DPDS_HEADER))
            return false;

        if(dpds_header.dpdsSize)
        {
            m_pbWMADecoder = (BYTE*)malloc(dpds_header.dpdsSize);
            if(!m_pbWMADecoder) 
                return false;
           
            nlen = fread(m_pbWMADecoder, 1, dpds_header.dpdsSize, file);
            if(nlen != dpds_header.dpdsSize)
                return false;
        }

        char szID[4] = {0};
        nlen = fread(&szID[0], 1, 4, file);
        if(nlen != 4)
            return false;

        fseek(file, -4, SEEK_CUR);

         if(_strnicmp(szID, "fact", 4) == 0)
         {
            nlen = fread(&fact_block, 1, sizeof(FACT_BLOCK), file);
            if(nlen != sizeof(FACT_BLOCK))
                return false;
         }

        nlen = fread(&data_block, 1, sizeof(DATA_BLOCK), file);
        if(nlen != sizeof(DATA_BLOCK))
            return false;
    }
    else
        return false;

    m_pbWaveData = (BYTE*)malloc(data_block.DataSize);
    fread(m_pbWaveData, 1, data_block.DataSize, file);
    
    XAUDIO2_BUFFER buffer   = {0};
    buffer.pAudioData       = m_pbWaveData;
    buffer.Flags            = XAUDIO2_END_OF_STREAM;
    buffer.AudioBytes       = data_block.DataSize;

    XAUDIO2_BUFFER_WMA wmaBuffer    = {0};
    wmaBuffer.PacketCount           = dpds_header.dpdsSize;
    wmaBuffer.pDecodedPacketCumulativeBytes = (UINT32*)m_pbWMADecoder;

    WAVEFORMATEX* pwfx = (WAVEFORMATEX*)((BYTE*)&fmt_block);

    HRESULT hr = pAudio2->CreateSourceVoice( &m_pSourceVoice, pwfx, 0,  XAUDIO2_DEFAULT_FREQ_RATIO, m_pfVoiceCallBack);
    if( FAILED(hr))
    {
        return false;
    }

    XAUDIO2_BUFFER_WMA* pWMABuffer = (m_pbWMADecoder ? &wmaBuffer : nullptr);

    if( FAILED(m_pSourceVoice->SubmitSourceBuffer( &buffer, pWMABuffer ) ) )
    {
        m_pSourceVoice->DestroyVoice();
        m_pSourceVoice = nullptr;
        SAFE_FREE(m_pbWaveData);
        SAFE_FREE(m_pbWMADecoder);
        return false;
    }

    fclose(file);
    m_pSourceVoice->Start(0);

    return true;
}

bool AudioManager::BackMusic::Pause(bool bPause)
{
    if(m_pSourceVoice)
    {
        // m_pSourceVoice->GetVolume();
    }

    return false;
}


//------------------------------------------------------------------------------------
void SXAudio2VoiceCallback::OnVoiceProcessingPassEnd()
{

}

void SXAudio2VoiceCallback::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{

}
void SXAudio2VoiceCallback::OnStreamEnd()
{
}

void SXAudio2VoiceCallback::OnBufferStart(void* pBufferContext)
{
}

void SXAudio2VoiceCallback::OnBufferEnd(void* pBufferContext)
{

}
void SXAudio2VoiceCallback::OnLoopEnd(void* pBufferContext)
{
}

void SXAudio2VoiceCallback::OnVoiceError(void* pBufferContext, HRESULT Error)
{
}


void SXAudio2EngineCallback::OnProcessingPassStart()
{
}

void SXAudio2EngineCallback::OnProcessingPassEnd()
{
}

void SXAudio2EngineCallback::OnCriticalError(HRESULT Error)
{
}


AudioManager::AudioManager()
{
    m_pAudio2               = nullptr;
    m_pMasterVoice          = nullptr;
    m_pfEngineCallBack      = nullptr;
}


AudioManager::~AudioManager()
{
    Release();
}

bool AudioManager::Init()
{
    if(!m_pAudio2)
    {
        if (FAILED(XAudio2Create( &m_pAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
            return false;

        if(FAILED(m_pAudio2->CreateMasteringVoice(&m_pMasterVoice)))
            return false;

        if(FAILED(m_pAudio2->StartEngine()))
            return false;

        m_pfEngineCallBack = reinterpret_cast<SXAudio2EngineCallback*>(new SXAudio2EngineCallback);
        if(FAILED(m_pAudio2->RegisterForCallbacks(m_pfEngineCallBack)))
            return false;

    }

    m_backMusic.Init();

    return true;
}

void AudioManager::Release()
{
    m_backMusic.Release();

    if(m_pMasterVoice)
    {
        m_pMasterVoice->DestroyVoice();
        m_pMasterVoice = nullptr;
    }

    if(m_pAudio2)
    {
        m_pAudio2->UnregisterForCallbacks(m_pfEngineCallBack);
        SAFE_DELETE(m_pfEngineCallBack);
        m_pAudio2->StopEngine();
        m_pAudio2->Release();
        m_pAudio2 = nullptr;
    }
}

bool AudioManager::PauseBackGroundMusic(bool pause)
{
    return m_backMusic.Pause(pause);
}

bool AudioManager::PlayBackGroundMusic(const char* pWaveFile)
{
    if(!pWaveFile) return false;
    return m_backMusic.PlayWaveFile(pWaveFile, m_pAudio2);
}
