#include "stdafx.h"
#include "LibWindows/SRWLock.h"

using namespace LibWindows;

SRWLock::SRWLock()
{
    InitializeSRWLock(&m_lock);
}


SRWLock::~SRWLock()
{

}

void SRWLock::AcquireShared()
{
    AcquireSRWLockShared(&m_lock);
}

void SRWLock::ReleaseShared()
{
    ReleaseSRWLockShared(&m_lock);
}

void SRWLock::AcquireExclusive()
{
    AcquireSRWLockExclusive(&m_lock);
}

void SRWLock::ReleaseExclusive()
{
    ReleaseSRWLockExclusive(&m_lock);
}

//////////////////////////////////////////////////////////////////////////

SRWLock_share::SRWLock_share(SRWLock& lock_) : m_lockShared(lock_)
{
    m_lockShared.AcquireShared();
}

SRWLock_share::~SRWLock_share()
{
    m_lockShared.ReleaseShared();
}

//////////////////////////////////////////////////////////////////////////

SRWLock_exclusive::SRWLock_exclusive(SRWLock& lock_) : m_lockExclusive(lock_)
{
    m_lockExclusive.AcquireExclusive();
}

SRWLock_exclusive::~SRWLock_exclusive()
{
    m_lockExclusive.ReleaseExclusive();
}
