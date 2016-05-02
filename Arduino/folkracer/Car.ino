void carWait()
{
  setSpeed(0);
  turnTo(0);
  //ledBlink(LED_SLOW_BLINK);
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
  int newDirection = 0;
  
  //Retrieve ranges from all sensors
  int sensor0 = getSensorDistanceInCm(0);
  int sensor1 = getSensorDistanceInCm(1);
  int sensor7 = getSensorDistanceInCm(7);

  //Find the center of the raceway. Then figure out how far we are from there, and how to get us there.
  //int center = (sensor0 + sensor7) / 2;
  int value = (sensor0 * 100) / (sensor1 + sensor0);
  value = constrain(value, 0, 100);
  value = map(value, 0, 100, -90, 90);
  newDirection = value;
  
  //TODO, reverse direction if we're reversing
  
  return newDirection;
}


