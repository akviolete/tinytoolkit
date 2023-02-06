#ifndef __TINY_TOOLKIT__NET__SERVER__H__
#define __TINY_TOOLKIT__NET__SERVER__H__

#include "session.h"


namespace Toolkit
{
    class ITCPServer
    {
        friend class NetManager;

        friend class TCPServerPipe;

    public:
        virtual ~ITCPServer() = default;

        virtual void OnError() = 0;

        virtual void OnRelease() = 0;

        virtual void OnSessionError(Toolkit::ITCPSession *session) = 0;

        virtual Toolkit::ITCPSession *OnSessionConnect() = 0;

        void Close();

        void Send(const void *data, std::size_t size);

        bool Launch(std::string localHost, uint16_t localPort, std::size_t cacheSize);

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
