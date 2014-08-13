#ifndef VN200_HPP
#define VN200_HPP

#include <GPS/GPS.hpp>
#include <IMU/IMU.hpp>
#include <map>
#include <unordered_map>
#include <thirdparty/vectornav/vndevice.h>
#include <thirdparty/vectornav/vn200.h>
#include <cstring>
#include <cstdint>

namespace IRL
{
    struct IMUFilterConfig
    {
        uint16_t MagWindowSize;
        uint16_t AccelWindowSize;
        uint16_t GyroWindowSize;
        uint16_t TempWindowSize;
        uint16_t PresWindowSize;
        uint8_t MagFilterMode;
        uint8_t AccelFilterMode;
        uint8_t GyroFilterMode;
        uint8_t TempFilterMode;
        uint8_t PresFilterMode;
    };

    class VN200 : public GPS, public IMU
    {


    private:
        enum class vSetting
        {
            vnevUndefined,
            // Overall Settings
            vnevDeviceName,
            vnevBuadRate,
            vnevAsync,
            vnevAsyncType,
            vnevBinary,
            vnevCallBack,
            vnevReset,

            // Binary Settings
            vnevSetBin,
            vnevBinOutput,
            vnevBinDiv,

            // Binary Group 1: Common
            vnevG1TimeStartUp,
            vnevG1TimeGPS,
            vnevG1TimeSyncIn,
            vnevG1YawPitchRoll,
            vnevG1Quaternion,
            vnevG1AngularRate,
            vnevG1Position,
            vnevG1Velocity,
            vnevG1Accel,
            vnevG1IMU,
            vnevG1MagPres,
            vnevG1DeltaTheta,
            vnevG1InsStatus,
            vnevG1SyncInCnt,
            vnevG1TimeGpsPps,

            // Binary Group 2: Time
            vnevG2TimeStartUp,
            vnevG2TimeGPS,
            vnevG2GPSTow,
            vnevG2GPSWeek,
            vnevG2TimeSyncIn,
            vnevG2TimeGpsPps,
            vnevG2TimeUTC,
            vnevG2SyncInCnt,

            // Binary Group 3: IMU
            vnevG3IMUStatus,
            vnevG3UncompMag,
            vnevG3UncompAccel,
            vnevG3UncompGyro,
            vnevG3Temp,
            vnevG3Pres,
            vnevG3DeltaTheta,
            vnevG3DeltaVel,
            vnevG3Mag,
            vnevG3Accel,
            vnevG3AngularRate,
            vnevG3SensSat,

            // Binary Group 4: GPS
            vnevG4UTC,
            vnevG4Tow,
            vnevG4Week,
            vnevG4NumSats,
            vnevG4Fix,
            vnevG4PosLla,
            vnevG4PosEcef,
            vnevG4VelNed,
            vnevG4VelEcef,
            vnevG4PosU,
            vnevG4VelU,
            vnevG4TimeU,
            vnevG4SvStat,

            // Binary Group 5:  Attitude
            vnevG5VpeStatus,
            vnevG5YawPitchRoll,
            vnevG5Quaternion,
            vnevG5DCM,
            vnevG5MagNed,
            vnevG5AccelNed,
            vnevG5LinearAccelBody,
            vnevG5LinearAccelNed,
            vnevG5YprU,

            // Binary Group 6: INS
            vnevG6InsStatus,
            vnevG6PosLla,
            vnevG6PosEcef,
            vnevG6VelBody,
            vnevG6VelEcef,
            vnevG6MagEcef,
            vnevG6AccelEcef,
            vnevG6PosU,
            vnevG6VelU,

        };

        bool setSetting(const vSetting& key, const std::string& value);
        const std::string getSetting(const vSetting& key);

        static std::unordered_map<std::string, vSetting> translationTable;
        static std::map<vSetting, int16_t> binaryGroupTrans;

        std::map<vSetting,std::string> m_settings;
        VnDeviceNewAsyncDataReceivedListener m_callback = NULL;

        bool setAsyncOutput(int type);

        Vn200 m_vn200;
        int binaryGroup1, binaryGroup2, binaryGroup3, binaryGroup4,
            binaryGroup5, binaryGroup6;
        int binaryMessage, binaryDiv;

    public:

        VN200() :
            m_settings(),
            binaryGroup1(0),
            binaryGroup2(0),
            binaryGroup3(0),
            binaryGroup4(0),
            binaryGroup5(0),
            binaryGroup6(0),
            binaryMessage(1),
            binaryDiv(20)
        {
            memset(&m_vn200, 0, sizeof(Vn200));
        }

        ~VN200();

        GPS::Data hasGPSFix(void);

        GPS::Data getGPSTime(void);

        GPS::Data getNumOfSat(void);

        GPS::Data getPos(void);

        GPS::Data getGPSVelocity(void);

        bool setSetting(const std::string& key, const std::string& value);

        const std::string getSetting(const std::string& key);





        bool setup(void);

        void cleanup(void);

        IMU::Data getGyro(void);

        IMU::Data getAcceleration(void);

        IMU::Data getMagnetic(void);

        IMU::Data getTemp(void);

        IMU::Data getPressure(void);

        inline void setAsyncCallBack(VnDeviceNewAsyncDataReceivedListener callback)
        {
            m_callback = callback;
        }

        IMUFilterConfig getIMUFilterConfig(void);
        bool setIMUFilterConfig(const IMUFilterConfig filterConfig);
    };

}
#endif // VN200_HPP
