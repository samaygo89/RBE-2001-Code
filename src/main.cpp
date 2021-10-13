#include <Arduino.h>
#include <chassis.h>
#include <RBE1001Lib.h>
#include <IRdecoder.h>
#include <BlueMotor.h>
#include <arm.h>
#include <IR_Buttons.h>
#include <PID_v1.h>
Chassis body;
const uint8_t IR_DETECTOR_PIN = 34;//Figure out
IRDecoder decoder(IR_DETECTOR_PIN);
const int TrigPin = 23;
const int EchoPin = 22;
const int PhotoResistorR = 39;
const int PhotoResistorL = 36;
Arm arm;
enum STATE
{
  IDLE,
  LINING,
  DROPPING_OFF_PLATE,
  PICKING_UP_PLATE
};
enum ANGLE
{
  ROBOT_25,
  ROBOT_45
};
STATE robot_state=IDLE;
ANGLE target_angle;
void setup() {
    Serial.begin(115200);
    body.AttachComponents(EchoPin,TrigPin,PhotoResistorL,PhotoResistorR);
    arm.setup();
    decoder.init();
    ESP32PWM::allocateTimer(2);
}
int value=0;
void loop() {
    arm.SetArmEffort(255);
    //Serial.print("hi");
    //arm.SetArmEffort(value);
    //arm.open_gripper();
    //delay(1000);
    //arm.SetArmEffort(-value);
    //arm.close_gripper();
    //delay(1000);

    
}