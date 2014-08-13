#include <Device/Hokuyo.hpp>
#include <Util/util.hpp>

#define SETTINGS_CONTAIN(x) (m_settings.find(x) != m_settings.end())

namespace IRL
{
    void Hokuyo::init()
    {
        // Set up String Translation for settings
        {
            //Device
            m_trans["devicename"] = hSetting::hevDeviceName;
            m_trans["ip"] = hSetting::hevDeviceName;
            m_trans["device"] = hSetting::hevDeviceName;

            //BuadRate
            m_trans["buadrate"] = hSetting::hevBuadRate;
            m_trans["port"] = hSetting::hevBuadRate;

            //Connection
            m_trans["connection"] = hSetting::hevConnection;

            //Laser
            m_trans["laser"] = hSetting::hevLaser;

            //Type
            m_trans["type"] = hSetting::hevType;

            //Timeout
            m_trans["timeout"] = hSetting::hevTimeOut;

            //Reboot
            m_trans["reboot"] = hSetting::hevReboot;

            //Sleep
            m_trans["sleep"] = hSetting::hevSleep;

            //Wakeup
            m_trans["wake"] = hSetting::hevWakeUp;
            m_trans["wakeup"] = hSetting::hevWakeUp;

            //Stable
            m_trans["stable"] = hSetting::hevStable;
        }
    }

    Hokuyo::~Hokuyo()
    {
        cleanup();
    }

    bool Hokuyo::setup()
    {
        bool isReady = SETTINGS_CONTAIN(hSetting::hevConnection) &&
                       SETTINGS_CONTAIN(hSetting::hevBuadRate) &&
                       SETTINGS_CONTAIN(hSetting::hevConnection);

        long buad = std::stol(m_settings[hSetting::hevBuadRate]);
        std::string connection = m_settings[hSetting::hevConnection];
        bool isSerial = (Util::lowercase(connection) == "serial");
        qrk::Lidar::connection_type_t type = isSerial
                                             ? qrk::Lidar::Serial
                                             : qrk::Lidar::Ethernet;

        isReady = isReady && m_urg.open(
                      m_settings[hSetting::hevDeviceName].c_str(),
                      buad, type);

        return isReady;
    }

    bool Hokuyo::cleanup()
    {
        if(_started) stopMeasurement();

        if(m_urg.is_open()) m_urg.close();

        return true;
    }

    bool Hokuyo::startMeasurement()
    {
        bool isOpen = m_urg.is_open() && SETTINGS_CONTAIN(hSetting::hevType);

        if(isOpen)
        {
            std::string meas = Util::lowercase(m_settings[hSetting::hevType]);

            qrk::Lidar::measurement_type_t type = qrk::Lidar::Distance;

            if(meas == "distance_intensity")
            {
                type = qrk::Lidar::Distance_intensity;
            }
            else if(meas == "multiecho")
            {
                type = qrk::Lidar::Multiecho;
            }
            else if(meas == "multiecho_intensity")
            {
                type = qrk::Lidar::Multiecho_intensity;
            }

            isOpen = isOpen && m_urg.start_measurement(type);
            _started = true;
        }

        return isOpen;
    }

    void Hokuyo::stopMeasurement()
    {
        m_urg.stop_measurement();
    }

    bool Hokuyo::setSetting(const std::string &key, const std::string &value)
    {
        hSetting trans = m_trans[Util::lowercase(key)];

        switch(trans)
        {
            case hSetting::hevDeviceName:
            {
                m_settings[trans] = value;
                break;
            }

            case hSetting::hevConnection:
            {
                if(Util::lowercase(value) == "serial"
                   || Util::lowercase(value) == "ethernet"
                   || Util::lowercase(value) == "ip")
                {
                    m_settings[trans] = value;
                }
                else
                {
                    return false;
                }

                break;
            }

            case hSetting::hevBuadRate:
            {
                if(Util::isInt(value))
                    m_settings[trans] = value;
                else
                    return false;

                break;
            }

            case hSetting::hevLaser:
            {
                if(!_started) return false;

                if(Util::lowercase(value) == "on")
                {
                    m_urg.laser_on();
                }
                else if(Util::lowercase(value) == "off")
                {
                    m_urg.laser_off();
                }
                else
                    return false;

                break;
            }

            case hSetting::hevType:
            {
                if(Util::lowercase(value) == "distance")
                    m_settings[trans] = value;
                else
                    return false;

                break;
            }

            case hSetting::hevTimeOut:
            {
                if(Util::isInt(value))
                {
                    m_settings[trans] = value;
                }
                else
                {
                    return false;
                }
            }

            case hSetting::hevReboot:
            {
                if(!_started) return false;

                m_urg.reboot();
            }

            case hSetting::hevSleep:
            {
                if(!_started) return false;

                m_urg.sleep();
            }

            case hSetting::hevWakeUp:
            {
                if(!_started) return false;

                m_urg.wakeup();
            }

            default:
                return false;
        }

        return true;
    }


    const std::string Hokuyo::getSetting(const std::string &key)
    {
        hSetting trans = m_trans[Util::lowercase(key)];
        std::string retStr;

        switch(trans)
        {
            case hSetting::hevTimeOut:
            case hSetting::hevType:
            case hSetting::hevBuadRate:
            case hSetting::hevConnection:
            case hSetting::hevDeviceName:
            {
                retStr = m_settings[trans];
                break;
            }

            default:
                retStr = "";
        }

        return retStr;
    }

    bool Hokuyo::getMeasurement(std::vector<long>& data,long* timestamp)
    {
        std::string meas = Util::lowercase(m_settings[hSetting::hevType]);

        if(_started)
        {
            if(meas == "distance")
            {
                return m_urg.get_distance(data,timestamp);
            }
            else if(meas == "multiecho")
            {
                return m_urg.get_multiecho(data, timestamp);
            }
            else if(meas == "distance_intensity" || meas == "multiecho_intensity")
            {
                std::vector< unsigned short> dummy_int;
                return getIntensity(data,dummy_int,timestamp);
            }
        }

        return false;
    }

    bool Hokuyo::getIntensity(std::vector<long>& data,
                              std::vector< unsigned short> & intensity,
                              long* timestamp)
    {
        std::string meas = Util::lowercase(m_settings[hSetting::hevType]);

        if(_started)
        {
            if(meas == "distance")
            {
                return m_urg.get_distance_intensity(data,intensity, timestamp);
            }
            else if(meas == "multiecho")
            {
                return m_urg.get_multiecho_intensity(data, intensity, timestamp);
            }
            else if(meas == "distance" || meas == "multiecho")
            {
                return getMeasurement(data, timestamp);
            }
        }
        return false;
    }
}
