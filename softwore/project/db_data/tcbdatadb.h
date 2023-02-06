#ifndef __TCB__DATA__DB__H__
#define __TCB__DATA__DB__H__

#include <string>
#include <tcbdb.h>

class TCBDataDb
{
public:
    TCBDataDb() = delete;

    /**
    *   缓存文件名
    *   index 起始播放地址
    **/
    TCBDataDb(const std::string &id, std::size_t index = 0);

    ~TCBDataDb();

public:
    /**
     * 异步刷新,更新到硬盘
     * */
    void Sync();

    /**
     * 缓存大小
     * return   大小
     * */
    std::size_t Size();

    /**
     * 获取当前索引数据,向下播放
     * value    传出参数
     * index    索引
     * return   成功/失败
     * */
    bool GetNext(std::string &value);

    /**
     * 获取当前索引数据,向上播放
     * value    传出参数
     * index    索引
     * return   成功/失败
     * */
    bool GetBack(std::string &value);

    /**
     * 保存数据
     * buffer    数据
     * size      大小
     * return   成功/失败
     * */
    bool Put(const char *buffer, std::size_t size);

    /**
     * 获取当前索引数据
     * value    传出参数
     * index    索引
     * return   成功/失败
     * */
    bool Get(std::string &value, std::size_t index);

    /**
     *    获取当前错误信息
     * return   error message
     * */
    const char *GetErrorMsg();

private:
    std::size_t _tail{0};

    std::size_t _index{0};

    TCBDB *_handle{nullptr};

    std::string errorMsg{};
};

#endif //__TCB__DATA__DB__H__