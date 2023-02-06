#include <cstring>
#include <iostream>

#include "twslinklist.h"

#define MIN_BUFFER_SIZE 32
#define MAX_BUFFER_SIZE 4096

#define LIKELY(x)    __builtin_expect(!!(x), 1)
#define UNLIKELY(x)  __builtin_expect(!!(x), 0)

TwsLinkList::TwsLinkList(uint32_t size) : _rPos(0), _wPos(0), _size(0)
{
    _size = 2 << size;
    _size = _size > MAX_BUFFER_SIZE ? MAX_BUFFER_SIZE : _size;
    _size = _size < MIN_BUFFER_SIZE ? MIN_BUFFER_SIZE : _size;

    Creat();
}

TwsLinkList::~TwsLinkList()
{
    Destroy();
}

void TwsLinkList::Creat()
{
    ///初始化双向环形链表
    {
        _wLinkList = new LinkListNode;

        auto tempNode = _wLinkList;
        auto tempNodeLast = _wLinkList;

        for (int i = 0; i < _size - 1; i++)
        {
            auto *node = new LinkListNode;

            tempNode->_next = node;

            tempNode = tempNode->_next;

            tempNode->_last = tempNodeLast;

            tempNodeLast = tempNodeLast->_next;
        }

        tempNode->_next = _wLinkList;
        _wLinkList->_last = tempNodeLast;
    }

    ///初始各个节点顺序指针
    {
        auto tmpI = _wLinkList;
        for (int i = 0; i < _size; ++i)
        {
            ///数据填充
            {
                memset(&tmpI->_data, 0, sizeof(nvrservice_head_tracking_data));
                tmpI->_data.timestamp_ns = i;
            }

            auto tmpJ = tmpI;
            for (int j = 0; j < _size; ++j)
            {
                tmpI->_currArray.push_back(tmpJ);

                tmpJ = tmpJ->_next;
            }
            tmpI = tmpI->_next;
        }
    }
}

void TwsLinkList::Destroy()
{
    for (int i = 0; i < _size; ++i)
    {
        auto node = _wLinkList;

        _wLinkList = _wLinkList->_next;

        delete node;

        node = nullptr;
    }
}


inline void TwsLinkList::Push(const nvrservice_head_tracking_data &data)
{
    memcpy(&_wLinkList->_data, &data, sizeof(nvrservice_head_tracking_data));

    _wLinkList = _wLinkList->_next;

    ++_wPos;
}

uint32_t TwsLinkList::Size()
{
    return _size;
}

TwsLinkList::LinkListNode *TwsLinkList::GetCurrLinkList()
{
    return _wLinkList;
}

/**
 * ts   时间戳
 * data 返回数据
 * @return 0 ==,1 插值 2 左边界 3右边界 4无有效数据
 * */
int TwsLinkList::Select(const uint64_t ts, nvrservice_head_tracking_data &data)
{
    auto actualSub = _wPos - _rPos;

    if (UNLIKELY(!actualSub))
    {
        std::cout << "there is no Valid data" << std::endl;

        memset(&data, 0, sizeof(nvrservice_head_tracking_data));

        data.rotation[0] = 1;

        return 4;
    }

    if (actualSub > _size)
    {
        _rLinkList = _rLinkList->_currArray[actualSub - _size];

        _rPos = _wPos - _size;

        actualSub = _size;
    }


    auto find = BinSearch(_rLinkList->_currArray, actualSub, ts, data);

    if (find != -1)
    {
        _rPos += find;
        _rLinkList = _rLinkList->_currArray[find];
    }

    return 0;
}

/**
 * Array    二分查找数组
 * size     查找有效距离
 * ts       时间戳
 * data     返回数据
 * @return 0 ==,1 插值 2 左边界 3右边界 4无有效数据
 * */
int TwsLinkList::BinSearch(const std::vector<LinkListNode *> &Array,
                           const uint32_t size, const uint64_t ts,
                           nvrservice_head_tracking_data &data)
{
    if (ts < Array[0]->_data.timestamp_ns)
    {
        memcpy(&data, &Array[0]->_data, sizeof(nvrservice_head_tracking_data));

        return 2;
    }
    if (ts > Array[size - 1]->_data.timestamp_ns)
    {
        memcpy(&data, &Array[size - 1]->_data, sizeof(nvrservice_head_tracking_data));

        return 3;
    }

    uint32_t start = 0, end = size - 1;

    while (start <= end)
    {
        auto middle = start + ((end - start) >> 1);

        auto *value = Array[middle];

        if (ts < value->_data.timestamp_ns)
        {
            end = middle - 1;

            continue;
        }

        if (ts == value->_data.timestamp_ns)
        {
            /// 找到数据
            std::cout << "SEARCH:" << '\t' << middle << "\t" << Array[middle] << std::endl;

            return middle;
        }

        if (ts < value->_next->_data.timestamp_ns) // Array[middle+1]
        {
            /// 插值计算
            std::cout << "SEARCH:" << '\t' << middle << "\t" << Array[middle] << "," << Array[middle + 1]
                      << std::endl;

            return middle;
        }

        start = middle + 1;
    }


    return 0;
}