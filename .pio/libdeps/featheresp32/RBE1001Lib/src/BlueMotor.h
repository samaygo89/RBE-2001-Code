#pragma once

class BlueMotor {
 public:
  void setEffort(int effort);
  long getPosition();
  void reset();
  void setup();
  void forwards();
  void backwards();
  //    static portMUX_TYPE mux;
  void setEffort(int effort, bool clockwise);
  
  const int PWM = 2;
  const int AIN2 = 21;
  const int AIN1 = 19;
  const int ENCA = 18;
  const int ENCB = 5;
};