#ifndef __TINY_TOOLKIT__NET__MANAGER__H__
#define __TINY_TOOLKIT__NET__MANAGER__H__


#include "tcp.h"


namespace Toolkit
{
    class NetManager
    {
    public:

        ~NetManager();

        bool Launch();

        bool LaunchTCPClient(ITCPSession *client);

        bool LaunchTCPServer(ITCPServer *server);

    private:

        void ThreadProcess();

    private:
        bool _status{false};

        std::thread _thread{};

        TINY_TOOLKIT_SOCKET_HANDLE _handle{TINY_TOOLKIT_SOCKET_HANDLE_INVALID};
    };
}


#endif
