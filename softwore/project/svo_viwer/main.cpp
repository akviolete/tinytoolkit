#include "handle.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (1 == argc)
    {
        std::cout << "Please Input Yaml Config File Path:" << std::endl;
        std::cout << "Ex:./bin/svo_viewer  config/config.yaml" << std::endl;

        return 0;
    }

    Handle handle(argv[1]);

    handle.Start();

    return 0;
}
