#include <Device/VN200.hpp>
#include <GPS/GPS.hpp>
#include <IMU/IMU.hpp>

namespace IRL
{
    VN200::~VN200()
    {

    }

    void VN200::setup()
    {

    }

    void VN200::cleanup()
    {

    }


    bool VN200::setSetting(const std::string &key, const std::string &value)
    {
        return false;
    }

    const std::string VN200::getSetting(const std::string &key)
    {
        return std::string("");
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
        return GPS::Data((uint16_t)0);
    }

    GPS::Data VN200::getPos()
    {
        return GPS::Data(0.0,0.0,0.0,0.0,0.0,0.0);
    }

    GPS::Data VN200::getGPSVelocity()
    {
        return GPS::Data(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, true);
    }

    IMU::Data VN200::getAcceleration()
    {
        IMU::Data data(IMUDataType::ACCEL);
        data.acceleration.v1 = 0;
        data.acceleration.v2 = 0;
        data.acceleration.v3 = 0;
        return data;
    }

    IMU::Data VN200::getGyro()
    {
        IMU::Data data(IMUDataType::GYRO);
        data.gyro.v1 = 0;
        data.gyro.v2 = 0;
        data.gyro.v3 = 0;
        return data;
    }

    IMU::Data VN200::getMagnetic()
    {
        IMU::Data data(IMUDataType::MAG);
        data.magnetic.v1 = 0;
        data.magnetic.v2 = 0;
        data.magnetic.v3 = 0;
        return data;
    }

    IMU::Data VN200::getPressure()
    {
        IMU::Data data(IMUDataType::PRESSURE);
        data.pressure = 0.0;
        return data;
    }

    IMU::Data VN200::getTemp()
    {
        IMU::Data data(IMUDataType::TEMP);
        data.temperature = 0.0;
        return data;
    }

}
