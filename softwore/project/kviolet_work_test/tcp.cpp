#include "tcp.h"

void TCPSession::OnConnect()
{
    KLOG_INFO("{}", "Onconnect");

}

void TCPSession::OnDisconnect()
{
    KLOG_INFO("{}", "OnDisconnect");

}

void TCPSession::OnConnectFailed()
{
    KLOG_INFO("OnConnectFailed:{}", strerror(errno));
}


typedef struct
{
    int length;
    int protocl;
} NET_TRAN_HEAD;

std::size_t TCPSession::OnReceive(const char *data, std::size_t size)
{
    if (size < sizeof(NET_TRAN_HEAD))
    {
        return 0;
    }
    auto header = (NET_TRAN_HEAD *) data;
    auto total = sizeof(NET_TRAN_HEAD) + header->length;
    if (total > size)
    {
        return 0;
    }
    if (header->protocl == 0)
    {
        KLOG_INFO("Recv:{}", std::string(data + sizeof(NET_TRAN_HEAD), header->length));
    }
    return total;


}
