#ifndef __TCP__H__
#define __TCP__H__

#include "basic.h"

class TCPSession : public tinyToolkit::ITCPSession
{
public:
    TCPSession() = default;

    ~TCPSession() override = default;

    void OnConnect() override;

    void OnDisconnect() override;

    void OnConnectFailed() override;

    std::size_t OnReceive(const char *data, std::size_t size) override;
};

#endif //__TCP__H__
