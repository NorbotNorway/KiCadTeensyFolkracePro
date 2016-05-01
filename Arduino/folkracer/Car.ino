void carWait()
{
  setSpeed(0);
  turnTo(0);
  ledBlink(LED_SLOW_BLINK);
}

void carDrive()
{
  int speed = calculateMotorSpeed();
  int direction = calculateDirection();

  setSpeed(speed);
  turnTo(direction);
}

void carStop()
{
  ledBlink(LED_FAST_BLINK);
  setSpeed(0);
  turnTo(0);
}

int calculateMotorSpeed()
{
  return 30; //TODO
}

int calculateDirection()
{
  //Retrieve ranges from all sensors
  int sensor0 = getSensorDistanceInCm(0);
  int sensor1 = getSensorDistanceInCm(1);
  int sensor7 = getSensorDistanceInCm(7);

  //Find the center of the raceway. Then figure out how far we are from there, and how to get us there.
  int center = (sensor0 + sensor7) / 2;
  //TODO!!
  
  return -45;
}

