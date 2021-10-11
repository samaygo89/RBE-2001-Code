#include "chassis.h"
#include <Arduino.h>
void Chassis::AttachComponents( int EchoPin, int TrigPin, int LeftLineSense, int RightLineSense){
    
    photoresistorPinL=LeftLineSense;
    photoresistorPinR = RightLineSense;
    left_motor.attach();
    right_motor.attach();
    ultrasonic.attach(TrigPin,EchoPin);
}
void Chassis::SetEffort(float effort){
    this->right_motor.setEffort(effort);
    this->left_motor.setEffort(effort);
}
float Kp1 = .01;
void Chassis::followline(float base_speed){
    int Right = analogRead(photoresistorPinR);
    int Left = analogRead(photoresistorPinL);
    int Error = Right-Left;
    left_motor.setSpeed(base_speed + Kp1 * Error);// adding proportional effort and subtracting derivative term
    right_motor.setSpeed(base_speed - Kp1 * Error);//subtracting proportional error and adding the derivative term
}
void Chassis::brake(){
    this->left_motor.setEffort(0);
    this->right_motor.setEffort(0);
}
void Chassis::turn(int direction){  //1:Right, -1:Left
    int prev_reading = 0;
    int curr_reading = 0;
    bool flag = false;
    right_motor.setSpeed(-155 * direction);
    left_motor.setSpeed(155 * direction);
    int polling_pin = photoresistorPinR;
    if(direction == -1){
        polling_pin = photoresistorPinL;
    }
    while(!flag){
        delay(50);
        curr_reading = analogRead(polling_pin);
        if((prev_reading - curr_reading) > 200){
            flag=true;
        }
        prev_reading=curr_reading;
    }
    this->brake();
}
float Chassis::getDistanceCM(){
  return this->ultrasonic.getDistanceCM();
}

