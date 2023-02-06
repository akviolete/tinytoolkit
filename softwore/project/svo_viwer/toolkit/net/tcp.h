#ifndef __TINY_TOOLKIT__NET__TCP__H__
#define __TINY_TOOLKIT__NET__TCP__H__


#include "event.h"
#include "server.h"


namespace Toolkit
{
    class TCPSessionPipe : public ITCPPipe, public INetCompleter
    {
        friend class TCPServerPipe;

    public:

        TCPSessionPipe(ITCPSession *session, TINY_TOOLKIT_SOCKET_TYPE socket, TINY_TOOLKIT_SOCKET_HANDLE handle);

        ~TCPSessionPipe() override = default;

        void Close() override;

        void Send(const void *data, std::size_t size) override;

        void OnCallback(NetEvent *netEvent, void *sysEvent) override;

        bool AsyncSend() override;

        bool AsyncAccept() override;

        bool AsyncReceive() override;

    private:
        void DoIO(NetEvent *netEvent, void *sysEvent);

        void DoSend(NetEvent *netEvent, void *sysEvent);

        void DoReceive(NetEvent *netEvent, void *sysEvent);

        void DoConnect(NetEvent *netEvent, void *sysEvent);

    public:
        bool _isSend{false};
        bool _isConnect{false};

#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        NetEvent _sendEvent{ };
        NetEvent _receiveEvent{ };

#else

        NetEvent _netEvent{};

#endif

    private:
        NetCache _cache;

        ITCPSession *_session{nullptr};

        LockQueue<std::shared_ptr<NetMessage>> _sendQueue{};

        TINY_TOOLKIT_SOCKET_TYPE _socket{TINY_TOOLKIT_SOCKET_INVALID};

        TINY_TOOLKIT_SOCKET_HANDLE _handle{TINY_TOOLKIT_SOCKET_HANDLE_INVALID};
    };

    class TCPServerPipe : public ITCPPipe, public INetCompleter
    {
    public:

        TCPServerPipe(ITCPServer *server, TINY_TOOLKIT_SOCKET_TYPE socket, TINY_TOOLKIT_SOCKET_HANDLE handle);

        ~TCPServerPipe() override = default;

        void Close() override;

        void Send(const void *data, std::size_t size) override;

        void OnCallback(NetEvent *netEvent, void *sysEvent) override;

        bool AsyncSend() override;

        bool AsyncAccept() override;

        bool AsyncReceive() override;

    private:

        void DoAccept(NetEvent *netEvent, void *sysEvent);

    public:
        NetEvent _netEvent{};

    private:
        ITCPServer *_server{nullptr};

        TINY_TOOLKIT_SOCKET_TYPE _socket{TINY_TOOLKIT_SOCKET_INVALID};

        TINY_TOOLKIT_SOCKET_HANDLE _handle{TINY_TOOLKIT_SOCKET_HANDLE_INVALID};
    };
}


#endif // __TINY_TOOLKIT__NET__TCP__H__
