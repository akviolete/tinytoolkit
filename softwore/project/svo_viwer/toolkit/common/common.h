#ifndef ___TOOLKIT__COMMON__COMMON__H__
#define ___TOOLKIT__COMMON__COMMON__H__


#include <cassert>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>


#include <queue>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <condition_variable>


#define TINY_TOOLKIT_ASSERT(cond, ...)    (void)cond


#define TINY_TOOLKIT_NET_COUNT                      10240
#define TINY_TOOLKIT_SOCKET_ERROR                   -1
#define TINY_TOOLKIT_SOCKET_INVALID                 -1
#define TINY_TOOLKIT_SOCKET_TEMP_SIZE               1460
#define TINY_TOOLKIT_SOCKET_LISTEN_COUNT            2048
#define TINY_TOOLKIT_SOCKET_HANDLE_INVALID          -1

#define TINY_TOOLKIT_SOCKET_TYPE                    int32_t
#define TINY_TOOLKIT_SOCKET_HANDLE                  int32_t


#define TINY_TOOLKIT_PLATFORM_LINUX                 1
#define TINY_TOOLKIT_PLATFORM TINY_TOOLKIT_PLATFORM_LINUX


#endif // ___TOOLKIT__COMMON__COMMON__H__
