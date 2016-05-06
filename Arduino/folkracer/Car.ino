

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
  car.speed = speed;
  int direction = calculateDirection();
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
  int speed = 0;
  
  int frontSensorConnector = 7; //TODO, move to EEPROM?
  //int frontSensor = getSensorDistanceInCm(frontSensorConnector); //Front sensor
  int frontSensor = getAveragSensorDistanceInCm(frontSensorConnector);
  if (frontSensor < car.config.crashdist)
    speed = car.config.maxspeed * -1;
  else
    speed = car.config.maxspeed;

  //If we're turning, then reduce speed
  if (car.direction < -1*car.config.reducespeedangle || car.direction > car.config.reducespeedangle)
    speed = speed / car.config.reducespeedby;

  //Ensure we don't go below the stall speed
  if (speed > 0 && speed < car.config.minspeed)
    speed = car.config.minspeed;
  else if (speed < 0 && speed > car.config.minspeed*-1)
    speed = car.config.minspeed * -1;

  if (car.config.plotspeed)
  {
    Trace(speed);
  }
  
  return speed; 
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
  if (car.speed < 0)
    newDirection *= -1;

  //if (newDirection < 0 && newDirection > -40)
//    newDirection = -40;
//  else if (newDirection > 0 && newDirection < 40)
    //newDirection = 40;
  //if (newDirection > 30)
//    newDirection = 75;
//  else if (newDirection < 30)
    //newDirection = -75;

    newDirection *= car.config.turngain;
  
  return newDirection;
}


