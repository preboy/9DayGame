#pragma once

namespace LibWindows
{
    class SRWLock
    {
    public:

        SRWLock();
        ~SRWLock();

    public:

        void    AcquireShared();
        void    ReleaseShared();

        void    AcquireExclusive();
        void    ReleaseExclusive();

    private:

        SRWLOCK m_lock;
    };


    class SRWLock_share
    {
    public:
        SRWLock_share(SRWLock& lock_);
       ~SRWLock_share();

    private:
        SRWLock&    m_lockShared;
    };


    class SRWLock_exclusive
    {

    public:
        SRWLock_exclusive(SRWLock& lock_);
       ~SRWLock_exclusive();

    private:
        SRWLock&    m_lockExclusive;

    };
}