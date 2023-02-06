#ifndef __TINY_TOOLKIT__NET__TYPE__H__
#define __TINY_TOOLKIT__NET__TYPE__H__


#include "../common/common.h"


namespace Toolkit
{
    enum class NET_EVENT_TYPE : uint8_t
    {
        IO,
        SEND,
        ACCEPT,
        CONNECT,
        RECEIVE,
        INVALID,
    };
}


#endif
