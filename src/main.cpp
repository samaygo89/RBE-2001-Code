#include <Arduino.h>
#include <chassis.h>
#include <RBE1001Lib.h>
#include <IRdecoder.h>
#include <BlueMotor.h>
#include <arm.h>
#include <PID_v1.h>
Chassis body;
const int TrigPin = 17;
const int EchoPin = 16;
const int PhotoResistorR = 39;
const int PhotoResistorL = 36;
IRDecoder decoder(34);
Arm arm;
enum ROBOT_STATE
{
  ROBOT_IDLE,
  ROBOT_LINING,
  ROBOT_DROPPING_OFF_PLATE,
  ROBOT_PICKING_UP_PLATE
};
enum ANGLE
{
  ROBOT_25,
  ROBOT_45
};
void setup()
{
  Serial.begin(115200);
  body.AttachComponents(EchoPin, TrigPin, PhotoResistorL, PhotoResistorR);
  arm.setup();
  ESP32PWM::allocateTimer(2);
  decoder.init();
}
/**
long int i = 0;
long int prev_position = 0;
int prev_time1 = 0;
float adjustedEffort = 0;
int currtime1 = 0;
long int curr_position = 0;
float velocity=0;
**/
long int PIDtimer=0;
long int currtime1=0;
int value=-1;
void loop()
{

  
    int value = decoder.getKeyCode();
    currtime1 = millis();
    if(currtime1>PIDtimer+10){
      Serial.println(body.getDistanceCM());
      arm.SetPIDEffort();
      PIDtimer=currtime1;
    }
  //adjustedEffort=85+(255-85)*i/255;
  //arm.SetArmEffort(i);
  //currtime1 = millis();
  //curr_position = arm.ArmMotor.getPosition();
  //velocity=(curr_position - prev_position) / (currtime1 - prev_time1);
  //velocity=arm.ArmMotor.getPosition()-prev_position;
  //velocity=velocity/(currtime1-prev_time1);
  //Serial.printf("%i,%f,%f \n", i, adjustedEffort, velocity);
  //i++;
  //prev_time1 = currtime1;
  //prev_position = curr_position;
  //delay(500);
}