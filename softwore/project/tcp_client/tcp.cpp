#include "tcp.h"

void TCPSession::OnConnect()
{
    _isConnect = true;

    std::cout << "OnConnect" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}

void TCPSession::OnDisconnect()
{
    _isConnect = false;

    std::cout << "OnDisconnect" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}

void TCPSession::OnConnectFailed()
{
    _isConnect = false;

    std::cout << "OnConnectFailed" << RemoteHost() << ":" << RemotePort() << "," << LocalHost() << ":"
              << LocalPort() << std::endl;
}

bool TCPSession::OnSessionStauts()
{
    return _isConnect;
}

void TCPSession::SetSessionCallBack(
        std::function<void(std::size_t, const char *, std::size_t)> callback)
{
    _callback = callback;
}

bool TCPSession::OnSessionSend(std::size_t protocl, std::string const &buffer)
{

    std::string value;

    SessionPacket(value, buffer, protocl);

    Send(value.c_str(), value.size());

    return true;
}

void TCPSession::SessionPacket(std::string &retValue, const std::string &value, int protocl)
{
    char buffer[sizeof(NET_TRAN_HEAD) + value.size()];

    memset(buffer, 0, sizeof(buffer));

    auto header = (NET_TRAN_HEAD *) buffer;

    header->protocl = protocl;

    header->length = value.size();

    memcpy(buffer + sizeof(NET_TRAN_HEAD), value.c_str(), value.size());

    retValue = std::move(std::string(buffer, sizeof(NET_TRAN_HEAD) + value.size()));
}

std::size_t TCPSession::OnReceive(const char *data, std::size_t size)
{
    std::size_t count = 0;

    while (true)
    {
        if (size < sizeof(NET_TRAN_HEAD))
        {
            return count;
        }

        auto header = (NET_TRAN_HEAD *) (data + count);
        auto total = sizeof(NET_TRAN_HEAD) + header->length;

        if (total > size)
        {
            return count;
        }

        {
            if (_callback)
            {
                _callback(header->protocl, data + count + sizeof(NET_TRAN_HEAD), header->length);
            } else
            {
                std::cerr << "TCPSession No Callback!!!" << std::endl;
            }

        }

        size -= total;

        count += total;
    }
}
