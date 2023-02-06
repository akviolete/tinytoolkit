#ifndef __TINY_TOOLKIT__NET__BUFFER__H__
#define __TINY_TOOLKIT__NET__BUFFER__H__

#include "../common/common.h"


namespace Toolkit
{
    class NetCache
    {
    public:

        explicit NetCache(std::size_t size);

        ~NetCache();

        void Clear();

        bool Reduced(std::size_t size);

        bool Push(const void *value, std::size_t size);

        std::size_t Length() const;

        const char *Value() const;

    private:
        char *_value{nullptr};

        std::size_t _size{0};
        std::size_t _wPos{0};
        std::size_t _rPos{0};

        mutable std::mutex _mutex{};
    };
}

#endif
