#include <Device/BlackFly.hpp>

namespace IRL
{
    BlackFly::~BlackFly()
    {
        cleanup();
    }
    
    void BlackFly::setup(uint16_t camera)
    {

        _started = 0;
    }
    
    void BlackFly::cleanup()
    {
        
    }
    
    
    int BlackFly::captureImage(uint8_t *image)
    {
        return 0;
    }
    
    void BlackFly::setSetting(const std::string& key, const std::string& value)
    {

    }

    const std::string BlackFly::getSetting(const std::string& key)
    {
        std::string test = "";
        return test;
    }

    bool BlackFly::imageAvailable(void)
    {
        return false;
    }

    uint32_t getNumberOfCameras(void)
    {
        return 0;
    }

    void printBuildInfo()
    {

    }

    void printCameraInfo(const FlyCapture2::CameraInfo& rCamInfo)
    {

    }
    void printFormat7Capablities(const FlyCapture2::Format7Info& fmt7info)
    {

    }

    uint32_t discoverCameras(std::vector<FlyCapture2::CameraInfo>& camInfo)
    {
        return 0;
    }
    
}
