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
#include <Servo.h>
#include "config.h"

Servo servoSteering;
Servo servoMotor;

void setup() {
  //USB Serial
  Serial.begin(SERIAL_BAUD_USB);

  //Onboard LED
  pinMode(LED_PIN, OUTPUT);

  //Bluetooth
  Serial1.begin(SERIAL_BAUD_BLUETOOTH);

  //I2C
  Wire.begin();
  delay(100);
  
  setupIRSensors();

  //Connect servos
  servoSteering.attach(SERVO_STEERING_PIN);

  delay(3000);

  Trace("Setup completed");  
  

  //set("avg", 5);
  TraceNoLine("Average set to: ");
  Trace(getSetting("avg"));
}

void loop() {
//Trace("loop");
  //Any incoming bluetooth commands?
  while(Serial1.available())
  {
    String command = Serial1.readStringUntil('\r');
    Run(command);
  }

/*
  turnTo(0);
  delay(1000);
  turnTo(-90);
  delay(1000);
  turnTo(90);
  delay(1000);
*/
  /*

  int sensor0 = getSensorDistanceInCm(0);
  int sensor0AVG = getAveragSensorDistanceInCm(0);
  int sensor1 = getSensorDistanceInCm(1);
  int sensor7 = getSensorDistanceInCm(7);

  TraceNoLine(sensor0);
  TraceNoLine(",");
  Trace(sensor0AVG);
  */
 /*
  TraceNoLine(sensor0);
  TraceNoLine(",");
  //Trace(sensor0AVG);
  //TraceNoLine(",");
  TraceNoLine(sensor1);
  TraceNoLine(",");
  Trace(sensor7);
  */
  delay(20);
}
