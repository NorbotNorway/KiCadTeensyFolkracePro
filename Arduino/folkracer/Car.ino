void carWait()
{
  setSpeed(0);
  turnTo(0);
  //ledBlink(LED_SLOW_BLINK);
}

/*
struct CarSettings {
  int speed;
  int direction;
};*/

void carDrive()
{
  int speed = calculateMotorSpeed();
  int direction = calculateDirection();

  //setSpeed(CarSettings.speed);
  if (EEPROM.read(SETTING_DISABLE_MOTOR) == 0)
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
  int sensor7 = getSensorDistanceInCm(7);
  if (sensor7 < 20)
    return 0;
  
  return get("maxspeed"); //TODO
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
  if (EEPROM.read(SETTING_PLOT_SENSORS) > 0)
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


