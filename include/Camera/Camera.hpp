#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <cstdint>
#include <string>

namespace IRL
{
    /**
     * ICamera
     * 
     * This is the interface for Camera Objects, this will
     * allow for the ablity to switch Cameras without major changes
     * to the main body of the program
     */
    class ICamera
    {
    public:
        virtual ~ICamera() {}
        
        /**
         * setup
         * 
         * Setups up the camera to start taking pictures
         */
        virtual void setup(void) = 0;
        
        /**
         * cleanup
         * 
         * Cleans up camera and gets ready for closing
         */
        virtual void cleanup(void) = 0;
        
        /**
         * captureImage
         * 
         * Captures an image
         */
        virtual int captureImage(uint8_t* image) = 0;
        
        /**
         * setSetting
         * 
         * sets a setting based on a key value pair
         */
        virtual void setSetting(const std::string& key, const std::string& value) = 0;
        
        /**
         * getSetting
         * 
         * gets a setting value based on a key
         */
        virtual const std::string& getSetting(const std::string& key) = 0;
    };
    
}

#endif 