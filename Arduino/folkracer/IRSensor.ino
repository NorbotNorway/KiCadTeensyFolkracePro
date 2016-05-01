//GP2Y0E02B I2C sensor
#define SENSOR_ADDRESS  0x80 >> 1
#define DISTANCE_REG    0x5E
#define SHIFT           0x35

void tcaSelect(uint8_t i)
{
  if (i > 7) return;

  Wire.beginTransmission(TCA_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();
}

int shift = 0;
byte hi,low;
int distance;
void setupIRSensors()
{
    Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(SHIFT);
  Wire.endTransmission();

  Wire.requestFrom(SENSOR_ADDRESS, 1);
  while (Wire.available() == 0);
  //Serial.println("Wire available!");
  shift = Wire.read();
}

int readI2Csensor()
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

int getSensorDistanceInCm(int sensornumber)
{
  //Set active channel on the TCA I2C multiplexer
  tcaSelect(sensornumber);
  int cm = readI2Csensor();
  return cm;
}
