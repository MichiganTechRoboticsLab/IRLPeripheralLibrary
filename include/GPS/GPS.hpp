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
    VEL,
    UNKNOWN
};

class GPS
{
public:
    struct Data
    {

        GPSDataType type;
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

        Data() : type(GPSDataType::UNKNOWN) {}

        Data(bool _fix)
        {
            this->type = GPSDataType::FIX;
            this->fix = _fix;
        }

        Data(uint64_t _second, uint64_t _week)
        {
            this->type = GPSDataType::TIME;
            this->time.second = _second;
            this->time.week = _week;
        }

        Data(uint16_t _sat)
        {
            this->type = GPSDataType::SAT;
            this->sat = _sat;
        }

        Data(double v1, double v2, double v3,
             double x1, double x2, double x3, bool vel = false)
        {
            if(vel)
            {
                this->type = GPSDataType::VEL;
                this->vel.ned.v1 = v1;
                this->vel.ned.v2 = v2;
                this->vel.ned.v3 = v3;
                this->vel.ecef.v1 = x1;
                this->vel.ecef.v2 = x2;
                this->vel.ecef.v3 = x3;
            }
            else
            {
                this->type = GPSDataType::POS;
                this->pos.lla.v1 = v1;
                this->pos.lla.v2 = v2;
                this->pos.lla.v3 = v3;
                this->vel.ecef.v1 = x1;
                this->vel.ecef.v2 = x2;
                this->vel.ecef.v3 = x3;
            }
        }
    };

    virtual ~GPS() {}
    virtual void setup(void) = 0;
    virtual void cleanup(void) = 0;
    virtual GPS::Data hasGPSFix(void) = 0;
    virtual GPS::Data getGPSTime(void) = 0;
    virtual GPS::Data getNumOfSat(void) = 0;
    virtual GPS::Data getPos(void) = 0;
    virtual GPS::Data getGPSVelocity(void) = 0;
    virtual bool setSetting(const std::string& key, const std::string& value) = 0;
    virtual const std::string getSetting(const std::string& key) = 0;
};
}

#endif // GPS_HPP
