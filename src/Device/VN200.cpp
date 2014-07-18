#include <Device/VN200.hpp>
#include <GPS/GPS.hpp>
#include <IMU/IMU.hpp>

namespace IRL {
    VN200::~VN200()
    {

    }

    GPS::Data VN200::hasGPSFix()
    {
        return GPS::Data(false);
    }

    GPS::Data VN200::getGPSTime()
    {
        return GPS::Data(0,0);
    }

    GPS::Data VN200::getNumOfSat()
    {
        return GPS::Data(0);
    }

    GPS::Data VN200::getPos()
    {
        return GPS::Data(0.0,0.0,0.0,0.0,0.0,0.0);
    }

    GPS::Data VN200::getGPSVelocity()
}
