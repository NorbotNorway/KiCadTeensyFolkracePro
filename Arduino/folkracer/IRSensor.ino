#include <Wire.h>
extern "C"
{
  #include "utility/twi.h" //from Wire library, so we can do bus scanning
}

int getSensorDistanceInCm(int sensornumber)
{
  tcaSelect(sensornumber);
}

void tcaSelect(uint8_t i)
{
  if (i > 7) return;

  Wire.beginTransmission(TCA_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();

  Serial.print("TCA: ");
  Serial.println(i);
  
}
