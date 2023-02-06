#include "server.h"
#include "../common.h"

std::size_t TCPServerSession::OnReceive(const char *data, std::size_t size)
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

        if (__builtin_expect(!!_callback, 1))
        {
            _callback(header->protocol, data + count + sizeof(NET_TRAN_HEAD), header->length);
        }

        size -= total;
        count += total;
    }
}

TCPServer::TCPServer(SessionCallBack call) : _callback(call)
{
}

TCPServer::~TCPServer()
{
}

void TCPServer::OnError()
{
}


void TCPServer::OnRelease()
{

    for (auto &iter : _pool)
    {
        iter.second->Close();

        delete iter.second;
    }
}


void TCPServer::OnSessionError(Toolkit::ITCPSession *session)
{
    std::string key = RemoteHost() + ":" + std::to_string(RemotePort());

    if (session)
    {
        auto find = _pool.find(key);

        if (find != _pool.end())
        {
            find->second->Close();

            delete find->second;

            _pool.erase(find);
        }
    }
}


Toolkit::ITCPSession *TCPServer::OnSessionConnect()
{

    std::string key = RemoteHost() + ":" + std::to_string(RemotePort());

    auto find = _pool.find(key);

    if (find == _pool.end())
    {
        _pool.insert(std::make_pair(key, new TCPServerSession(_callback)));

        find = _pool.find(key);
    }

    return find->second;
}


TCPServerSession::TCPServerSession(SessionCallBack callback) : _callback(callback)
{
}

TCPServerSession::~TCPServerSession()
{
}

void TCPServerSession::OnConnect()
{
    std::cout << "RemoteHost:" << RemoteHost()
              << ",RemotePort:" << RemotePort()
              << ",LocalPort::" << LocalPort()
              << ",Connect" << std::endl;
}

void TCPServerSession::OnDisconnect()
{
    std::cout << "RemoteHost:" << RemoteHost()
              << ",RemotePort:" << RemotePort()
              << ",LocalPort::" << LocalPort()
              << ",DisConnect" << std::endl;

}

void TCPServerSession::OnConnectFailed()
{

    std::cout << "RemoteHost:" << RemoteHost()
              << ",RemotePort:" << RemotePort()
              << ",LocalPort::" << LocalPort()
              << ",OnConnectFailed" << std::endl;
}

