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
  
  const int PWM = 23;
  const int AIN2 = 19;
  const int AIN1 = 21;
  const int ENCA = 5;
  const int ENCB =18;
};