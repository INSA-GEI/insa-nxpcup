 /** Copyright 2014 - 2015 The MathWorks, Inc.*/
 
#include "MW_Camera.h"
#include "mbed.h"

#define LOW       0
#define HIGH      1
#define EXPOSURE_TIME_MAX 150U
#define EXPOSURE_TIME_MIN   0U

const PinName MW_Camera::cameraPinName[] = {PTC2, PTC1};
const DigitalOut MW_Camera::SIPinName[]={PTB8,PTB10};
const DigitalOut MW_Camera::CLKPinName[]={PTB9,PTB11};

MW_Camera::~MW_Camera() {
    delete this->camera;
}

MW_Camera::MW_Camera(uint8_t cameraNumber) {
    this->exposureTime = 10U;

    this->camera = new AnalogIn(cameraPinName[cameraNumber]);
    this->CLK = new DigitalOut(CLKPinName[cameraNumber]);
    this->SI = new DigitalOut(SIPinName[cameraNumber]);




    // start SI and CLK LOW
    this->CLK->write(LOW);
    this->SI->write(LOW);
}

uint16_t MW_Camera::getCameraDatum(uint8_t index) {
    return this->lineScanImage[index];
}

uint16_t* MW_Camera::getCameraData() {
    return &(this->lineScanImage[0]);
}

void MW_Camera::getCameraImage(uint16_t* cameraDataVector) {
    for(int i = 0; i < MW_Camera::numPixels; i++)
    {
        cameraDataVector[i] = this->lineScanImage[i];
    }
}

void MW_Camera::setExposureTime(uint8_t exposureTime_ms) {
    // Clamp exposure time to the min and max exposure time
    if( exposureTime_ms > EXPOSURE_TIME_MAX )
        exposureTime_ms = EXPOSURE_TIME_MAX;
    if( exposureTime_ms < EXPOSURE_TIME_MIN )
        exposureTime_ms = EXPOSURE_TIME_MIN;

    this->exposureTime = exposureTime_ms;
}

void MW_Camera::updateCameraData() {

    // Start the Capture Sequence for the Line scan Camera
    this->SI->write(HIGH);
    this->CLK->write(HIGH);
    this->SI->write(LOW);

    for(uint8_t j = 0; j < MW_Camera::numPixels; j++) {
        this->lineScanImage[j] = camera->read_u16();

        this->CLK->write(LOW);
        this->CLK->write(HIGH);
    }
    this->CLK->write(LOW);
}

void MW_Camera::updateCameraImage() {
    
    // wipe the camera's data by triggering a new data capture
    this->SI->write(HIGH);
    this->CLK->write(HIGH);
    this->SI->write(LOW);
    for(uint8_t i = 0; i < MW_Camera::numPixels; i++) {
        this->CLK->write(LOW);
        this->CLK->write(HIGH);
    }
    this->CLK->write(LOW);
    // wait the alloted exposure time
    wait_ms(this->exposureTime);
    // retrieve the data from the camera
    this->updateCameraData();
}

MW_Camera::operator uint16_t*() {
    return this->getCameraData();
}