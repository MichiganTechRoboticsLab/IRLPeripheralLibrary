#define TEST 1
#include <iostream>
#include <Device/Hokuyo.hpp>
#include <Device/VN200.hpp>
#include <vector>
#include <unistd.h>
#include <iomanip>

#if TEST == 1
bool setCom(IRL::VN200& vn200)
{
    bool ret = false;
    std::string port = "/dev/ttyUSB0";
    std::cout  << "COM PORT: " << port << " ";

    if((ret = vn200.setSetting("com", port)))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }

    return ret;
}

bool setBuad(IRL::VN200& vn200)
{
    bool ret = false;
    std::cout << "BUADRATE: 115200 ";

    if((ret = vn200.setSetting("buad", "115200")))
    {
        std::cout << "SET" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }
    return ret;
}

void receiveData(void* sender, VnDeviceCompositeData* data)
{
    static int count = 1;
    static VnVector3 initAccel = { 0,0,0};
    if((count) == 1)
        initAccel = data->linearAccelBody;
    std::cout << std::setprecision(9)
              << std::showpoint
              << std::showpos
              << std::fixed
              << data->linearAccelBody.c0 - initAccel.c0 << "  "
              << data->linearAccelBody.c1 - initAccel.c1 << "  "
              << data->linearAccelBody.c2 - initAccel.c2 << "  "
              << data->ypr.yaw << "  "
              << data->ypr.pitch << "  "
              << data->ypr.roll << std::endl;
    count++;
}

void setSettings(IRL::VN200& vn200)
{
    if(vn200.setSetting("reset", ""))
        std::cout << "VectorNav reset" << std::endl;
    vn200.setSetting("g1yawpitchroll", "1");
    vn200.setSetting("g3accel", "1");
    vn200.setSetting("g5linearaccelbody", "1");
    vn200.setSetting("bindiv", "50");
    vn200.setAsyncCallBack(receiveData);
    vn200.setSetting("callback", "");

    while(!vn200.setSetting("async", "0"));

    IRL::IMUFilterConfig config = {0,4,4,4,0,0,3,3,3,0 } ;
    vn200.setIMUFilterConfig(config);
    if(!vn200.setSetting("setbin", ""))
    {
       std::cerr << "FAILED TO START BINARY" << std::endl;
    }
}

#else

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

#endif

int main(int argc, char* argv[])
{
    IRL::Hokuyo hokuyo;
    IRL::VN200 vn200;
    std::cout << "Checking settings: \n" <<
              "------------------" << std::endl;
#if TEST == 0
    setIP(hokuyo);
    setPort(hokuyo);
    setType(hokuyo);
    setConnection(hokuyo);
    std::cout << hokuyo.getSetting("ip") << std::endl;
    std::cout << hokuyo.getSetting("port") << std::endl;
    std::cout << hokuyo.getSetting("type") << std::endl;
    std::cout << hokuyo.getSetting("connection") << std::endl;
    
    if(hokuyo.setup() && hokuyo.startMeasurement())
    {
        int loop_count = 10;
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
#else
    setCom(vn200);
    setBuad(vn200);
    if(!vn200.setup())
    {
        std::cerr << "FAILED TO SETUP VECTORNAV" << std::endl;
        return 1;
    }
    std::cout << "Connected to VectorNav ... Reseting" << std::endl;
    setSettings(vn200);
    int count = 0;
    while(1)
    {
        count++;
        sleep(1);
        //std::cout << count << " seconds" << std::endl;
    }
#endif
}
