#ifndef LIDAR_HPP
#define LIDAR_HPP

#include <vector>
#include <memory>
#include <string>

namespace IRL
{
class Lidar
{
public:
    virtual ~Lidar() {}
    virtual bool setup(void) = 0;
    virtual bool cleanup(void) = 0;
    virtual bool startMeasurement(void) = 0;
    virtual void stopMeasurement(void) = 0;
    //         virtual const void* getDevice(void) = 0 ;
    virtual bool setSetting(const std::string& key, const std::string& value) = 0;
    virtual std::string& getSetting(const std::string& key) = 0;
};
}

#endif // LIDAR_HPP