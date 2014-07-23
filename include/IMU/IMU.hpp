#ifndef IMU_HPP
#define IMU_HPP

#include <Util/util.hpp>
#include <string>

namespace IRL
{

    enum class IMUDataType
    {
        MAG,
        ACCEL,
        GYRO,
        TEMP,
        PRESSURE,
        UNKNOWN
    };



    class IMU
    {
    public:
        struct Data
        {
            IMUDataType type;
            union
            {
                Util::triple<float> magnetic;
                Util::triple<float> acceleration;
                Util::triple<float> gyro;
                float temperature;
                float pressure;
            };
            Data() : type(IMUDataType::UNKNOWN) {}
            Data(IMUDataType _type) : type(_type) {}
        };

        virtual ~IMU() {}
        virtual void setup(void) = 0;
        virtual void cleanup(void) = 0;
        virtual IMU::Data getGyro(void) = 0;
        virtual IMU::Data getAcceleration(void) = 0;
        virtual IMU::Data getMagnetic(void) = 0;
        virtual IMU::Data getTemp(void) = 0;
        virtual IMU::Data getPressure(void) = 0;
        virtual bool setSetting(const std::string& key, const std::string& value) = 0;
        virtual const std::string getSetting(const std::string& key) = 0;
    };
}

#endif // IMU_HPP
