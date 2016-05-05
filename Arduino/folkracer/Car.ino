

void carWait()
{
  setSpeed(0);
  turnTo(0);
  car.speed = 0;
  car.direction = 0;
  //ledBlink(LED_SLOW_BLINK);
}



void carDrive()
{
  int speed = calculateMotorSpeed();
  int direction = calculateDirection();
  car.speed = speed;
  car.direction = direction;

  //setSpeed(CarSettings.speed);
  if (!car.config.disablemotor)
    setSpeed(speed);
  turnTo(direction);
}

void carStop()
{
  ledBlink(LED_FAST_BLINK);
  car.speed = 0;
  car.direction = 0;
  setSpeed(0);
  turnTo(0);
}

int calculateMotorSpeed()
{
  int sensor7 = getSensorDistanceInCm(7);
  if (sensor7 < 20)
    return 0;
  
  //return get("maxspeed"); //TODO
  return car.config.maxspeed;
}

int calculateDirection()
{
  int newDirection = 0;
  
  //Retrieve ranges from all sensors
  int minimum = 10;
  int sensor0 = getSensorDistanceInCm(0)-minimum;
  int sensor1 = getSensorDistanceInCm(1)-minimum-1;

  //Alternative 1
  //Find the center of the raceway. Then figure out how far we are from there, and how to get us there.
  //int center = (sensor0 + sensor1) / 2;
  //int error = sensor0 - center; //This is how many centimeters we are from the nominal path
  //A large error should make wheels turn sharply, while a small error should just cause smaller adjustments.
  //newDirection = error * 

  //Alternative 2
  int value = (sensor0 * 100) / (sensor1 + sensor0);
  value = constrain(value, 0, 100);
  value = map(value, 0, 100, -90, 90);
  newDirection = value;
  
  //Trace to Plotter?
  if (car.config.plotsensors)
  {
    TraceNoLine(newDirection);
    TraceNoLine(",");
    TraceNoLine(sensor0);
    TraceNoLine(",");
    Trace(sensor1);
  }

  //TODO, reverse direction if we're reversing
  
  return newDirection;
}


