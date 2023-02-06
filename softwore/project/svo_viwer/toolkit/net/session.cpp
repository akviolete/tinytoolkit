#include "session.h"
#include "manager.h"


#include "../utilities/singleton.h"


namespace Toolkit
{
    void ITCPSession::Close()
    {
        if (_pipe)
        {
            _pipe->Close();
        }
    }

    void ITCPSession::Send(const void *data, std::size_t size)
    {
        if (_pipe)
        {
            _pipe->Send(data, size);
        }
    }

    bool ITCPSession::Launch(std::string remoteHost, uint16_t remotePort, std::size_t cacheSize)
    {
        _cacheSize = cacheSize;

        _remotePort = remotePort;
        _remoteHost = std::move(remoteHost);

        return Singleton<NetManager>::Instance().LaunchTCPClient(this);
    }

    uint16_t ITCPSession::LocalPort() const
    {
        return _localPort;
    }

    uint16_t ITCPSession::RemotePort() const
    {
        return _remotePort;
    }

    std::size_t ITCPSession::CacheSize() const
    {
        return _cacheSize;
    }

    const std::string &ITCPSession::LocalHost() const
    {
        return _localHost;
    }

    const std::string &ITCPSession::RemoteHost() const
    {
        return _remoteHost;
    }
}
