#include <Arduino.h>
#include <chassis.h>
#include <RBE1001Lib.h>
#include <IRdecoder.h>
#include <BlueMotor.h>
#include <arm.h>
#include <PID_v1.h>
Chassis body;

const int TrigPin = 23;
const int EchoPin = 22;
const int PhotoResistorR = 39;
const int PhotoResistorL = 36;
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
void setup() {
    Serial.begin(115200);
    body.AttachComponents(EchoPin,TrigPin,PhotoResistorL,PhotoResistorR);
    arm.setup();
}

void loop() {
arm.gripper.write(165);
}