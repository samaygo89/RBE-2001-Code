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
void Chassis::SetSpeed(float speed){
    this->right_motor.setSpeed(speed);
    this->left_motor.setSpeed(speed);
}
float Kp1 = .01;
void Chassis::followline(float base_speed){
    int Right = analogRead(photoresistorPinR);
    int Left = analogRead(photoresistorPinL);
    int Error = Right-Left;
    left_motor.setSpeed(base_speed + Kp1 * Error);// adding proportional effort and subtracting derivative term
    right_motor.setSpeed(base_speed - Kp1 * Error);//subtracting proportional error and adding the derivative term
}
bool now_both_black = false;
bool Chassis::checkforintersection()
{
    int adcPhotoresistorL = analogRead(photoresistorPinL);
    int adcPhotoresistorR = analogRead(photoresistorPinR);
    now_both_black = ((adcPhotoresistorR > 1900) && (adcPhotoresistorL > 1900));
    if (now_both_black)
    {
        return true;
    }
    return false;
}
/**
 * @brief 
 * 
 * @param distance 
 * @return true when ultrasonic reads a distance equal to or larger than distance
 * @return false 
 */
bool Chassis::CheckDistanceAway(float distance)
{
    Serial.println(getDistanceCM());
    if (this->getDistanceCM()>=distance)
    {
        return true;
    }
    return false;
}
void Chassis::brake(){
    this->left_motor.setEffort(0);
    this->right_motor.setEffort(0);
}
void Chassis::turn(int direction){  //1:Right, -1:Left, 2:180
    left_motor.setSpeed(155*direction);
    right_motor.setSpeed(-155*direction);
    if(direction == 1 || direction == -1){
        delay(1235);
    }
    else
    {
        delay(2470);
    }
    brake();
    /**
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
    **/
}
float Chassis::getDistanceCM(){
  return this->ultrasonic.getDistanceCM();
}
bool startedbacking = false;
void Chassis::BackAway(){
    if(!startedbacking){
        this->SetEffort(-100);
        startedbacking = true;
    }
    if(CheckDistanceAway(15)){
    delay(100);
    turn(1); // Blocking turn function
    startedbacking=false;
    return;
    }
}
