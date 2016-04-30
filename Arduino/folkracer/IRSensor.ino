

void tcaSelect(uint8_t i)
{
  if (i > 7) return;

  //Trace("About to change TCA");

  Wire.beginTransmission(TCA_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();

  //Serial.print("TCA: ");
  //Serial.println(i);
  //Trace("TCA changed");
}

int readI2Csensor()
{
  return 234;
}

int getSensorDistanceInCm(int sensornumber)
{
  //Set active channel on the TCA I2C multiplexer
  tcaSelect(sensornumber);
  int cm = readI2Csensor();
  return cm;
}
