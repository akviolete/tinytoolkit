#ifndef __HANDLE__H__
#define __HANDLE__H__

#include <string>
#include <yaml-cpp/yaml.h>

class Handle
{
public:
    Handle(const std::string &yamlPath);

    ~Handle() = default;

public:
    void Start();

private:
    YAML::Node _node;
};


#endif //__HANDLE__H__