#include "server.h"
#include "manager.h"

#include "../utilities/singleton.h"


namespace Toolkit
{
    void ITCPServer::Close()
    {
        if (_pipe)
        {
            _pipe->Close();
        }
    }

    void ITCPServer::Send(const void *data, std::size_t size)
    {
        if (_pipe)
        {
            _pipe->Send(data, size);
        }
    }

    bool ITCPServer::Launch(std::string localHost, uint16_t localPort, std::size_t cacheSize)
    {
        _cacheSize = cacheSize;

        _localPort = localPort;
        _localHost = std::move(localHost);

        return Singleton<NetManager>::Instance().LaunchTCPServer(this);
    }

    uint16_t ITCPServer::LocalPort() const
    {
        return _localPort;
    }

    uint16_t ITCPServer::RemotePort() const
    {
        return _remotePort;
    }

    std::size_t ITCPServer::CacheSize() const
    {
        return _cacheSize;
    }

    const std::string &ITCPServer::LocalHost() const
    {
        return _localHost;
    }


    const std::string &ITCPServer::RemoteHost() const
    {
        return _remoteHost;
    }
}
