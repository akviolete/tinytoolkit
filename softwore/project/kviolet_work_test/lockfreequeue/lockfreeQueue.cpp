#include <unistd.h>
#include <iostream>

#include "lockfreeQueue.h"

namespace LockFreeQueue
{
    SimpleSignaler::SimpleSignaler()
    {
        int flags = 0;

        _fd = eventfd(0, flags);

        if (_fd == -1)
        {
            throw std::runtime_error("Eventfd cteate Error");
        }
    }


    SimpleSignaler::~SimpleSignaler()
    {
        close(_fd);
    }


    void SimpleSignaler::Send()
    {
        static uint64_t index = 1;

        (void) write(_fd, &index, sizeof(index));

    }

    void SimpleSignaler::Read()
    {
        static uint64_t index = 0;

        (void) read(_fd, &index, sizeof(index));
    }


    SimpleTimer::SimpleTimer(uint64_t loopUs)
    {
        _fd = timerfd_create(CLOCK_REALTIME, 0);

        struct itimerspec newValue;

        newValue.it_value.tv_sec = 1;
        newValue.it_value.tv_nsec = 1000 * 1000;

        newValue.it_interval.tv_sec = 0;
        newValue.it_interval.tv_nsec = loopUs;

        if (-1 == timerfd_settime(_fd, TFD_TIMER_ABSTIME, &newValue, NULL))
        {
            close(_fd);

            throw std::runtime_error(" Timerfd Cteate Error");
        }
    }


    SimpleTimer::~SimpleTimer()
    {
        close(_fd);
    }


    uint64_t SimpleTimer::Read()
    {
        static uint64_t exp;

        read(_fd, &exp, sizeof(uint64_t));

        return exp;
    }

}