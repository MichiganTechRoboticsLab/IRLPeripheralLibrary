#ifndef GPS_HPP
#define GPS_HPP

#include <Util/util.hpp>
#include <string>
#include <cstdint>

namespace IRL
{

    enum class GPSDataType
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
                uint8_t fix;
                struct
                {
                    uint64_t second;
                    uint64_t week;
                } time;
                uint16_t sat;
                struct
                {
                    Util::triple<double> lla;
                    Util::triple<double> ecef;
                } pos;
                struct
                {
                    Util::triple<double> ecef;
                    Util::triple<double> ned;
                } vel;
            };

            Data() : type(GPSDataType::UNKNOWN) {}

            Data(uint8_t _fix)
            {
                type = GPSDataType::FIX;
                fix = _fix;
            }

            Data(uint64_t _second, uint64_t _week)
            {
                type = GPSDataType::TIME;
                time.second = _second;
                time.week = _week;
            }

            Data(uint16_t _sat)
            {
                type = GPSDataType::SAT;
                sat = _sat;
            }

            Data(double v1, double v2, double v3,
                 double x1, double x2, double x3, bool _vel = false)
            {
                if(_vel)
                {
                    type = GPSDataType::VEL;
                    vel.ned.v1 = v1;
                    vel.ned.v2 = v2;
                    vel.ned.v3 = v3;
                    vel.ecef.v1 = x1;
                    vel.ecef.v2 = x2;
                    vel.ecef.v3 = x3;
                }
                else
                {
                    type = GPSDataType::POS;
                    pos.lla.v1 = v1;
                    pos.lla.v2 = v2;
                    pos.lla.v3 = v3;
                    pos.ecef.v1 = x1;
                    pos.ecef.v2 = x2;
                    pos.ecef.v3 = x3;
                }
            }
        };

        virtual ~GPS() {}
        virtual bool setup(void) = 0;
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
