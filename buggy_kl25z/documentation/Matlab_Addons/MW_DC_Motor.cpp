#include "MW_DC_Motor.h"
#include "mbed.h"
#include "MW_target_hardware_resources.h"

DigitalOut MW_DC_Motor::hBridgeEN(PTE21);

MW_DC_Motor::~MW_DC_Motor() {
    disableHbridge();
    delete this->motorIn1;
    delete this->motorIn2;
}

MW_DC_Motor::MW_DC_Motor(char motorLetter) {
    disableHbridge();

    switch( motorLetter ) {
        default:
            break;

        case 'A':
            this->motorIn1 = new PwmOut(PTA4);
            this->motorIn2 = new PwmOut(PTA5);

            break;

        case 'B':
            this->motorIn1 = new PwmOut(PTC8);
            this->motorIn2 = new PwmOut(PTC9);

            break;
    }
    
    initMotorInput(this->motorIn1);
    initMotorInput(this->motorIn2);
    enableHbridge();
}

void MW_DC_Motor::initMotorInput(PwmOut* motorIn) {
    motorIn->period(1.0/MW_TPM0_FREQUENCY);
    motorIn->write(0.0);
}

void MW_DC_Motor::setSpeed(float speed) {
    if(speed > 1.0)
        speed = 1.0;
    else if(speed < -1.0)
        speed = -1.0;

    if(speed >= 0) {
        *(this->motorIn1) = speed;
        *(this->motorIn2) = 0.0;
    } else if(speed < 0) {
        *(this->motorIn1) = 0.0;
        *(this->motorIn2) = -speed;
    }
}

void MW_DC_Motor::disableHbridge() {
    this->hBridgeEN = false;
}

void MW_DC_Motor::enableHbridge() {
    this->hBridgeEN = true;
}

float MW_DC_Motor::getSpeed() {

    return this->motorIn1->read() - this->motorIn2->read();
}
    
MW_DC_Motor& MW_DC_Motor::operator= (float speed) { 
    setSpeed(speed);
    return *this;
}

MW_DC_Motor& MW_DC_Motor::operator= (MW_DC_Motor& rhs) {
    setSpeed(rhs.getSpeed());
    return *this;
}

MW_DC_Motor::operator float() {
    return getSpeed();
}
