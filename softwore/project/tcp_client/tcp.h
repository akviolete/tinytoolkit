#ifndef _KVIOLET_TCP_H_
#define _KVIOLET_TCP_H_

#include "basic.h"

typedef struct
{
    std::size_t length;
    std::size_t protocl;
} NET_TRAN_HEAD;


class TCPSession : public tinyToolkit::ITCPSession
{
public:
    TCPSession() = default;

    ~TCPSession() override = default;

public:

    void OnConnect() override;

    void OnDisconnect() override;

    void OnConnectFailed() override;

    std::size_t OnReceive(const char *data, std::size_t size) override;

public:
    bool OnSessionStauts();


    bool OnSessionSend(std::size_t protocl, std::string const &buffer);

    void SetSessionCallBack(
            std::function<void(std::size_t, const char *, std::size_t)> callback);

protected:
    void SessionPacket(std::string &retValue, const std::string &value, int protocl);

protected:
    bool _isConnect{false};

    std::function<void(std::size_t, const char *, std::size_t)> _callback{nullptr};
};

#endif // _KVIOLET_TCP_H_
