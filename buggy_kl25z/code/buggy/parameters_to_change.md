# List of modifiable parameters of Buggy KL25Z
### Autor: Triet NGUYEN (tr_nguye@insa-toulouse.fr)

This file contains all the modifiable parameters that can affect the buggy performance, where to find them and their effects on the buggy. This list can be non-exhaustive.

## Physical parameters
### Camera's angle
- Location: On the buggy
- Importance level: ***Extremely important***

The angle of the camera determines how far the camera is looking. 
The closer the car looks, the faster it needs to react.
But if the car looks too far away, it cannot see the turn (especially 180 degrees) 

### Camera's height
- Location: On the buggy
- Importance level: ***Important***

Same as the camera's angle.

## Camera's parameters
### Gain KP
- Variable name: KP_TURN
- Location: ImageProcessing.cpp
- Importance level: ***Extremely important***

Proportional gain for the regulation loop of the camera.
The greater the gain, the faster the car reacts to a turn - it turns harder for a giving turn.
Risk of instability if the gain is too high.

### Gain KDP
- Variable name: KDP_TURN
- Location: ImageProcessing.cpp
- Importance level: ***Extremely important***

Differential gain for the regulation loop of the camera.
Its effect remains unclear.

### Camera's weight
- Variable name: K_CAMERA_NEAR(or FAR)
- Location: ImageProcessing.hpp
- Importance level: ***Extremely important***

The "importance" of a camera when calculating the combined RoadMiddle.
The sum of the weight of 2 cameras is equal to 1.
If the CAMERA_NEAR is more important, *the effect still in study*
If the CAMERA_NEAR is more important, *the effect still in study*

### Threshold for detecting edge
- Variable name: THRESHOLD_classic
- Location: ImageProcessing.hpp
- Importance level: ***Extremely important***


## Servo's parameters
### Max steering angle
- Variable name: SERVO_MAX_LEFT_ANGLE (or RIGHT)
- Location: driver_servo.h
- Importance level: ***Important***


## Speed
### Speed at start

### Target speed

### Speed at turn