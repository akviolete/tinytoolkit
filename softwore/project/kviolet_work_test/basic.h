#ifndef __BASIC__H__
#define __BASIC__H__

#include "klog.h"
#include "define.h"

#define sOptionManager tinyToolkit::OptionManager::Instance() //main 函数传入参数解析

class ConfigList
{
public:
    static ConfigList &Instance()
    {
        static ConfigList instance;

        return instance;
    }

private:
    ConfigList();

    ~ConfigList();

public:
    std::shared_ptr<std::string> _temp;
};

#define sConfig ConfigList::Instance()



#endif //__BASIC__H__


