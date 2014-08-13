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
        Lidar() {}
        virtual ~Lidar() {}
        virtual bool setup(void) = 0;
        virtual bool cleanup(void) = 0;
        virtual bool startMeasurement(void) = 0;
        virtual void stopMeasurement(void) = 0;

        virtual bool getMeasurement(std::vector<long>& data,long* timestamp = NULL) = 0;
        virtual bool getIntensity(std::vector<long>& data, std::vector< unsigned short> & intensity, long* timestamp = NULL) = 0;
        //         virtual const void* getDevice(void) = 0 ;
        virtual bool setSetting(const std::string& key, const std::string& value) = 0;
        virtual const std::string getSetting(const std::string& key) = 0;
    };
}

#endif // LIDAR_HPP
