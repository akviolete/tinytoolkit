#ifndef SOFTWARE_LIST_H
#define SOFTWARE_LIST_H

#include <vector>
#include <iostream>

typedef struct nvrservice_head_tracking_data
{
    float translation[3];       //x,y,z--for translation
    float rotation[4];          //w,x,y,z--for roattion
    float velocity[3];
    float angle_velocity[3];
    float pos_quality;
    float acc[3];
    float gyro[3];

    int32_t slam_state;

    uint64_t timestamp_ns;
} nvrservice_head_tracking_data;


class TwsLinkList
{
public:
    typedef struct LinkListNode
    {
        nvrservice_head_tracking_data _data{};

        LinkListNode *_next{nullptr};
        LinkListNode *_last{nullptr};
        std::vector<LinkListNode *> _currArray{};
    } LinkListNode;
public:
    TwsLinkList() = delete;

    TwsLinkList(uint32_t size); /// 2^size

    ~TwsLinkList();

public:

    uint32_t Size();

    LinkListNode *GetCurrLinkList();

    inline void Push(const nvrservice_head_tracking_data &data);

    /**
     * ts   时间戳
     * data 返回数据
     * @return 0 ok,1 插值 2 左边界 3右边界
     * */
    int Select(const uint64_t ts, nvrservice_head_tracking_data &data);

private:
    void Creat();

    void Destroy();

    int BinSearch(const std::vector<LinkListNode *> &Array,
                  const uint32_t size, const uint64_t ts,
                  nvrservice_head_tracking_data &data);

private:
    uint64_t _rPos{0};
    uint64_t _wPos{0};
    uint64_t _size{0};
    LinkListNode *_wLinkList{nullptr};
    LinkListNode *_rLinkList{nullptr};
};

#endif //SOFTWARE_LIST_H
