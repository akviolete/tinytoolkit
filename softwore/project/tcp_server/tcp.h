#ifndef _KVIOLET_TCP_H_
#define _KVIOLET_TCP_H_

#include "basic.h"

typedef struct
{
    std::size_t length;
    std::size_t protocl;
} NET_TRAN_HEAD;


class TCPServerSession : public tinyToolkit::ITCPSession
{
public:
    TCPServerSession(std::function<void(std::size_t protocl, const std::string &, const char *, std::size_t)> callback);

    ~TCPServerSession() override;

    void OnConnect() override;

    void OnDisconnect() override;

    void OnConnectFailed() override;

    std::size_t OnReceive(const char *data, std::size_t size) override;

private:
    std::function<void(std::size_t, const std::string &, const char *, std::size_t)> _callback{nullptr};
};

class TCPServer : public tinyToolkit::ITCPServer
{
public:
    TCPServer();

    ~TCPServer() override;

    void OnError() override;

    void OnRelease() override;

    tinyToolkit::ITCPSession *OnSessionConnect() override;

    void OnSessionError(tinyToolkit::ITCPSession *session) override;

public:
    bool OnSessionSend(std::size_t protocl, std::string const &key, std::string const &buffer);

    void SetSessionCallBack(
            std::function<void(std::size_t protocl, const std::string &, const char *, std::size_t)> callback);


protected:
    void SessionPacket(std::string &retValue, const std::string &value, int protocl);

protected:
    std::map<std::string, tinyToolkit::ITCPSession *> _pool{};
    std::function<void(std::size_t, const std::string &, const char *, std::size_t)> _callback{nullptr};

};


#endif // _KVIOLET_TCP_H_
