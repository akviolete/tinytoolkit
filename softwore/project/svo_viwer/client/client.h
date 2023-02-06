#ifndef __SVO__VIWER__CLIENT__
#define __SVO__VIWER__CLIENT__

#include "../toolkit/toolkit.h"


class TCPSession : public Toolkit::ITCPSession
{
public:
    TCPSession() = default;

    ~TCPSession() override = default;

public:

    void OnConnect() override;

    void OnDisconnect() override;

    void OnConnectFailed() override;

    std::size_t OnReceive(const char *data, std::size_t size) override;

    void OnSessionSend(std::size_t protocl, const char *data, std::size_t size);
};

#endif
