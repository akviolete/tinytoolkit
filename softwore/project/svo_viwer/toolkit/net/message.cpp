
#include "message.h"


namespace Toolkit
{
    NetMessage::NetMessage(const void *data, std::size_t size) : _size(size)
    {
        _data = new char[_size + 1];

        memcpy(_data, data, _size);

        _data[_size] = '\0';
    }

    NetMessage::NetMessage(Toolkit::NetMessage &&rhs) noexcept: _data(rhs._data), _size(rhs._size)
    {

    }

    NetMessage::~NetMessage()
    {
        delete[] _data;

        _data = nullptr;
    }
}
