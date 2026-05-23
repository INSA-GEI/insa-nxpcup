#include "MW_Servo.h"
#include "mbed.h"
#include "MW_target_hardware_resources.h"

const PinName MW_Servo::servoPins[] = {PTA12, PTA13};

MW_Servo::~MW_Servo()
{
    delete this->Servo;
}

MW_Servo::MW_Servo(uint8_t servoNumber, float minAngle, float maxAngle) {

    this->Servo = new PwmOut(servoPins[servoNumber]);

    setRange(minAngle, maxAngle);
    initServo(this->Servo);
}

void MW_Servo::setMinAngle(float minAngleInDeg) {
    this->minAngle = minAngleInDeg;
}

void MW_Servo::setMaxAngle(float maxAngleInDeg) {
    this->maxAngle = maxAngleInDeg;
}

void MW_Servo::setRange(float minAngleInDeg, float maxAngleInDeg) {
    setMinAngle(minAngleInDeg);
    setMaxAngle(maxAngleInDeg);
}

void MW_Servo::initServo(PwmOut* servo) {
    servo->period(1.0/MW_TPM1_FREQUENCY); // set to 20ms
    setAngle(0.0f);
}

void MW_Servo::setPosition(float position) {
    if(position > 1.0f)
        position = 1.0f;
    else if(position < -1.0f)
        position = -1.0f;

    this->angle = ((this->maxAngle - this->minAngle)/2.0f)*position
                 + (this->maxAngle + this->minAngle)/2.0f;

    this->setAngle(this->angle);
}

void MW_Servo::setAngle(float angleInDeg) {
    if(angleInDeg > this->maxAngle)
        angleInDeg = this->maxAngle;
    else if(angleInDeg < this->minAngle)
        angleInDeg = this->minAngle;

    this->angle = angleInDeg;

    this->Servo->pulsewidth( ( 0.0005f * ( angleInDeg / 45.0f ) ) + 0.001275f );
}

float MW_Servo::getAngle() {
    return this->angle;
}

MW_Servo& MW_Servo::operator= (float angle) {
    setAngle(angle);
    return *this;
}

MW_Servo& MW_Servo::operator= (MW_Servo& rhs) {
    setAngle(rhs.getAngle());
    return *this;
}

MW_Servo::operator float() {
    return getAngle();
}
