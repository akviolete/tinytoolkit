#include "client.h"
#include "../common.h"

void TCPSession::OnConnect()
{

    std::cout << "OnConnect" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}

void TCPSession::OnDisconnect()
{

    std::cout << "OnDisconnect" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}

void TCPSession::OnConnectFailed()
{

    std::cout << "OnConnectFailed" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}


void TCPSession::OnSessionSend(std::size_t protocol, const char *data, std::size_t size)
{
    char buffer[sizeof(NET_TRAN_HEAD)] = {0};

    auto header = (NET_TRAN_HEAD *) buffer;

    header->protocol = protocol;

    header->length = size;

    Send(buffer, sizeof(NET_TRAN_HEAD));

    Send(data, size);

}


std::size_t TCPSession::OnReceive(const char *data, std::size_t size)
{
    (void) data;

    return size;
}
