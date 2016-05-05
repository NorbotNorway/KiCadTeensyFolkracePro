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

const int numReadings = 15; //TODO - get from EEPROM
const int sensorCount = 25; //i.e. Max number of Sharp IR sensors
int totals[sensorCount];
int readings[sensorCount][numReadings];
int readIndexes[sensorCount];

int getAveragSensorDistanceInCm(int sensorNumber)
{
  delay(10);
  //TraceNoLine("Totals: ");
  //Trace(totals[sensorNumber]);
  totals[sensorNumber] = totals[sensorNumber] - readings[readIndexes[sensorNumber]][sensorNumber];
  //Trace("Totals: ");
  //Trace(totals[sensorNumber]);
  int cm = getSensorDistanceInCm(sensorNumber);
  readings[readIndexes[sensorNumber]][sensorNumber] = cm;
  totals[sensorNumber] = totals[sensorNumber] + cm;
  readIndexes[sensorNumber] = readIndexes[sensorNumber] + 1;
  if (readIndexes[sensorNumber] > numReadings)
    readIndexes[sensorNumber] = 0;

  return totals[sensorNumber] / numReadings;
}


