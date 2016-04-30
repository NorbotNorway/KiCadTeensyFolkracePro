#include <Adafruit_NeoPixel.h>
#ifndef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>
extern "C"
{
  #include "utility/twi.h" //from Wire library, so we can do bus scanning
}

/*
 * Frode Lillerud, april 2016
 * Folkrace code for KicadTeensyFolkracePro board
 */

//TCA9548APWR (https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout?view=all)
#define TCA_ADDRESS 0x70

//Sharp GP2Y0E02B i2c sensor
#define SENSOR_ADDRESS  0x80 >> 1
#define DISTANCE_REG    0x5E
#define SHIFT           0x35

int distance = 0;
int shift = 0;
byte hi,low;

const int PIN_LED = 13;

//NeoPixel, WS2812B LEDs
//int LED_COUNT = 2;
//int LED_PIN = 12;
//Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void tcaSelect(uint8_t i)
{
  if (i > 7) return;

  Wire.beginTransmission(TCA_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();

  Serial.print("TCA: ");
  Serial.println(i);
  
}

void setup() {

  //USB serial
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting Serial");
  
  //NeoPixels
  //leds.begin();
  //leds.show();

  Wire.begin();
  delay(50);

  pinMode(PIN_LED, OUTPUT);

/*

  tcaSelect(0);

  Serial.println("Starting Wire");
  
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(SHIFT);
  Wire.endTransmission();

  Wire.requestFrom(SENSOR_ADDRESS, 1);
  while(Wire.available() == 0); //wait here...
  Serial.println("Wire available");
  shift = Wire.read();
*/
}

void loop() {

 // digitalWrite(PIN_LED, !digitalRead(PIN_LED));

  for (int s = 0; s <= 1; s++)
  {

    tcaSelect(s);

    Serial.println("About to request from Wire");

    Wire.beginTransmission(SENSOR_ADDRESS);
    Wire.write(DISTANCE_REG);
    Wire.endTransmission();

    Serial.println("endTransmission called");

    Wire.requestFrom(SENSOR_ADDRESS, 2);
    while (Wire.available() < 2);

    Serial.println("Found data");

    hi = Wire.read();
    low = Wire.read();

    distance = (hi * 16 + low) / 16 / (int)pow(2, shift);

    Serial.println(distance);

    if (distance < 100)
    {
      //leds.setPixelColor(1, 30, 230, 30);
      digitalWrite(PIN_LED, LOW);
    }
    else
    {
      //leds.setPixelColor(1, 230, 30, 30);
      digitalWrite(PIN_LED, HIGH);
    }
  }
  
// leds.show();
 
 delay(30);
  
}
