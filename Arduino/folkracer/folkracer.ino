/*
 * Frodes Folkrace car for Gothenburg 2016
 * 
 * Features;
 * - Three GP2Y0E02B Sharp Sensors, I2C, 4-50cm
 * - Servo for steering
 * - Servo for motor speed
 * - Bluetooth (for debugging)
 *    - Get telemetry back from car for analysis
 *    - Send commands to car for remote control
 * - Two WS2812b neopixel leds
 * - EEPROM (on Teensy) for configuration
 */
#include <Wire.h>
extern "C"
{
  #include "utility/twi.h" //from Wire library, so we can do bus scanning
}
#include <EEPROM.h>
#include "config.h" 

void setup() {
  //USB Serial
  Serial.begin(SERIAL_BAUD_USB);

  //Onboard LED
  pinMode(LED_PIN, OUTPUT);

  //Bluetooth
  Serial1.begin(SERIAL_BAUD_BLUETOOTH);

  //I2C
  Wire.begin();
  delay(50);

  Trace("Setup completed");
}

int loopCount = 0;
void loop() {
  //Trace("Loop start");
  loopCount++;
  
  //digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  while(Serial1.available())
  {
    String command = Serial1.readStringUntil('\r');
    Run(command);
  }
  
  //delay(100);
}
