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
    /**
     * @brief The BlackFly class
     */
    class BlackFly : public Camera
    {
    private:
        /**
         * @brief m_settings
         */
        std::unordered_map<std::string,std::string> m_settings;

        /**
         * @brief m_camera
         */
        FlyCapture2::GigECamera m_camera;
    public:

        /**
         * @brief BlackFly
         */
        BlackFly() : m_settings(), m_camera() {}


        ~BlackFly();

        /**
         * @brief setup
         * @param camera
         */
        void setup(uint16_t camera = 0);

        /**
         * @brief cleanup
         */
        void cleanup(void);

        /**
         * @brief captureImage
         * @param image
         * @return
         */
        int captureImage(uint8_t* image);

        /**
         * @brief setSetting
         * @param key
         * @param value
         * @return
         */
        bool setSetting(const std::string& key, const std::string& value);

        /**
         * @brief getSetting
         * @param key
         * @return
         */
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
