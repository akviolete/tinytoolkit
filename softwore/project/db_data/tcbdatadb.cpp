#include "tcbdatadb.h"

#include <iostream>
#include <stdexcept>

const std::string KEY_TAIL = "KEY_TAIL";


TCBDataDb::TCBDataDb(const std::string &id, std::size_t index) : _index(index)
{
    int cacheLeaf = 2048;
    int cacheNonLeaf = 1024;
    int memory = 1024 * 1024 * 8;

    _handle = tcbdbnew();

    tcbdbsetmutex(_handle); /* 开启线程互斥锁 */
    tcbdbtune(_handle, 1024, 2048, 50000000, 8, 10, BDBTLARGE);
    tcbdbsetcache(_handle, cacheLeaf, cacheNonLeaf);
    tcbdbsetxmsiz(_handle, memory); /* 内存缓存大小 */


    if (!tcbdbopen(_handle, (id + ".db").c_str(), BDBOWRITER | BDBOCREAT))
    {
        throw std::runtime_error(tcbdberrmsg(tcbdbecode(_handle)));
    }

    //tail
    {
        auto key_size = tcbdbget2(_handle, KEY_TAIL.c_str());
        if (key_size)
        {
            _tail = atoi(key_size);

            free(key_size);
        }
    }
}

TCBDataDb::~TCBDataDb()
{
    tcbdbsync(_handle);
    tcbdbclose(_handle);
    tcbdbdel(_handle);
}


bool TCBDataDb::GetNext(std::string &value)
{
    if (Get(value, _index))
    {
        ++_index;
        return true;
    }
    return false;
}

bool TCBDataDb::GetBack(std::string &value)
{
    if (Get(value, _index))
    {
        --_index;
        return true;
    }
    return false;
}

bool TCBDataDb::Get(std::string &value, std::size_t index)
{
    if (0 <= index && index <= _tail)
    {
        char *buffer = nullptr;
        auto key = std::to_string(index);

        if (buffer = tcbdbget2(_handle, key.c_str()))
        {
            value = std::move(std::string(buffer, tcbdbvsiz2(_handle, key.c_str())));

            free(buffer);

            return true;
        }
    }

    return false;
}

bool TCBDataDb::Put(const char *buffer, std::size_t size)
{
    auto key = std::to_string(_tail);

    if (tcbdbput(_handle, key.c_str(), key.size(), buffer, size))
    {
        auto value = std::to_string(++_tail);

        tcbdbput(_handle, KEY_TAIL.c_str(), KEY_TAIL.size(), value.c_str(), value.size());

        return true;
    }

    return false;
}

const char *TCBDataDb::GetErrorMsg()
{
    return tcbdberrmsg(tcbdbecode(_handle));
}

void TCBDataDb::Sync()
{
    tcbdbsync(_handle);
}

std::size_t TCBDataDb::Size()
{
    return _tail;
}

