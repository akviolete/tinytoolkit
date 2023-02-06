
#include "main.h"

void ParseOption(int32_t argc, char const **argv)
{
    sOptionManager.DefineVersion(tinyToolkit::Application::CompileTimeString());

    sOptionManager.DefineArg("port", "port", "8888", "");
    sOptionManager.DefineArg("host", "host", "127.0.0.1", "");

    sOptionManager.Parse(argc, argv);
}


int main(int32_t argc, char const **argv)
{
    tinyToolkit::Signal::RegisterIgnore();
    tinyToolkit::Signal::RegisterTerminate(Terminate);
    tinyToolkit::Signal::RegisterException(PrintError);


    ParseOption(argc, argv);


    auto host = sOptionManager.Get("host");
    auto port = atoi(sOptionManager.Get("port").c_str());

    ConfigList::Instance();

    auto callBack1 = [](std::size_t protocl, const char *data, std::size_t len)
    {
        std::cout << len << std::endl;
        std::cout << protocl << std::endl;
        std::cout << data[0] << std::endl;
    };

    auto callBack2 = [](std::size_t protocl, const char *data, std::size_t len)
    {
        std::cout << len << std::endl;
        std::cout << protocl << std::endl;
        std::cout << data[0] << std::endl;
    };

    TCPSession _session1;

    _session1.SetSessionCallBack(callBack1);

    _session1.Launch("127.0.0.1", 8888, 1024 * 1024 * 4);


    sleep(3);

    TCPSession _session2;

    _session2.SetSessionCallBack(callBack2);

    _session2.Launch("127.0.0.1", 8889, 1024 * 1024 * 4);

    sleep(3);
    int index = 0;

    do
    {
        TINY_TOOLKIT_SLEEP_MS(1);
        std::cout << "111111111" << std::endl;

        _session1.OnSessionSend(0, "11111111");

        //sleep(3);

        std::cout << "2222222222" << std::endl;

        _session2.OnSessionSend(0, "22222222");

        //sleep(3);

    } while (1);

    std::cerr << "Exit App" << std::endl;

    return 0;
}
