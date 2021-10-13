#pragma once

#include <Esp32WifiManager.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32AnalogRead.h>

#include "Rangefinder.h"
#include "Motor.h"

// Pins used by a perpheral, may be re-used
#define BOOT_FLAG_PIN 0
#define SERIAL_PROGRAMMING_TX 1
#define SERIAL_PROGRAMMING_RX 3

//#define AIN1 23
//#define AIN2 19
//#define ENCA 18
//#define ENCB 5



//A4
#define LEFT_LINE_SENSE 36
//A3
#define RIGHT_LINE_SENSE 39
//A2
#define IR 34
/**
 * Gripper pin for Servo
 */
#define SERVO_PIN 33

#define MOTOR_DISABLE 15

/**
 * Drive motor 1 10Khz full duty PWM pin
 */
#define MOTOR_LEFT_PWM 13
/**
 * Pin for setting the direction of the H-Bridge
 */
//A5
#define MOTOR_LEFT_DIR 4
/**
 * Drive motor 2 10Khz full duty PWM pin
 */
#define MOTOR_RIGHT_PWM 12
/**
 * Pin for setting the direction of the H-Bridge
 */
//A1
#define MOTOR_RIGHT_DIR 25
//Encoder pins

#define MOTOR_LEFT_ENCA 27
//A0
#define MOTOR_LEFT_ENCB 26

#define MOTOR_RIGHT_ENCA 32
#define MOTOR_RIGHT_ENCB 14

class LeftMotor : public Motor
{
public:
    LeftMotor() : Motor{MOTOR_LEFT_PWM, MOTOR_LEFT_DIR, MOTOR_LEFT_ENCA, MOTOR_LEFT_ENCB} {}
};

class RightMotor : public Motor
{
public:
    RightMotor() : Motor{MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR, MOTOR_RIGHT_ENCA, MOTOR_RIGHT_ENCB} {}
};
