#include <atomic>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "twslinklist.h"
#include <pthread.h>
#include "ringbuf.h"




int main(int argc, const char **argv)
{
    std::cout << FindPowerExpTwoDown(atoi(argv[1])) << std::endl;

    std::cout << FindPowerExpTwoUp(atoi(argv[1])) << std::endl;

    return 0;
}

