
#include "main.h"

void ParseOption(int32_t argc, char const **argv)
{
    sOptionManager.DefineVersion(tinyToolkit::Application::CompileTimeString());

    sOptionManager.DefineArg("port", "port", "8888", "");
    sOptionManager.DefineArg("host", "host", "0.0.0.0", "");

    sOptionManager.Parse(argc, argv);
}

int main(int32_t argc, char const **argv)
{

    tinyToolkit::Signal::RegisterIgnore();
    tinyToolkit::Signal::RegisterTerminate(Terminate);
    tinyToolkit::Signal::RegisterException(PrintError);

    ParseOption(argc, argv);

    auto callBack1 = [&](std::size_t protocl, const std::string &key, const char *data, std::size_t len)
    {
        std::cout << "1111111111111" << std::endl;
    };

    auto callBack2 = [&](std::size_t protocl, const std::string &key, const char *data, std::size_t len)
    {
        std::cout << "2222222222222" << std::endl;
    };


    TCPServer tcpServer1;

    tcpServer1.SetSessionCallBack(callBack1);

    tcpServer1.Launch("0.0.0.0", 8888, 1024 * 1024 * 4);


    TCPServer tcpServer2;

    tcpServer2.SetSessionCallBack(callBack2);

    tcpServer2.Launch("0.0.0.0", 8889, 1024 * 1024 * 4);


    sleep(1000);

    return 0;
}
