//GP2Y0E02B I2C sensor
#define SENSOR_ADDRESS  0x80 >> 1
#define DISTANCE_REG    0x5E
#define SHIFT           0x35

//Change the channel in the TCA I2C multiplexer
void setActiveSensor(uint8_t i)
{
  if (i > 7) return;

  Wire.beginTransmission(TCA_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();
}

int shift = 0;
byte hi,low;
int distance;
//Initialize I2C sensor
void setupIRSensors()
{
  //TODO, what does the SHIFT register actually contain? And why do we care?
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(SHIFT);
  Wire.endTransmission();

  delay(200); //Sometimes the below code never receives data back... Is this really needed?

  Wire.requestFrom(SENSOR_ADDRESS, 1, false);
  while (Wire.available() == 0)
    Trace("Waiting for TCA to reply...");
  shift = Wire.read();
  //Trace(shift);
}

//Get raw centimeters from the currently selected I2C IR sensor
int readFromActiveSensor()
{
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(DISTANCE_REG);
  Wire.endTransmission();

  Wire.requestFrom(SENSOR_ADDRESS, 2);
  while (Wire.available() < 2);

  hi = Wire.read();
  low = Wire.read();
  distance = (hi * 16 + low) / 16 / (int)pow(2, shift);

  return distance;
}

//Change active sensor, and read its value.
int getSensorDistanceInCm(int sensornumber)
{
  //Set active channel on the TCA I2C multiplexer
  setActiveSensor(sensornumber);
  int cm = readFromActiveSensor();
  return cm;
}

const int numReadings = 6;
const int pinCount = 2; //i.e. more pins than the Teensy has.
int readings[pinCount][numReadings]; //Each "Column" contains the sensorreadings. Each "Row" is used for the different pins.
/*
 * PIN0 - [reading 1], [reading 2], [reading 3], etc...
 * PIN1 - [reading 1], [reading 2], [reading 3], etc...
 * PIN2 - [reading 1], [reading 2], [reading 3], etc...
 * etc...
 */
int readIndexes[pinCount];
int totals[pinCount]; //The sum from each "Row" pr pin.
int getAverageSensorDistanceInCm(int pin)
{
  /*
   * The sensor value for the pin is stored in the array, and a running total is calulcated, and an average is returned.
   */
  totals[pin] = totals[pin] - readings[readIndexes[pin]][pin]; //Remove the oldest sensorreading for this pin.
  int value = getSensorDistanceInCm(pin);   //Get a new value from the sensor.
  Trace(value);
  readings[readIndexes[pin]][pin] = value; //Add the value to the matrix
  totals[pin] = totals[pin] + value;        //Calculate the total
  Trace(totals[pin]);
  readIndexes[pin] = readIndexes[pin] + 1;
  if (readIndexes[pin] > numReadings)
    readIndexes[pin] = 0;

  return totals[pin] / numReadings;
}

int lastLeft;
int lastRight;
int lastFront;
void isRobotStuck()
{
  if (startmodule_state != RUNNING)
    return;
  
  //Returns true if the sensors have not changed in a while
  int right = getSensorDistanceInCm(0);
  int left = getSensorDistanceInCm(1);
  //int front = getSensorDistanceInCm(7);

  Trace(right);
  Trace(lastRight);
  if (abs(right-lastRight) < 3 && abs(left-lastLeft) < 3) //Less than two centimeter change
  {
    ledOn();
    Trace("STUCK!");

    setSpeed(car.config.reversespeed*-1);
    delay(300);
    setSpeed(0); //Stop for a while to avoid tipping the car.
    delay(300);
  }
  else 
  {
    ledOff();
  }

  lastRight = right;
  lastLeft = left;
}


