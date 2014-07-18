#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <cstdint>
#include <string>

namespace IRL
{
/**
 * Camera
 *
 * This is the interface for Camera Objects, this will
 * allow for the ablity to switch Cameras without major changes
 * to the main body of the program
 */
class Camera
{
protected:
    bool _started = false;
public:
    
    virtual ~Camera() {}

    /**
     * setup
     *
     * Setups up the camera to start taking pictures
     */
    virtual void setup(uint16_t camera = 0) = 0;

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
    virtual const std::string getSetting(const std::string& key) = 0;

    /**
     * imageAvailable
     *
     * tells if a image is available to grab
     */
    virtual bool imageAvailable(void) = 0;

    virtual uint32_t getNumberOfCameras(void) = 0;
    
    virtual inline bool isStarted(void) { return _started; }
};

}

#endif
