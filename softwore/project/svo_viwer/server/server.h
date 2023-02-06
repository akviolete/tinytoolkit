#ifndef __SVO__VIWER__SERVER__H__
#define __SVO__VIWER__SERVER__H__

#include "../toolkit/toolkit.h"

#include <map>
#include <string>
#include <iostream>
#include <functional>

typedef std::function<void(std::size_t protocol, const char *data, std::size_t size)> SessionCallBack;

class TCPServerSession : public Toolkit::ITCPSession
{
public:
    TCPServerSession(SessionCallBack callback);

    ~TCPServerSession() override;

    void OnConnect() override;

    void OnDisconnect() override;

    void OnConnectFailed() override;

    std::size_t OnReceive(const char *data, std::size_t size) override;

private:
    SessionCallBack _callback{nullptr};
};

class TCPServer : public Toolkit::ITCPServer
{
public:
    TCPServer(SessionCallBack call);

    ~TCPServer() override;

    void OnError() override;

    void OnRelease() override;

    Toolkit::ITCPSession *OnSessionConnect() override;

    void OnSessionError(Toolkit::ITCPSession *session) override;

protected:
    SessionCallBack _callback{nullptr};
    std::map<std::string, Toolkit::ITCPSession *> _pool{};
};


#endif // __SVO__VIWER__SERVER__H__
