#ifndef POINTGREY_HPP
#define POINTGREY_HPP

#include <Camera/Camera.hpp>
#include <flycapture/FlyCapture2.h>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>

namespace IRL
{
class BlackFly : public Camera
{
private:
    std::unordered_map<std::string,std::string> m_settings;
    FlyCapture2::GigECamera m_camera;
public:
    BlackFly() : m_settings(), m_camera() {}
    ~BlackFly();
    void setup(uint16_t camera = 0);
    void cleanup(void);
    int captureImage(uint8_t* image);
    bool setSetting(const std::string& key, const std::string& value);
    const std::string getSetting(const std::string& key);
    bool imageAvailable(void);
    uint32_t getNumberOfCameras(void);
protected:
    void printBuildInfo();
    void printCameraInfo(const FlyCapture2::CameraInfo& rCamInfo);
    void printFormat7Capablities(const FlyCapture2::Format7Info& fmt7info);
    uint32_t discoverCameras(std::vector<FlyCapture2::CameraInfo>& camInfo);
};
}


#endif // POINTGREY_HPP
