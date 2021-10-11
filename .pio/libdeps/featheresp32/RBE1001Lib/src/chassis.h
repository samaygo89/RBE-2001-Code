#include <RBE1001Lib.h>

class Chassis{
public:

LeftMotor left_motor;
RightMotor right_motor;
Rangefinder ultrasonic;
int photoresistorPinL;
int photoresistorPinR;
void SetEffort(float effort);
void turn(int direction);
void AttachComponents(int EchoPin, int TrigPin,int LeftLineSense, int RightLineSense);
void brake();
void followline(float base_speed);
float getDistanceCM();
};