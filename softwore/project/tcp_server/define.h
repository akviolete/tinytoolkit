#ifndef __DEFINE__H__
#define __DEFINE__H__

#include "common.h"

#define KEY_SN_CODE_STATUS_SQL_OK 0 //执行成功
#define KEY_SN_CODE_STATUS_SQL_NO_CONNECT 1 //数据库无连接
#define KEY_SN_CODE_STATUS_SQL_CONNECT_STATEMENT_ERROR 2  //语句错误
#define KEY_SN_CODE_STATUS_SQL_CONNECT_STATEMENT_NO_EFFECT 3  //无影响
#define KEY_SN_CODE_STATUS_SQL_CONNECT_STATEMENT_DO_NOTHING 4  //不做任何事情

#define SQL_RESET 0
#define SQL_SELECT 1
#define SQL_UPDATE 2


typedef struct
{
    int protocl;  // select update reset
    char pid[32];
    char key[32];
    char uuid[32];
} SN_CODE;


typedef struct
{

    int errNo;

    SN_CODE snCode;

    std::string key;

} KEY_SN_CODE;


typedef struct
{

    struct
    {
        int port; //数据库相关信息
        std::string host;
        std::string user;
        std::string name;
        std::string pass;
    } sql;

} CONFIG_INFO;

#endif //__DEFINE__H__