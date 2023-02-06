#ifndef __TINY_TOOLKIT__UTILITIES__NET__H__
#define __TINY_TOOLKIT__UTILITIES__NET__H__


#include "../common/common.h"


namespace Toolkit
{
    class Net
    {
    public:

        static bool AsNetByte(const std::string &value, uint32_t &head, uint32_t &tail);

        static bool TraverseAddressFromHost(const char *host, std::vector<std::string> &list);

        static bool CloseSocket(TINY_TOOLKIT_SOCKET_TYPE socket);

        static bool DisableNagle(TINY_TOOLKIT_SOCKET_TYPE socket);

        static bool EnableLinger(TINY_TOOLKIT_SOCKET_TYPE socket, int32_t timeout = 0);

        static bool EnableNonBlock(TINY_TOOLKIT_SOCKET_TYPE socket);

        static bool EnableReuseAddress(TINY_TOOLKIT_SOCKET_TYPE socket);

        static bool GetLocalAddress(TINY_TOOLKIT_SOCKET_TYPE socket, struct sockaddr_in &address);

        static bool GetRemoteAddress(TINY_TOOLKIT_SOCKET_TYPE socket, struct sockaddr_in &address);

        static uint32_t AsNetByte(const char *value);

        static uint32_t AsHostByte(const char *value);

    };
}


#endif // __TINY_TOOLKIT__UTILITIES__NET__H__
