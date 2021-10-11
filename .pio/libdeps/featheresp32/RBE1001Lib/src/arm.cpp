#include <arm.h>

void Arm::setup(){
ArmMotor.setup();
ESP32PWM::allocateTimer(1);
gripper.attach(SERVO_PIN);
ArmMotor.reset();
servoPositionFeedback.attach(SERVO_FEEDBACK_SENSOR);
ArmCountSetPoint=0;
}


void Arm::SetArmEffort(float effort){
ArmMotor.setEffort(effort);
}

int volatile error;
int volatile prev_error;
int volatile errorsum;
int volatile prev_time;
int volatile currtime;
float Kp=0;
float Kd=0;
float Ki=0;
float PID;
int deadband=35;
int Arm::SetPIDEffort(){
error = this->ArmCountSetPoint - this->ArmMotor.getPosition();
currtime = millis();
PID = Kp*error+Ki*error*(currtime-prev_time)-Kd*(error-prev_error)/(currtime-prev_time);
this->SetArmEffort(PID);
}
