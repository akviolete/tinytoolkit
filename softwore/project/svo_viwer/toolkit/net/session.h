#ifndef __TINY_TOOLKIT__NET__SESSION__H__
#define __TINY_TOOLKIT__NET__SESSION__H__

#include "pipe.h"
#include "cache.h"
#include "message.h"

#include "../container/queue.h"


namespace Toolkit
{
    class ITCPSession
    {
        friend class NetManager;

        friend class TCPServerPipe;

        friend class TCPSessionPipe;

    public:

        virtual ~ITCPSession() = default;

        virtual void OnConnect() = 0;

        virtual void OnDisconnect() = 0;

        virtual void OnConnectFailed() = 0;

        virtual std::size_t OnReceive(const char *data, std::size_t size) = 0;

        void Close();

        void Send(const void *data, std::size_t size);

        bool Launch(std::string remoteHost, uint16_t remotePort, std::size_t cacheSize);

        uint16_t LocalPort() const;

        uint16_t RemotePort() const;

        std::size_t CacheSize() const;


        const std::string &LocalHost() const;


        const std::string &RemoteHost() const;

    private:
        uint16_t _localPort{0};
        uint16_t _remotePort{0};

        std::string _localHost{};
        std::string _remoteHost{};

        std::size_t _cacheSize{0};

        std::shared_ptr<ITCPPipe> _pipe{};
    };
}


#endif
