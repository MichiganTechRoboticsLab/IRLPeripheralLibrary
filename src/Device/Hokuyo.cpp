#include <Device/Hokuyo.hpp>

namespace IRL
{
Hokuyo::~Hokuyo()
{

}

bool Hokuyo::setup()
{
    return false;
}

bool Hokuyo::cleanup()
{
    return false;
}

bool Hokuyo::startMeasurement()
{
    return true;
}

void Hokuyo::stopMeasurement()
{

}

bool Hokuyo::setSetting(const std::string &key, const std::string &value)
{
    return false;
}

const std::string Hokuyo::getSetting(const std::string &key)
{
    return "";
}

}
