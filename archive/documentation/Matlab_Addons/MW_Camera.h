#ifndef _MW_Camera_H
#define _MW_Camera_H

#include "mbed.h"

class MW_Camera
{

public:
    // Constructor and Destructor
    ~MW_Camera();
    MW_Camera(uint8_t cameraNumber);

    // accessor methods
    void setExposureTime(uint8_t exposureTime_ms); // set the exposure time in ms
    uint16_t  getCameraDatum(uint8_t index);     // Get pixel value
    uint16_t* getCameraData();                   // Get pointer to image
    void      getCameraImage(uint16_t* cameraDataVector); // Get image

    void updateCameraData();    // collects data from camera through ADC
    void updateCameraImage();   // collects an image after clearing the
                                // previous values in the ADC
    
    /**  Shorthand for the accessor methods */
    operator uint16_t*();

private:
    AnalogIn* camera; // AnalogIn Object represents the camera

    DigitalOut* SI;   // Signal triggers a capture sequence
    DigitalOut* CLK;  // Clock triggers sequential pixel conversions
    static const PinName cameraPinName[]; // Stores the Cameras' data Pins
    static const DigitalOut SIPinName[];
    static const DigitalOut CLKPinName[];
    static const uint8_t numPixels = 128;

    uint16_t lineScanImage[numPixels]; // Most recent image data
    uint8_t   exposureTime;                      // exposure time in ms
};

#endif