#ifndef VN200_HPP
#define VN200_HPP

#include <GPS/GPS.hpp>
#include <IMU/IMU.hpp>
#include <map>
#include <unordered_map>

namespace IRL
{
    class VN200 : public GPS, public IMU
    {
    private:
        enum vSetting
        {

        };

        std::unordered_map<std::string, vSetting> m_trans;

        std::map<vSetting,std::string> m_settings;



    public:
        VN200() {}
        ~VN200();
        GPS::Data hasGPSFix(void);
        GPS::Data getGPSTime(void);
        GPS::Data getNumOfSat(void);
        GPS::Data getPos(void);
        GPS::Data getGPSVelocity(void);
        bool setSetting(const std::string& key, const std::string& value);
        const std::string getSetting(const std::string& key);
        void setup(void);
        void cleanup(void);
        IMU::Data getGyro(void);
        IMU::Data getAcceleration(void);
        IMU::Data getMagnetic(void);
        IMU::Data getTemp(void);
        IMU::Data getPressure(void);
    };
}
#endif // VN200_HPP
