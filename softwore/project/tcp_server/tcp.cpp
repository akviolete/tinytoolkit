#include "tcp.h"

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

        {
            if (_callback)
            {

                std::cout << RemoteHost() << "," << RemotePort() << std::endl;

                _callback(header->protocl, tinyToolkit::String::Format("{}:{}", RemoteHost(), RemotePort()),
                          data + count + sizeof(NET_TRAN_HEAD), header->length);
            }

        }

        size -= total;

        count += total;
    }
}

TCPServer::TCPServer()
{
}

TCPServer::~TCPServer()
{
}

void TCPServer::OnError()
{
}

void TCPServer::SetSessionCallBack(
        std::function<void(std::size_t protocl, const std::string &, const char *, std::size_t)> callback)
{
    _callback = callback;
}

bool TCPServer::OnSessionSend(std::size_t protocl, std::string const &key, std::string const &buffer)
{
    auto find = _pool.find(key);

    if (_pool.end() != find)
    {
        std::string value;

        SessionPacket(value, buffer, protocl);

        find->second->Send(value.c_str(), value.size());

        return true;
    }

    return false;
}

void TCPServer::SessionPacket(std::string &retValue, const std::string &value, int protocl)
{
    char buffer[sizeof(NET_TRAN_HEAD) + value.size()];

    memset(buffer, 0, sizeof(buffer));

    auto header = (NET_TRAN_HEAD *) buffer;

    header->protocl = protocl;

    header->length = value.size();

    memcpy(buffer + sizeof(NET_TRAN_HEAD), value.c_str(), value.size());

    retValue = std::move(std::string(buffer, sizeof(NET_TRAN_HEAD) + value.size()));
}

void TCPServer::OnRelease()
{

    for (auto &iter : _pool)
    {
        iter.second->Close();

        delete iter.second;
    }
}

/**
 *
 * 会话错误触发回调函数
 *
 */
void TCPServer::OnSessionError(tinyToolkit::ITCPSession *session)
{
    std::string key = RemoteHost() + ":" + std::to_string(RemotePort());

    if (session) //引擎和管理器断开
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

/**
 *
 * 会话连接触发回调函数
 *
 * @return 会话
 *
 */
tinyToolkit::ITCPSession *TCPServer::OnSessionConnect()
{

    std::string key = RemoteHost() + ":" + std::to_string(RemotePort());

    auto find = _pool.find(key);

    if (find == _pool.end())
    {
        _pool.insert(std::make_pair(key, new TCPServerSession(_callback)));

        find = _pool.find(key);
    }

    std::cout << "OnSessionConnect:" << key << std::endl;

    return find->second;
}


TCPServerSession::TCPServerSession(
        std::function<void(std::size_t, const std::string &, const char *, std::size_t)> callback)
        : _callback(callback)
{
}

TCPServerSession::~TCPServerSession()
{
}

void TCPServerSession::OnConnect()
{
    std::cout << "OnConnect:"  << std::endl;
    //LOGINFO("RemoteHost:{},RemotePort:{},LocalPort:{},Connect", RemoteHost(), RemotePort(), LocalPort());
}

void TCPServerSession::OnDisconnect()
{
    std::cout << "OnDisconnect:"  << std::endl;
    //LOGWARNING("RemoteHost:{},RemotePort:{},LocalPort:{},Disconnect", RemoteHost(), RemotePort(), LocalPort());
}

void TCPServerSession::OnConnectFailed()
{
    std::cout << "OnConnectFailed:"  << std::endl;
    // LOGWARNING("RemoteHost:{},RemotePort:{},LocalPort:{},Error:{}", RemoteHost(), RemotePort(), LocalPort(),
    //          tinyToolkit::OS::LastErrorMessage());
}

