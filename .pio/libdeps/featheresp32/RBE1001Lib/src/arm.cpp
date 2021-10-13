#include <arm.h>

void Arm::setup(){
ArmMotor.setup();
ESP32PWM::allocateTimer(1);
gripper.attach(SERVO_PIN);
ArmMotor.reset();
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
if(currtime>prev_time+10){
PID = Kp*error  +  Ki*error*(currtime-prev_time)  -  Kd*(error-prev_error)/(currtime-prev_time);
this->SetArmEffort(PID);
prev_time=currtime;
prev_error=error;
}


}

int open_angle=19;
int closed_angle=160;
void Arm::open_gripper(){
 gripper.write(closed_angle);;
}
void Arm::close_gripper(){
 gripper.write(open_angle);
}