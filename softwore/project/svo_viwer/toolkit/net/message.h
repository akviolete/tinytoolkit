#ifndef __TINY_TOOLKIT__NET__MESSAGE__H__
#define __TINY_TOOLKIT__NET__MESSAGE__H__

#include "../common/common.h"


namespace Toolkit
{
    class NetMessage
    {
    public:
        NetMessage(const void *data, std::size_t size);

        NetMessage(NetMessage &&rhs) noexcept;

        ~NetMessage();

    public:
        char *_data{nullptr};

        std::size_t _pos{0};
        std::size_t _size{0};
    };
}


#endif
