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

void setup() {
  //USB Serial
  Serial.begin(115200);

}

//int loopCount = 0;
void loop() {
//  loopCount++;
  
  Serial.print("In loop with 115200: ");
//  Serial.println(loopCount);

  delay(1000);
}
