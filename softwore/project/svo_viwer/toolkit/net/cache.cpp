#include "cache.h"

namespace Toolkit
{
    NetCache::NetCache(std::size_t size) : _size(size)
    {
        _value = new char[size + 1];
    }

    NetCache::~NetCache()
    {
        delete[] _value;

        _value = nullptr;
    }

    void NetCache::Clear()
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _rPos = 0;
        _wPos = 0;

        memset(_value, 0, _size);
    }

    bool NetCache::Reduced(std::size_t size)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if ((_rPos + size) > _wPos)
        {
            return false;
        } else
        {
            _rPos += size;

            return true;
        }
    }

    bool NetCache::Push(const void *data, std::size_t size)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if ((_size - Length()) < size)
        {
            return false;
        }

        if ((_size - _wPos) < size)
        {
            if (_rPos == _wPos)
            {
                _rPos = 0;
                _wPos = 0;
            } else
            {
                memmove(_value, _value + _rPos, Length());

                _wPos = Length();
                _rPos = 0;
            }
        }

        memcpy(_value + _wPos, data, size);

        _wPos += size;

        _value[_wPos] = '\0';

        return true;
    }

    std::size_t NetCache::Length() const
    {
        return _wPos - _rPos;
    }

    const char *NetCache::Value() const
    {
        return _value + _rPos;
    }
}