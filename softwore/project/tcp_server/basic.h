#ifndef __BASIC__H__
#define __BASIC__H__

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

public:
    ConfigList();

    ~ConfigList();

public:
};

#define sConfig ConfigList::Instance()

#endif
