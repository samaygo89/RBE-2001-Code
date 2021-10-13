#include <RBE1001Lib.h>
#include <Arduino.h>
#include <BlueMotor.h>

class Arm{
    public:
    BlueMotor ArmMotor;
    Servo gripper;
    //ESP32AnalogRead servoPositionFeedback;
    void setup();
    int SetPIDEffort();
    void SetArmEffort(float effort);
    void open_gripper();
    void close_gripper();
    int ArmCountSetPoint=0;
    
    
};