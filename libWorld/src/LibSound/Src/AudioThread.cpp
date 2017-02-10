#include "stdafx.h"
#include "LibSound/AudioThread.h"

using namespace LibSound;

//-----------------------------------------------------------------------

WaveFile::WaveFile()
{

}

WaveFile::~WaveFile()
{

}

bool WaveFile::Load()
{
 return true;
}

void WaveFile::UnLoad()
{

}


//-----------------------------------------------------------------------
AudioThread::AudioThread()
{
}

AudioThread::~AudioThread()
{
}

bool AudioThread::Run()
{
    return true;
}

bool AudioThread::OnThreadEnter()
{
    return true;
}

void AudioThread::OnThreadLeave()
{
}

