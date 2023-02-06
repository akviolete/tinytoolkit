
#ifndef __MAIN__H__
#define __MAIN__H__

#include "tcp.h"

void StartApp()
{

}


void Terminate(int32_t)
{

    exit(0);
}

//打印栈错误信息
void PrintError(int32_t signalNo)
{
    for (auto &iter : tinyToolkit::StackTrace::Content(signalNo))
    {
        std::cerr << iter << std::endl;
    }

    exit(0);
}

#endif // __EXAMPLE__NET__MAIN__H__
