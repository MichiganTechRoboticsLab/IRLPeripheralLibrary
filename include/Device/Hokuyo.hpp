#ifndef HOKUYO_HPP
#define HOKUYO_HPP

#include <Lidar/Lidar.hpp>
#include <urg_cpp/Urg_driver.h>
#include <string>
#include <unordered_map>
#include <map>

namespace IRL
{
    class Hokuyo : public Lidar
    {

    private:
        enum class hSetting
        {
            hevUndefined,
            hevDeviceName,
            hevBuadRate,
            hevConnection,
            hevLaser,
            hevType,
            hevTimeOut,
            hevReboot,
            hevSleep,
            hevWakeUp,
            hevStable
        };

        std::unordered_map<std::string, hSetting> m_trans;

        std::map<hSetting,std::string> m_settings;

        qrk::Urg_driver m_urg;

        bool _started;

        void init(void);

    public:
        Hokuyo() : m_settings(), m_urg()
        {
            init();
        }

        ~Hokuyo();

        bool setup(void);

        bool cleanup(void);

        bool startMeasurement(void);

        void stopMeasurement(void);
        //         const void* getDevice(void);
        bool setSetting(const std::string& key, const std::string& value);

        const std::string getSetting(const std::string& key);

        bool getMeasurement(std::vector<long>& data,long* timestamp = NULL);

        bool getIntensity(std::vector<long>& data,
                          std::vector< unsigned short> & intensity,
                          long* timestamp = NULL);
    };
}

#endif // HOKUYO_HPP
