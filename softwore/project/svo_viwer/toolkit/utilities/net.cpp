#include "net.h"

namespace Toolkit
{
    bool Net::AsNetByte(const std::string &value, uint32_t &head, uint32_t &tail)
    {
        std::size_t pos = value.find('-');

        if (pos == std::string::npos)
        {
            pos = value.find('/');

            if (pos == std::string::npos)  /// a.b.c.d
            {
                head = AsNetByte(value.c_str());
                tail = head;
            } else
            {
                if (value.find('.', pos + 1) == std::string::npos)  /// a.b.c.d/e
                {
                    int64_t mask = strtol(value.substr(pos + 1).data(), nullptr, 10);

                    if (32 < mask || mask < 0)
                    {
                        return false;
                    }

                    head = AsNetByte(value.substr(0, pos).c_str());
                    tail = head | ~(mask == 0 ? 0 : htonl(0xFFFFFFFF << (32 - mask)));
                } else  /// a.b.c.d/a.b.c.d
                {
                    head = AsNetByte(value.substr(0, pos).c_str());
                    tail = AsNetByte(value.substr(pos + 1).c_str());
                }
            }
        } else  /// a.b.c.d-a.b.c.d
        {
            head = AsNetByte(value.substr(0, pos).c_str());
            tail = AsNetByte(value.substr(pos + 1).c_str());
        }

        return head <= tail;
    }

    bool Net::TraverseAddressFromHost(const char *host, std::vector<std::string> &list)
    {
        bool status = false;

        struct addrinfo hints{};
        struct addrinfo *result{nullptr};

        hints.ai_flags = AI_CANONNAME;
        hints.ai_family = AF_UNSPEC;  /// 意味着函数返回的是适用于指定主机名和服务名且适合任何协议族的地址
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = 0;

        auto res = getaddrinfo(host, nullptr, &hints, &result);

        if (res == 0)
        {
            for (auto iter = result; iter != nullptr; iter = iter->ai_next)
            {
                char address[1024]{0};

                res = getnameinfo(iter->ai_addr, static_cast<socklen_t>(iter->ai_addrlen), address, sizeof(address),
                                  nullptr, 0, NI_NUMERICHOST | NI_NUMERICSERV);

                if (res == 0)
                {
                    status = true;

                    list.emplace_back(address);
                } else
                {
                    status = false;

                    TINY_TOOLKIT_ASSERT(false, gai_strerror(res));

                    break;
                }
            }

            freeaddrinfo(result);
        } else
        {
            status = false;

            TINY_TOOLKIT_ASSERT(false, gai_strerror(res));
        }

        return status;
    }

    bool Net::CloseSocket(TINY_TOOLKIT_SOCKET_TYPE socket)
    {
#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        return ::closesocket(socket) == 0;

#else

        return ::close(socket) == 0;

#endif
    }

    bool Net::DisableNagle(TINY_TOOLKIT_SOCKET_TYPE socket)
    {
        int32_t val = 1l;

        return setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char *>(&val), sizeof(val)) == 0;
    }

    bool Net::EnableLinger(TINY_TOOLKIT_SOCKET_TYPE socket, int32_t timeout)
    {
#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        LINGER val{ };

#else

        struct linger val{};

#endif

        val.l_onoff = 1l;
        val.l_linger = timeout;

        return setsockopt(socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char *>(&val), sizeof(val)) == 0;
    }

    bool Net::EnableNonBlock(TINY_TOOLKIT_SOCKET_TYPE socket)
    {
#if TINY_TOOLKIT_PLATFORM == TINY_TOOLKIT_PLATFORM_WINDOWS

        u_long opt = 1l;

        return ioctlsocket(socket, FIONBIO, &opt) == 0;

#else

        return fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) == 0;

#endif
    }


    bool Net::EnableReuseAddress(TINY_TOOLKIT_SOCKET_TYPE socket)
    {
        int32_t val = 1l;

        return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&val), sizeof(val)) == 0;
    }

    bool Net::GetLocalAddress(TINY_TOOLKIT_SOCKET_TYPE socket, struct sockaddr_in &address)
    {
        std::size_t len = sizeof(struct sockaddr_in);

        return ::getsockname(socket, reinterpret_cast<struct sockaddr *>(&address),
                             reinterpret_cast<socklen_t *>(&len)) == 0;
    }

    bool Net::GetRemoteAddress(TINY_TOOLKIT_SOCKET_TYPE socket, struct sockaddr_in &address)
    {
        std::size_t len = sizeof(struct sockaddr_in);

        return ::getpeername(socket, reinterpret_cast<struct sockaddr *>(&address),
                             reinterpret_cast<socklen_t *>(&len)) == 0;
    }
    
    uint32_t Net::AsNetByte(const char *value)
    {
        struct in_addr addr{0};

        inet_pton(AF_INET, value, &addr);

        return addr.s_addr;
    }
}
