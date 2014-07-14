#ifndef GPS_HPP
#define GPS_HPP

#include <Util/util.hpp>
#include <string>
#include <cstdint>

namespace IRL
{

enum GPSDataType
{
    FIX,
    TIME,
    SAT,
    POS,
    VEL
};

class GPS
{
public:
    struct Data
    {
        GPSDataType tyope;
        union 
        {
            bool fix;
            struct time
            {
                uint64_t second;
                uint64_t week;
            };
            uint16_t sat;
            struct pos
            {
                triple<double> lla;
                triple<double> ecef;
            };
            struct vel
            {
                triple<double> ecef;
                triple<double> ned;
            };
        };

    };


    virtual ~GPS() {};
    virtual GPS::Data hasGPSFix() = 0;
    virtual GPS::Data getGPSTime() = 0;
    virtual GPS::Data getNumOfSat() = 0;
    virtual GPS::Data getPos() = 0;
    virtual GPS::Data getGPSVelocity() = 0;
    virtual void setSetting(const std::string& key, const std::string& value) = 0;
    virtual const std::string& getSetting(const std::string& key) = 0;
};
}

#endif // GPS_HPP