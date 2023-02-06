#ifndef __LOCK__FREE_QUEUE__H__
#define __LOCK__FREE_QUEUE__H__

#include "ypipe.hpp"

#include <sys/eventfd.h>
#include <sys/timerfd.h>


namespace LockFreeQueue
{

    class SimpleSignaler
    {
    public:
        SimpleSignaler();

        ~SimpleSignaler();

    public:

        void Send();

        void Read();

    private:
        uint32_t _fd{0};
    };

    class SimpleTimer
    {
    public:
        SimpleTimer(uint64_t loopUs = 50);

        ~SimpleTimer();

    public:

        uint64_t Read();

    private:
        uint32_t _fd{0};
    };


    template<typename TypeT>
    class LockFreeNotifyQueue
    {
    public:
        LockFreeNotifyQueue() = default;

        ~LockFreeNotifyQueue() = default;

    public:
        void Push(const TypeT &value)
        {
            _yqueue.write(value, false);

            _yqueue.flush();

            _siger.Send();
        }


        bool WaitPop(TypeT &value)
        {
            _siger.Read();

            if (_yqueue.read(&value))
            {
                return true;
            }
            return false;
        }

    private:
        SimpleSignaler _siger;
        zmq::ypipe_t<TypeT, 1024> _yqueue;
    };


    template<typename TypeT>
    class LockFreeLoopQueue
    {
    public:
        LockFreeLoopQueue() = default;

        ~LockFreeLoopQueue() = default;

    public:
        void Push(const TypeT &value)
        {
            _yqueue.write(value, false);

            _yqueue.flush();
        }

        bool WaitPop(TypeT &value)
        {

        }

    private:

        SimpleTimer _timer;
        zmq::ypipe_t<TypeT, 1024> _yqueue;
    };

}

#endif