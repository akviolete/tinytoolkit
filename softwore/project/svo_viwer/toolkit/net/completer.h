#ifndef __TINY_TOOLKIT__NET__COMPLETER__H__
#define __TINY_TOOLKIT__NET__COMPLETER__H__

#include "../common/common.h"


namespace Toolkit
{
    class NetEvent;

    class INetCompleter
    {
    public:

        virtual ~INetCompleter() = default;

        virtual void OnCallback(NetEvent *netEvent, void *sysEvent) = 0;
    };
}


#endif // __TINY_TOOLKIT__NET__COMPLETER__H__
