#include <RBE1001Lib.h>

class Chassis{
public:

LeftMotor left_motor;
RightMotor right_motor;
Rangefinder ultrasonic;
int photoresistorPinL;
int photoresistorPinR;
void SetEffort(float effort);
void SetSpeed(float speed);
void turn(int direction);
void AttachComponents(int EchoPin, int TrigPin,int LeftLineSense, int RightLineSense);
void brake();
void followline(float base_speed);
bool checkforintersection();
bool CheckDistanceAway(float distance);
float getDistanceCM();
void BackAway();
};