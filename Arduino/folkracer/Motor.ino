/*
 * Control the forward/reverse motion of the car with Servo
 */

void setSpeed(int speed)
{
  int maxSpeed = get("maxspeed"); //EEPROM.read(SETTING_MAX_SPEED);
  if (speed > maxSpeed)
    speed = maxSpeed;
  
  int microseconds = map(speed, -100, 100, SERVO_MOTOR_MIN, SERVO_MOTOR_MAX);
  microseconds = constrain(microseconds, SERVO_MOTOR_MIN, SERVO_MOTOR_MAX);
  servoMotor.writeMicroseconds(microseconds);

  //TraceNoLine("Motor speed set to ");
  //Trace(speed);
}


