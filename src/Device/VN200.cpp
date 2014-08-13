#include <Device/VN200.hpp>
#include <GPS/GPS.hpp>
#include <IMU/IMU.hpp>
#include <Util/maphelper.hpp>

#define SETTINGS_CONTAIN(x) (m_settings.find(x) != m_settings.end())

namespace IRL
{

    std::unordered_map<std::string, VN200::vSetting> VN200::translationTable =
    {
        {"com",                 VN200::vSetting::vnevDeviceName},
        {"buad",                VN200::vSetting::vnevBuadRate},
        {"async",               VN200::vSetting::vnevAsync},
        {"asynctype",           VN200::vSetting::vnevAsyncType},
        {"binary",              VN200::vSetting::vnevBinary},
        {"bin",                 VN200::vSetting::vnevBinary},
        {"callback",            VN200::vSetting::vnevCallBack},
        {"reset",               VN200::vSetting::vnevReset},

        {"setbin",              VN200::vSetting::vnevSetBin},
        {"binaryoutput",        VN200::vSetting::vnevBinOutput},
        {"binoutput",           VN200::vSetting::vnevBinOutput},
        {"binout",              VN200::vSetting::vnevBinOutput},
        {"binary output",       VN200::vSetting::vnevBinOutput},
        {"bin output",          VN200::vSetting::vnevBinOutput},
        {"bin out",             VN200::vSetting::vnevBinOutput},
        {"bindiv",              VN200::vSetting::vnevBinDiv},

        // Group 1
        {"g1timestartup",       VN200::vSetting::vnevG1TimeStartUp},
        {"g1timegps",           VN200::vSetting::vnevG1TimeGPS},
        {"g1timesyncin",        VN200::vSetting::vnevG1TimeSyncIn},
        {"g1yawpitchroll",      VN200::vSetting::vnevG1YawPitchRoll},
        {"g1quaternion",        VN200::vSetting::vnevG1Quaternion},
        {"g1angularrate",       VN200::vSetting::vnevG1AngularRate},
        {"g1position",          VN200::vSetting::vnevG1Position},
        {"g1velocity",          VN200::vSetting::vnevG1Velocity},
        {"g1accel",             VN200::vSetting::vnevG1Accel},
        {"g1imu",               VN200::vSetting::vnevG1IMU},
        {"g1magpres",           VN200::vSetting::vnevG1MagPres},
        {"g1deltatheta",        VN200::vSetting::vnevG1DeltaTheta},
        {"g1insstatus",         VN200::vSetting::vnevG1InsStatus},
        {"g1syncincnt",         VN200::vSetting::vnevG1SyncInCnt},
        {"g1timegpspps",        VN200::vSetting::vnevG1TimeGpsPps},

        //Group 2
        {"g2timestartup",       VN200::vSetting::vnevG2TimeStartUp},
        {"g2timegps",           VN200::vSetting::vnevG2TimeGPS},
        {"g2gpstow",            VN200::vSetting::vnevG2GPSTow},
        {"g2gpsweek",           VN200::vSetting::vnevG2GPSWeek},
        {"g2timesyncin",        VN200::vSetting::vnevG2TimeSyncIn},
        {"g2timegpspps",        VN200::vSetting::vnevG2TimeGpsPps},
        {"g2timeutc",           VN200::vSetting::vnevG2TimeUTC},
        {"g2syncincnt",         VN200::vSetting::vnevG2SyncInCnt},

        // Group 3
        {"g3imustatus",         VN200::vSetting::vnevG3IMUStatus},
        {"g3uncompmag",         VN200::vSetting::vnevG3UncompMag},
        {"g3uncompaccel",       VN200::vSetting::vnevG3UncompAccel},
        {"g3uncompgyro",        VN200::vSetting::vnevG3UncompGyro},
        {"g3temp",              VN200::vSetting::vnevG3Temp},
        {"g3pres",              VN200::vSetting::vnevG3Pres},
        {"g3deltatheta",        VN200::vSetting::vnevG3DeltaTheta},
        {"g3deltavel",          VN200::vSetting::vnevG3DeltaVel},
        {"g3mag",               VN200::vSetting::vnevG3Mag},
        {"g3accel",             VN200::vSetting::vnevG3Accel},
        {"g3angularRate",       VN200::vSetting::vnevG3AngularRate},
        {"g3senssat",           VN200::vSetting::vnevG3SensSat},

        //Group 4
        {"g4utc",               VN200::vSetting::vnevG4UTC},
        {"g4tow",               VN200::vSetting::vnevG4Tow},
        {"g4week",              VN200::vSetting::vnevG4Week,},
        {"g4numsats",           VN200::vSetting::vnevG4NumSats},
        {"g4fix",               VN200::vSetting::vnevG4Fix},
        {"g4poslla",            VN200::vSetting::vnevG4PosLla},
        {"g4posecef",           VN200::vSetting::vnevG4PosEcef},
        {"g4velned",            VN200::vSetting::vnevG4VelNed},
        {"g4velecef",           VN200::vSetting::vnevG4VelEcef},
        {"g4posu",              VN200::vSetting::vnevG4PosU},
        {"g4velu",              VN200::vSetting::vnevG4VelU},
        {"g4timeu",             VN200::vSetting::vnevG4TimeU},
        {"g4svstat",            VN200::vSetting::vnevG4SvStat},

        // Group 5
        {"g5vpestatus",         VN200::vSetting::vnevG5VpeStatus},
        {"g5yawpitchroll",      VN200::vSetting::vnevG5YawPitchRoll},
        {"g5quaternion",        VN200::vSetting::vnevG5Quaternion},
        {"g5dcn",               VN200::vSetting::vnevG5DCM},
        {"g5magned",            VN200::vSetting::vnevG5MagNed},
        {"g5accelned",          VN200::vSetting::vnevG5AccelNed},
        {"g5linearaccelbody",   VN200::vSetting::vnevG5LinearAccelBody},
        {"g5linearaccelned",    VN200::vSetting::vnevG5LinearAccelNed},
        {"g5ypru",              VN200::vSetting::vnevG5YprU},

        //Group 6
        {"g6insstatus",         VN200::vSetting::vnevG6InsStatus},
        {"g6poslla",            VN200::vSetting::vnevG6PosLla},
        {"g6posecef",           VN200::vSetting::vnevG6PosEcef},
        {"g6velbody",           VN200::vSetting::vnevG6VelBody},
        {"g6velecef",           VN200::vSetting::vnevG6VelEcef},
        {"g6magecef",           VN200::vSetting::vnevG6MagEcef},
        {"g6accelecef",         VN200::vSetting::vnevG6AccelEcef},
        {"g6posu",              VN200::vSetting::vnevG6PosU},
        {"g6velu",              VN200::vSetting::vnevG6VelU}
    };

    std::map<VN200::vSetting, int16_t> VN200::binaryGroupTrans =
    {
        // Binary Group 1: Common
        {VN200::vSetting::vnevG1TimeStartUp,        BG1_TIME_STARTUP},
        {VN200::vSetting::vnevG1TimeGPS,            BG1_TIME_GPS},
        {VN200::vSetting::vnevG1TimeSyncIn,         BG1_TIME_SYNC_IN},
        {VN200::vSetting::vnevG1YawPitchRoll,       BG1_YPR},
        {VN200::vSetting::vnevG1Quaternion,         BG1_QTN},
        {VN200::vSetting::vnevG1AngularRate,        BG1_ANGULAR_RATE},
        {VN200::vSetting::vnevG1Position,           BG1_POSITION},
        {VN200::vSetting::vnevG1Velocity,           BG1_VELOCITY},
        {VN200::vSetting::vnevG1Accel,              BG1_ACCEL},
        {VN200::vSetting::vnevG1IMU,                BG1_IMU},
        {VN200::vSetting::vnevG1MagPres,            BG1_MAG_PRES},
        {VN200::vSetting::vnevG1DeltaTheta,         BG1_DELTA_THETA},
        {VN200::vSetting::vnevG1InsStatus,          BG1_INS_STATUS},
        {VN200::vSetting::vnevG1SyncInCnt,          BG1_SYNC_IN_CNT},
        {VN200::vSetting::vnevG1TimeGpsPps,         0x4000},

        // Binary Group 2: Time
        {VN200::vSetting::vnevG2TimeStartUp,        BG2_TIME_STARTUP},
        {VN200::vSetting::vnevG2TimeGPS,            BG2_TIME_GPS},
        {VN200::vSetting::vnevG2GPSTow,             BG2_GPS_TOW},
        {VN200::vSetting::vnevG2GPSWeek,            BG2_GPS_WEEK},
        {VN200::vSetting::vnevG2TimeSyncIn,         BG2_TIME_SYNC_IN},
        {VN200::vSetting::vnevG2TimeGpsPps,         BG2_TIME_PPS},
        {VN200::vSetting::vnevG2TimeUTC,            BG2_TIME_UTC},
        {VN200::vSetting::vnevG2SyncInCnt,          BG2_SYNC_IN_CNT},

        // Binary Group 3: IMU
        {VN200::vSetting::vnevG3IMUStatus,          0x0001},
        {VN200::vSetting::vnevG3UncompMag,          BG3_UNCOMP_MAG},
        {VN200::vSetting::vnevG3UncompAccel,        BG3_UNCOMP_ACCEL},
        {VN200::vSetting::vnevG3UncompGyro,         BG3_UNCOMP_GYRO},
        {VN200::vSetting::vnevG3Temp,               BG3_TEMP},
        {VN200::vSetting::vnevG3Pres,               BG3_PRES},
        {VN200::vSetting::vnevG3DeltaTheta,         BG3_DELTA_THETA},
        {VN200::vSetting::vnevG3DeltaVel,           BG3_DELTA_V},
        {VN200::vSetting::vnevG3Mag,                BG3_MAG},
        {VN200::vSetting::vnevG3Accel,              BG3_ACCEL},
        {VN200::vSetting::vnevG3AngularRate,        BG3_GYRO},
        {VN200::vSetting::vnevG3SensSat,            BG3_SENS_SAT},

        // Binary Group 4: GPS
        {VN200::vSetting::vnevG4UTC,                BG4_UTC},
        {VN200::vSetting::vnevG4Tow,                BG4_TOW},
        {VN200::vSetting::vnevG4Week,               BG4_WEEK},
        {VN200::vSetting::vnevG4NumSats,            BG4_NUM_SATS},
        {VN200::vSetting::vnevG4Fix,                BG4_FIX},
        {VN200::vSetting::vnevG4PosLla,             BG4_POS_LLA},
        {VN200::vSetting::vnevG4PosEcef,            BG4_POS_ECEF},
        {VN200::vSetting::vnevG4VelNed,             BG4_VEL_NED},
        {VN200::vSetting::vnevG4VelEcef,            BG4_VEL_ECEF},
        {VN200::vSetting::vnevG4PosU,               BG4_POS_U},
        {VN200::vSetting::vnevG4VelU,               BG4_VEL_U},
        {VN200::vSetting::vnevG4TimeU,              BG4_TIME_U},

        // Binary Group 5:  Attitude
        {VN200::vSetting::vnevG5VpeStatus,          BG5_VPE_STATUS},
        {VN200::vSetting::vnevG5YawPitchRoll,       BG5_YPR},
        {VN200::vSetting::vnevG5Quaternion,         BG5_QUATERNION},
        {VN200::vSetting::vnevG5DCM,                BG5_DCM},
        {VN200::vSetting::vnevG5MagNed,             BG5_MAG_NED},
        {VN200::vSetting::vnevG5AccelNed,           BG5_ACCEL_NED},
        {VN200::vSetting::vnevG5LinearAccelBody,    BG5_LINEAR_ACCEL_BODY},
        {VN200::vSetting::vnevG5LinearAccelNed,     BG5_LINEAR_ACCEL_NED},
        {VN200::vSetting::vnevG5YprU,               BG5_YPR_U},

        // Binary Group 6: INS
        {VN200::vSetting::vnevG6InsStatus,          BG6_INS_STATUS},
        {VN200::vSetting::vnevG6PosLla,             BG6_POS_LLA},
        {VN200::vSetting::vnevG6PosEcef,            BG6_POS_ECEF},
        {VN200::vSetting::vnevG6VelBody,            BG6_VEL_BODY},
        {VN200::vSetting::vnevG6VelEcef,            BG6_VEL_ECEF},
        {VN200::vSetting::vnevG6MagEcef,            BG6_MAG_ECEF},
        {VN200::vSetting::vnevG6AccelEcef,          BG6_ACCEL_ECEF},
        {VN200::vSetting::vnevG6PosU,               BG6_POS_U},
        {VN200::vSetting::vnevG6VelU,               BG6_VEL_U},
    };


    bool VN200::setAsyncOutput(int type)
    {
        VN_ERROR_CODE error = vn200_setAsynchronousDataOutputType(
                                  &m_vn200,
                                  type,
                                  true);
        return error == VNERR_NO_ERROR;
    }

    VN200::~VN200()
    {
        cleanup();
    }

    bool VN200::setup()
    {
        bool isReady = SETTINGS_CONTAIN(vSetting::vnevDeviceName) &&
                       SETTINGS_CONTAIN(vSetting::vnevBuadRate);
        bool retVal = isReady;

        if(isReady)
        {
            VN_ERROR_CODE errorCode;
            std::string comPort = m_settings[vSetting::vnevDeviceName];
            int buadRate = std::stoi(m_settings[vSetting::vnevBuadRate]);
            errorCode = vn200_connect(&m_vn200, comPort.c_str(), buadRate);
            retVal = (errorCode == VNERR_NO_ERROR);
        }

        return retVal;
    }

    void VN200::cleanup()
    {
        if(m_vn200.isConnected)
        {
            if(m_callback != NULL)
            {
                vn200_unregisterAsyncDataReceivedListener(&m_vn200, m_callback);
            }

            vn200_disconnect(&m_vn200);
        }
    }


    bool VN200::setSetting(const std::string &key, const std::string &value)
    {
        vSetting setting = VN200::translationTable[Util::lowercase(key)];
        return setSetting( setting , value);
    }

    const std::string VN200::getSetting(const std::string &key)
    {
        return getSetting((VN200::translationTable[key]));
    }

    bool VN200::setSetting(const vSetting &key, const std::string &value)
    {
        bool retVal = false;

        switch (key)
        {
            case vSetting::vnevCallBack:
            {
                if(m_callback != NULL)
                {
                    VN_ERROR_CODE err = vn200_registerAsyncDataReceivedListener(&m_vn200,
                                        m_callback);

                    if(err != VNERR_NO_ERROR)
                    {
                        m_callback = NULL;
                        break;
                    }

                    retVal = true;
                }

                break;
            }

            case vSetting::vnevReset:
            {
                if(m_vn200.isConnected)
                {
                    VN_ERROR_CODE error = vn200_reset(&m_vn200);
                    retVal = (error == VNERR_NO_ERROR);
                }

                break;
            }

            case vSetting::vnevAsync:
                if((value == "0" || value == "false"
                    || value == "1" || value == "true")
                   && m_vn200.isConnected)
                {
                    if(value == "0" || value == "false")
                    {
                        if(!setAsyncOutput(VNASYNC_OFF))
                            break;
                    }

                    m_settings[key] = value;
                    retVal = true;
                }

                break;

            case vSetting::vnevAsyncType:
            {
                std::string lValue = Util::lowercase(value);
                bool async = SETTINGS_CONTAIN(vSetting::vnevAsync);

                if(async)
                {
                    std::string asyncStr = m_settings[vSetting::vnevAsync];
                    async = (asyncStr == "1" || asyncStr == "true");
                }

                if(!async && !m_vn200.isConnected)
                    break;

                m_settings[key] = lValue;

                if(lValue == "ypr")
                {
                    if(!setAsyncOutput(VNASYNC_VNYPR))
                        break;
                }
                else if(lValue == "qtn")
                {
                    if(!setAsyncOutput(VNASYNC_VNQTN))
                        break;
                }
                else if(lValue == "qtm")
                {
                    if(!setAsyncOutput(VNASYNC_VNQTM))
                        break;
                }
                else if(lValue == "qta")
                {
                    if(!setAsyncOutput(VNASYNC_VNQTA))
                        break;
                }
                else if(lValue == "qtr")
                {
                    if(!setAsyncOutput(VNASYNC_VNQTR))
                        break;
                }
                else if(lValue == "qma")
                {
                    if(!setAsyncOutput(VNASYNC_VNQMA))
                        break;
                }
                else if(lValue == "qar")
                {
                    if(!setAsyncOutput(VNASYNC_VNQAR))
                        break;
                }
                else if(lValue == "qmr")
                {
                    if(!setAsyncOutput(VNASYNC_VNQMR))
                        break;
                }
                else if(lValue == "dcm")
                {
                    if(!setAsyncOutput(VNASYNC_VNDCM))
                        break;
                }
                else if(lValue == "mag")
                {
                    if(!setAsyncOutput(VNASYNC_VNMAG))
                        break;
                }
                else if(lValue == "acc")
                {
                    if(!setAsyncOutput(VNASYNC_VNACC))
                        break;
                }
                else if(lValue == "gyr")
                {
                    if(!setAsyncOutput(VNASYNC_VNGYR))
                        break;
                }
                else if(lValue == "mar")
                {
                    if(!setAsyncOutput(VNASYNC_VNMAR))
                        break;
                }
                else if(lValue == "ymr")
                {
                    if(!setAsyncOutput(VNASYNC_VNYMR))
                        break;
                }
                else if(lValue == "ycm")
                {
                    if(!setAsyncOutput(VNASYNC_VNYCM))
                        break;
                }
                else if(lValue == "yba")
                {
                    if(!setAsyncOutput(VNASYNC_VNYBA))
                        break;
                }
                else if(lValue == "yia")
                {
                    if(!setAsyncOutput(VNASYNC_VNYIA))
                        break;
                }
                else if(lValue == "icm")
                {
                    if(!setAsyncOutput(VNASYNC_VNICM))
                        break;
                }
                else if(lValue == "imu")
                {
                    if(!setAsyncOutput(VNASYNC_VNIMU))
                        break;
                }
                else if(lValue == "gps")
                {
                    if(!setAsyncOutput(VNASYNC_VNGPS))
                        break;
                }
                else if(lValue == "ins")
                {
                    if(!setAsyncOutput(VNASYNC_VNINS))
                        break;
                }
                else if(lValue == "raw")
                {
                    if(!setAsyncOutput(VNASYNC_VNRAW))
                        break;
                }
                else if(lValue == "cmv")
                {
                    if(!setAsyncOutput(VNASYNC_VNCMV))
                        break;
                }
                else if(lValue == "stv")
                {
                    if(!setAsyncOutput(VNASYNC_VNSTV))
                        break;
                }
                else if(lValue == "cov")
                {
                    if(!setAsyncOutput(VNASYNC_VNCOV))
                        break;
                }
                else
                {
                    break;
                }

                retVal = true;
                break;
            }

            case vSetting::vnevDeviceName:
            {
                m_settings[key] = value;
                retVal = true;
                break;
            }

            case vSetting::vnevBuadRate:
            {
                if(Util::isInt(value))
                {
                    m_settings[key] = value;
                    retVal = true;
                }

                break;
            }

            case vSetting::vnevBinDiv:
            {
                if(Util::isInt(value))
                {
                    binaryDiv = std::stoi(value);
                    m_settings[key] = value;
                    retVal = true;
                }

                break;
            }

            case vSetting::vnevBinOutput:
            {
                if(Util::isInt(value) )
                {
                    int i = std::stoi(value);

                    if(1 <= i && i <=3)
                    {
                        binaryMessage = i;
                        m_settings[key] = value;
                        retVal = true;
                    }
                }

                break;
            }

            case vSetting::vnevSetBin:
            {
                if(!m_vn200.isConnected)
                    break;

                VN_ERROR_CODE errCode;

                switch (binaryMessage)
                {
                    case 1:
                        errCode = vn200_setBinaryOutput1Configuration(
                                      &m_vn200,
                                      BINARY_ASYNC_MODE_SERIAL_1,
                                      binaryDiv,
                                      binaryGroup1,
                                      binaryGroup2,
                                      binaryGroup3,
                                      binaryGroup4,
                                      binaryGroup5,
                                      binaryGroup6,
                                      true);
                        break;

                    case 2:
                        errCode = vn200_setBinaryOutput2Configuration(
                                      &m_vn200,
                                      BINARY_ASYNC_MODE_SERIAL_1,
                                      binaryDiv,
                                      binaryGroup1,
                                      binaryGroup2,
                                      binaryGroup3,
                                      binaryGroup4,
                                      binaryGroup5,
                                      binaryGroup6,
                                      true);
                        break;

                    case 3:
                        errCode = vn200_setBinaryOutput3Configuration(
                                      &m_vn200,
                                      BINARY_ASYNC_MODE_SERIAL_1,
                                      binaryDiv,
                                      binaryGroup1,
                                      binaryGroup2,
                                      binaryGroup3,
                                      binaryGroup4,
                                      binaryGroup5,
                                      binaryGroup6,
                                      true);
                        break;

                    default:
                        errCode = -1;
                }

                retVal = (errCode == VNERR_NO_ERROR);
                break;
            }

            // Binary Group 1: Common
            case vSetting::vnevG1TimeStartUp:
            case vSetting::vnevG1TimeGPS:
            case vSetting::vnevG1TimeSyncIn:
            case vSetting::vnevG1YawPitchRoll:
            case vSetting::vnevG1Quaternion:
            case vSetting::vnevG1AngularRate:
            case vSetting::vnevG1Position:
            case vSetting::vnevG1Velocity:
            case vSetting::vnevG1Accel:
            case vSetting::vnevG1IMU:
            case vSetting::vnevG1MagPres:
            case vSetting::vnevG1DeltaTheta:
            case vSetting::vnevG1InsStatus:
            case vSetting::vnevG1SyncInCnt:
            case vSetting::vnevG1TimeGpsPps:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup1 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup1 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            // Binary Group 2: Time
            case vSetting::vnevG2TimeStartUp:
            case vSetting::vnevG2TimeGPS:
            case vSetting::vnevG2GPSTow:
            case vSetting::vnevG2GPSWeek:
            case vSetting::vnevG2TimeSyncIn:
            case vSetting::vnevG2TimeGpsPps:
            case vSetting::vnevG2TimeUTC:
            case vSetting::vnevG2SyncInCnt:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup2 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup2 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            // Binary Group 3: IMU
            case vSetting::vnevG3IMUStatus:
            case vSetting::vnevG3UncompMag:
            case vSetting::vnevG3UncompAccel:
            case vSetting::vnevG3UncompGyro:
            case vSetting::vnevG3Temp:
            case vSetting::vnevG3Pres:
            case vSetting::vnevG3DeltaTheta:
            case vSetting::vnevG3DeltaVel:
            case vSetting::vnevG3Mag:
            case vSetting::vnevG3Accel:
            case vSetting::vnevG3AngularRate:
            case vSetting::vnevG3SensSat:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup3 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup3 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            // Binary Group 4: GPS
            case vSetting::vnevG4UTC:
            case vSetting::vnevG4Tow:
            case vSetting::vnevG4Week:
            case vSetting::vnevG4NumSats:
            case vSetting::vnevG4Fix:
            case vSetting::vnevG4PosLla:
            case vSetting::vnevG4PosEcef:
            case vSetting::vnevG4VelNed:
            case vSetting::vnevG4VelEcef:
            case vSetting::vnevG4PosU:
            case vSetting::vnevG4VelU:
            case vSetting::vnevG4TimeU:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup4 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup4 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            // Binary Group 5:  Attitude
            case vSetting::vnevG5VpeStatus:
            case vSetting::vnevG5YawPitchRoll:
            case vSetting::vnevG5Quaternion:
            case vSetting::vnevG5DCM:
            case vSetting::vnevG5MagNed:
            case vSetting::vnevG5AccelNed:
            case vSetting::vnevG5LinearAccelBody:
            case vSetting::vnevG5LinearAccelNed:
            case vSetting::vnevG5YprU:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup5 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup5 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            // Binary Group 6: INS
            case vSetting::vnevG6InsStatus:
            case vSetting::vnevG6PosLla:
            case vSetting::vnevG6PosEcef:
            case vSetting::vnevG6VelBody:
            case vSetting::vnevG6VelEcef:
            case vSetting::vnevG6MagEcef:
            case vSetting::vnevG6AccelEcef:
            case vSetting::vnevG6PosU:
            case vSetting::vnevG6VelU:
            {
                std::string lValue = Util::lowercase(value);

                if(lValue == "false" || lValue == "0")
                {
                    binaryGroup6 &= ~(binaryGroupTrans[key]);
                }
                else if(lValue == "true" || lValue == "1")
                {
                    binaryGroup6 |= binaryGroupTrans[key];
                }
                else
                {
                    break;
                }

                m_settings[key] = lValue;
                retVal = true;
            }

            default:
                break;

        }

        return retVal;
    }

    const std::string VN200::getSetting(const vSetting &key)
    {
        return m_settings[key];
    }

    GPS::Data VN200::hasGPSFix()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        return GPS::Data(data.gpsFix);
    }

    GPS::Data VN200::getGPSTime()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        return GPS::Data(data.gpsTowNs, data.gpsWeek);
    }

    GPS::Data VN200::getNumOfSat()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        return GPS::Data(data.numSats);
    }

    GPS::Data VN200::getPos()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        return GPS::Data(data.latitudeLongitudeAltitude.c0,
                         data.latitudeLongitudeAltitude.c1,
                         data.latitudeLongitudeAltitude.c2,
                         data.posEcef.c0,
                         data.posEcef.c1,
                         data.posEcef.c2);
    }

    GPS::Data VN200::getGPSVelocity()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        return GPS::Data(data.velNed.c0,
                         data.velNed.c1,
                         data.velNed.c2,
                         data.velEcef.c0,
                         data.velEcef.c1,
                         data.velEcef.c2,
                         true);
    }

    IMU::Data VN200::getAcceleration()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        IMU::Data imudata(IMUDataType::ACCEL);
        imudata.acceleration.v1 = data.acceleration.c0;
        imudata.acceleration.v2 = data.acceleration.c1;
        imudata.acceleration.v3 = data.acceleration.c2;
        return imudata;
    }

    IMU::Data VN200::getGyro()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        IMU::Data imudata(IMUDataType::GYRO);
        imudata.gyro.v1 = data.ypr.yaw;
        imudata.gyro.v2 = data.ypr.pitch;
        imudata.gyro.v3 = data.ypr.roll;
        return imudata;
    }

    IMU::Data VN200::getMagnetic()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        IMU::Data imudata(IMUDataType::MAG);
        imudata.magnetic.v1 = data.magEcef.c0;
        imudata.magnetic.v2 = data.magEcef.c1;
        imudata.magnetic.v3 = data.magEcef.c2;
        return imudata;
    }

    IMU::Data VN200::getPressure()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        IMU::Data imudata(IMUDataType::PRESSURE);
        imudata.pressure = data.pressure;
        return imudata;
    }

    IMU::Data VN200::getTemp()
    {
        VnDeviceCompositeData data;
        vn200_getCurrentAsyncData(&m_vn200, &data);
        IMU::Data imudata(IMUDataType::TEMP);
        imudata.temperature = data.temperature;
        return imudata;
    }

    bool VN200::setIMUFilterConfig(const IMUFilterConfig filterConfig)
    {
        VN_ERROR_CODE err = vn200_setImuFilteringConfiguration(&m_vn200,
                            filterConfig.MagWindowSize,
                            filterConfig.AccelWindowSize,
                            filterConfig.GyroWindowSize,
                            filterConfig.TempWindowSize,
                            filterConfig.PresWindowSize,
                            filterConfig.MagFilterMode,
                            filterConfig.AccelFilterMode,
                            filterConfig.GyroFilterMode,
                            filterConfig.TempFilterMode,
                            filterConfig.PresFilterMode,
                            true
                                                              );
        return err == VNERR_NO_ERROR;
    }

    IMUFilterConfig VN200::getIMUFilterConfig()
    {
        IMUFilterConfig filterConfig;
        vn200_getImuFilteringConfiguration(&m_vn200,
                                           &(filterConfig.MagWindowSize),
                                           &(filterConfig.AccelWindowSize),
                                           &(filterConfig.GyroWindowSize),
                                           &(filterConfig.TempWindowSize),
                                           &(filterConfig.PresWindowSize),
                                           &(filterConfig.MagFilterMode),
                                           &(filterConfig.AccelFilterMode),
                                           &(filterConfig.GyroFilterMode),
                                           &(filterConfig.TempFilterMode),
                                           &(filterConfig.PresFilterMode)
                                          );
        return filterConfig;
    }
}
