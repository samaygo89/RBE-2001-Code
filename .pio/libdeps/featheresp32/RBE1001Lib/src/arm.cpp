#include <arm.h>
#include <cmath>

void Arm::setup()
{
    ArmMotor.setup();
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    gripper.attach(SERVO_PIN);
    ArmMotor.reset();
    ArmCountSetPoint = 0; //5700 lift 25 5725 drop25
}

int deadband = 85;
void Arm::SetArmEffort(int effort)
{
    int adjusted_effort = deadband + (255 - deadband) * (effort / 255);
    if (effort < 85)
    {
        adjusted_effort -= 85;
    }
    ArmMotor.setEffort(adjusted_effort);
}

int volatile error;
int volatile prev_error;
int volatile errorsum;
int volatile prev_time;
int volatile currtime;
float Kp = .5;
float Kd = .01;
float Ki = .05;
float PIDEffort=0;

void Arm::SetPIDEffort()
{
    error = ArmCountSetPoint - ArmMotor.getPosition();
    currtime = millis();
    
    if (currtime > prev_time + 10)
    {
        PIDEffort = Kp * error + Ki * error * (currtime - prev_time) - Kd * (error - prev_error) / (currtime - prev_time);
        SetArmEffort(PIDEffort);
        
        prev_time = currtime;
        prev_error = error;
    }
}

int open_angle = 19;
int closed_angle = 160;
void Arm::open_gripper()
{
    gripper.write(closed_angle);
    ;
}
void Arm::close_gripper()
{
    gripper.write(open_angle);
}