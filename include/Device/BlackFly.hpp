#ifndef POINTGREY_HPP
#define POINTGREY_HPP

#include <Camera/Camera.hpp>
#include <FlyCapture2.h>

namespace IRL {
    class BlackFly : ICamera
    {
    public:
        BlackFly();
        ~BlackFly();
        void setup(void);
        void cleanup(void);
        int captureImage(uint8_t* image);
        void setSetting(const std::string& key, const std::string& value);
        const std::string& getSetting(const std::string& key);
        bool imageAvailable(void);
    private:
        
    };
}


#endif // POINTGREY_HPP