

void setSpeed(int speed)
{
  int microseconds = map(speed, -100, 100, SERVO_MOTOR_MIN, SERVO_MOTOR_MAX);
  microseconds = constrain(microseconds, SERVO_MOTOR_MIN, SERVO_MOTOR_MAX);
  servoMotor.writeMicroseconds(microseconds);
}

