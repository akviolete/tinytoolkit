#ifndef __TINY_TOOLKIT__NET__PIPE__H__
#define __TINY_TOOLKIT__NET__PIPE__H__

#include "../common/common.h"


namespace Toolkit
{
    class INetPipe
    {
    public:

        virtual ~INetPipe() = default;


        virtual void Send(const void *data, std::size_t size) = 0;

        virtual void Close() = 0;
    };

    class ITCPPipe : public INetPipe
    {
    public:
        virtual bool AsyncSend() = 0;

        virtual bool AsyncAccept() = 0;

        virtual bool AsyncReceive() = 0;
    };

    class IUDPPipe : public INetPipe
    {
    public:
        virtual bool AsyncSend() = 0;

        virtual bool AsyncReceive() = 0;
    };
}


#endif
