#include <iostream>
#include <Device/Hokuyo.hpp>
#include <vector>

bool setIP(IRL::Hokuyo& hokuyo)
{
    bool ret = false;
    std::cout  << "IP: 192.168.0.10 ";

    if((ret = hokuyo.setSetting("IP", "192.168.0.10")))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }

    return ret;
}

bool setPort(IRL::Hokuyo& hokuyo)
{
    bool ret = false;
    std::cout << "PORT: 10940 ";

    if((ret = hokuyo.setSetting("PORT", "10940")))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }
    return ret;
}

bool setType(IRL::Hokuyo& hokuyo)
{
    bool ret = false;
    std::cout << "Type: distance ";

    if((ret = hokuyo.setSetting("type", "distance")))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }
    return ret;
}

bool setConnection(IRL::Hokuyo& hokuyo)
{
    bool ret = false;
    std::cout << "Connection: ip ";

    if((ret = hokuyo.setSetting("Connection", "ip")))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }
    return ret;
}


int main(int argc, char* argv[])
{
    IRL::Hokuyo hokuyo;

    std::cout << "Checking settings: \n" <<
              "------------------" << std::endl;
    setIP(hokuyo);
    setPort(hokuyo);
    setType(hokuyo);
    setConnection(hokuyo);
    std::cout << hokuyo.getSetting("ip") << std::endl;
    std::cout << hokuyo.getSetting("port") << std::endl;
    std::cout << hokuyo.getSetting("type") << std::endl;
    std::cout << hokuyo.getSetting("connection") << std::endl;
    int loop_count = 10;
    if(hokuyo.setup() && hokuyo.startMeasurement())
    {
        std::vector<long> data;
        for(int i = 0; i<loop_count;i++)
        {
            hokuyo.getMeasurement(data);
            std::cout << data.size() << std::endl;
            for( auto value : data)
            {
//                std::cout << value << std::endl;
            }
        }
    }
    else
        std::cout << "Failed to start" << std::endl;
}
