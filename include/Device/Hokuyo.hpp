#ifndef HOKUYO_HPP
#define HOKUYO_HPP

#include <Lidar/Lidar.hpp>
#include <urg_cpp/Urg_driver.h>
#include <string>

namespace IRL
{
class Hokuyo : public Lidar
{

private:
    std::unordered_map<std::string,std::string> m_settings;
    qrk::Urg_driver m_urg;
public:
    Hokuyo() : m_settings(), m_urg();
    ~Hokuyo();
    bool setup(void);
    bool cleanup(void);
    bool startMeasurement(void);
    void stopMeasurement(void);
    //         const void* getDevice(void);
    void bool setSetting(const std::string& key, const std::string& value);
    std::string& getSetting(const std::string& key);
};
}

#endif // HOKUYO_HPP