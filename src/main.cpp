#include <Arduino.h>
#include <chassis.h>
#include <RBE1001Lib.h>
#include <IRdecoder.h>
#include <BlueMotor.h>
#include <arm.h>
#include <PID_v1.h>
#include <IR_Buttons.h>
Chassis body;
const int TrigPin = 16;
const int EchoPin = 17;
const int PhotoResistorR = 39;
const int PhotoResistorL = 36;
IRDecoder decoder(15);
Arm arm;
enum ROBOT_STATE
{
  ROBOT_IDLE,
  ROBOT_LINING,
  ROBOT_DROPPING_OFF_PLATE,
  ROBOT_PICKING_UP_PLATE,
  ROBOT_BACKING
};
enum ANGLE
{
  ROBOT_25,
  ROBOT_45,
  ROBOT_STAGING
};
ROBOT_STATE robot = ROBOT_IDLE;
ROBOT_STATE prev_robot;
ANGLE angle = ROBOT_45;
void setup()
{
  Serial.begin(115200);
  body.AttachComponents(EchoPin, TrigPin, PhotoResistorL, PhotoResistorR);
  arm.setup();
  decoder.init();
  arm.close_gripper();
}

int_fast16_t key;
bool staging_setup = false;
bool approaching = false;
bool backing_up = false;
bool dropping_setup = false;
bool approachingD = false;
bool backing = false;
bool begun = false;
void loop()
{
  key = decoder.getKeyCode();
  arm.SetPIDEffort();
  if (key == Play_Pause)
  {
    prev_robot = robot;
    robot = ROBOT_IDLE;
  }
  if (key == Num_pad_0)
  {
    robot = ROBOT_DROPPING_OFF_PLATE;
  }
  switch (robot)
  {
  case ROBOT_IDLE:

    break;
  case ROBOT_DROPPING_OFF_PLATE:
    if (angle == ROBOT_STAGING)
    {
      if (!dropping_setup)
      {
        arm.ArmCountSetPoint = 0;
        dropping_setup = true;
        approachingD = true;
      }
      if (approachingD)
      {
        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 5)
        {
          body.brake();
          approachingD = false;
          arm.close_gripper();
        }
      }
      if (key == Enter_Save)
      {
        arm.open_gripper();
      }
    }
    if (angle == ROBOT_25)
    {
      arm.ArmCountSetPoint = 5643;
      if ((arm.ArmCountSetPoint - arm.ArmMotor.getPosition()) < 2000)
      {
        staging_setup = true;
        approachingD = true;
      }
      if (approachingD)
      {
        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 3.5)
        {
          Serial.println("Distance Away");
          body.brake();
          approachingD = false;
        }
      }
      if (key == Enter_Save)
      {
        arm.open_gripper();
        backing = true;
      }
      if (backing)
      {
        body.SetEffort(-.5);
        delay(250);
        body.brake();
        backing = false;
      }
    }
    if (angle == ROBOT_45)
    {
      arm.ArmCountSetPoint = 3500;
      if ((arm.ArmCountSetPoint - arm.ArmMotor.getPosition()) < 2000 && !begun)
      {
        staging_setup = true;
        approachingD = true;
        begun = true;
      }
      if (approachingD)
      {
        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 10)
        {
          Serial.println("Distance Away");
          body.brake();
          approachingD = false;
        }
      }
      if (key == Enter_Save)
      {
        arm.open_gripper();
        backing = true;
      }
      if (backing)
      {
        body.SetEffort(-.5);
        delay(250);
        body.brake();
        backing = false;
      }
    }
    break;

  case ROBOT_PICKING_UP_PLATE:
    if (angle == ROBOT_STAGING)
    {
      if (!staging_setup)
      {
        arm.ArmCountSetPoint = 0;
        arm.open_gripper();
        staging_setup = true;
        approaching = true;
        arm.SetPIDEffort();
      }
      if (approaching)
      {
        arm.SetPIDEffort();
        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 3.2)
        {
          body.brake();
          approaching = false;
          arm.close_gripper();
        }
      }
      if (key == Enter_Save)
      {
        backing_up = true;
      }
      if (backing_up)
      {
        body.turn(1);
        backing_up = false;
      }
    }
    if (angle == ROBOT_25)
    {
      if (!staging_setup)
      {
        arm.ArmCountSetPoint = 3600;
        staging_setup = true;
        approaching = true;
        Serial.println("Switching to appraoching");
      }
      if (approaching)
      {
        arm.open_gripper();

        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 11.6)
        {
          Serial.println("Distance Away");
          body.brake();
          approaching = false;
          arm.close_gripper();
        }
      }
      if (key == Enter_Save)
      {

        backing_up = true;
      }
      if (backing_up)
      {
        body.turn(2);
        backing_up = false;
      }
    }
    if (angle == ROBOT_45)
    {
      if (!staging_setup)
      {
        arm.ArmCountSetPoint = 3500;
        staging_setup = true;
        approaching = true;
        Serial.println("Switching to appraoching");
      }
      if (approaching)
      {
        arm.open_gripper();

        body.followline(100);
        float distance = body.getDistanceCM();
        if (distance < 11.6)
        {
          Serial.println("Distance Away");
          body.brake();
          approaching = false;
          arm.close_gripper();
        }
      }
      if (key == Enter_Save)
      {
        arm.close_gripper();
        backing_up = true;
      }
      if (backing_up)
      {
        body.SetEffort(-.1);
        delay(500);
        body.brake();
        backing = false;
      }
    
    break;
  }
  // if(angle == ROBOT_45){
  //     if(!staging_setup){
  //       arm.ArmCountSetPoint=3600;
  //       staging_setup=true;
  //       approaching = true;
  //       Serial.println("Switching to appraoching");
  //     }
  //     if(approaching){
  //       arm.open_gripper();

  //       body.followline(100);
  //       float distance = body.getDistanceCM();
  //       if(distance < 11.6){
  //         Serial.println("Distance Away");
  //         body.brake();
  //         approaching = false;

  //       }
  //     }
  //     if(key == Enter_Save){
  //       c
  //       backing_up = true;
  //     }
  //     if(backing_up){
  //       body.turn(2);
  //       backing_up=false;
  //     }
  // }
}
}
