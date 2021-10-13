#include "BlueMotor.h"
#include <RBE1001Lib.h>

long volatile count = 0;  // encoder counter
int volatile prev_val=0;
// Mutex for the count critical variable
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

/**
 * Interrupt service routine (ISR) for one of the encoder
 * channels. It simply counts how many interrupts occured
 */
const int EncoderArray[4][4] = {
{0,-1,1,0},
{1,0,0,-1},
{-1,0,0,1},
{0,1,-1,0}
};

void IRAM_ATTR isr() {
  portENTER_CRITICAL_ISR(&mux);
  int new_val = (digitalRead(5) << 1) | digitalRead(18);
  count += EncoderArray[prev_val][new_val];
  prev_val = new_val;
  portEXIT_CRITICAL_ISR(&mux);
}



  /**
 * Set up all the variables for the blue motor
 * This is not the same as the ESP32 setup() function, although
 * that would be a good place to call this setup function
 */
void BlueMotor::setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  pinMode(PWM, OUTPUT);
  attachInterrupt(ENCA, isr, CHANGE);
  attachInterrupt(ENCB,isr,CHANGE);
}

/**
 * Get the current encoder count
 * Returns the encoder count value
 */
long BlueMotor::getPosition() {
  long value;
  portENTER_CRITICAL(&mux);
  value = count;
  portEXIT_CRITICAL(&mux);
  return value;
}

/**
 * Reset the encoder count to zero
 */
void BlueMotor::reset() {
  portENTER_CRITICAL(&mux);
  count = 0;
  portEXIT_CRITICAL(&mux);
}

/**
 * Set the motor effort
 * effort value ranges from -255 to +255
 * Negative values turn one way, positive values turn the other way
 */
void BlueMotor::setEffort(int effort) {
  if (effort < 0) {
    setEffort(-effort, true);
  } else {
    setEffort(effort, false);
  }
}

/**
 * Set the motor effort
 * effort values range from 0-255
 * clockwise is true for one direction, false for the other
 */
void BlueMotor::setEffort(int effort, bool clockwise) {
  if (clockwise) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  int value = constrain(effort, 0, 255);
  analogWrite(PWM, value);
}
void BlueMotor::forwards(){
  digitalWrite(AIN1, HIGH);  
  digitalWrite(AIN2, LOW);  
  digitalWrite(PWM, HIGH);
}