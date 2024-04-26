#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp()
{
    std::cout<<"format: command -i <configfile>" << std::endl;
}

//argc: argument count, 记录了命令行参数的个数(包括命令本身)
//argv: argument vector, 记录了命令行参数的具体内容
//optstring: 作为getopt()的第三个参数，用于规定合法选项(option)以及选项是否带参数(argument)。
//一般为合法选项字母构成的字符串，如果字母后面带上冒号:就说明该选项必须有参数。
//如"ht:"说明有两个选项-h和-t且后者(-t)必须带有参数(如-t 60)。

//?: 一般情况下，遇到非法选项或者参数缺失都会返回?。如果需要区分这两种错误，
//可以在optstring的开头加上:，如:ht: , 这样参数缺失就返回:，非法选项就返回?。

void MprpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;//optarg: 如果合法选项带有参数，那么对应的参数，赋值给optarg
            break;
        case '?':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件了 rpcserver_ip=  rpcserver_port=   zookeeper_ip=  zookepper_port=
    m_config.LoadConfigFile(config_file.c_str());

    // std::cout << "rpcserverip:" << m_config.Load("rpcserverip") << std::endl;
    // std::cout << "rpcserverport:" << m_config.Load("rpcserverport") << std::endl;
    // std::cout << "zookeeperip:" << m_config.Load("zookeeperip") << std::endl;
    // std::cout << "zookeeperport:" << m_config.Load("zookeeperport") << std::endl;
}

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig& MprpcApplication::GetConfig()
{
    return m_config;
}