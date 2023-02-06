#include <iostream>
#include <yaml-cpp/yaml.h>

#include "handle.h"
#include "server/server.h"
#include "client/client.h"
#include "pangolin_viewer/slamViewer.h"

Handle::Handle(const std::string &yamlPath)
{
    YAML::Node nodeData;

    try
    {
        nodeData = YAML::LoadFile(yamlPath);
    }
    catch (...)
    {
        throw std::runtime_error("Invalid Yaml Parameter");
    }

    _node = std::move(nodeData);
}


void Handle::Start()
{
    auto port = _node["SocketServer.port"].as<int>(8888);
    auto size = _node["SocketServer.size"].as<int>(1024 * 1024 * 4);
    auto host = _node["SocketServer.host"].as<std::string>("0.0.0.0");

    /**
     * Pangolin Handle
     * */
    pangolin_viewer::viewer viewer(_node);

    auto serRecv = [&](std::size_t protocol, const char *data, std::size_t len)
    {
        /**
         * protocol     协议号
         * data         数据
         * len          数据长度
         * */
        viewer.RunData(protocol, data, len);
    };

    /**
     * Socket Server Handle,异步通信
     * serRecv  : 接收到client消息后的回调函数
     * Launch   : 启动服务器
     * */
    TCPServer tcpServer(serRecv);
    tcpServer.Launch(host, port, size);

    /**
     * Pangolin Handle 绘图循环入口
     * */
    viewer.run();
}