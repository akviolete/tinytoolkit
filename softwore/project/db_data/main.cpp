#include <iostream>
#include "tcbdatadb.h"


int main()
{
    std::string idCard = "db";
    std::string value = "test";

    TCBDataDb dataDb(idCard);

    dataDb.Put(value.c_str(), value.size());
    dataDb.Put(value.c_str(), value.size());
    dataDb.Put(value.c_str(), value.size());
    dataDb.Put(value.c_str(), value.size());

    dataDb.Sync();

    std::cout << dataDb.Size() << std::endl;

    std::cout << dataDb.GetNext(value) << std::endl;
    std::cout << dataDb.GetNext(value) << std::endl;
    std::cout << dataDb.GetNext(value) << std::endl;
    std::cout << dataDb.GetNext(value) << std::endl;
    std::cout << dataDb.GetNext(value) << std::endl;
    std::cout << dataDb.GetNext(value) << std::endl;

    return 0;
}