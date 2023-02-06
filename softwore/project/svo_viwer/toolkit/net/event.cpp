#include "event.h"


namespace Toolkit
{

    NetEvent::NetEvent()
    {
#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        memset(&_overlap, 0, sizeof(OVERLAPPED));

#else

        _type = NET_EVENT_TYPE::INVALID;

#endif
    }

    NetEvent::NetEvent(NET_EVENT_TYPE type, TINY_TOOLKIT_SOCKET_TYPE socket, INetCompleter *completer) : _completer(
            completer),
                                                                                                         _type(type),
                                                                                                         _socket(socket)
    {
#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        memset(&_overlap, 0, sizeof(OVERLAPPED));

#endif
    }
}
