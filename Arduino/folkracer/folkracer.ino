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

 //#include <SoftwareSerial.h> //For Bluetooth
 //SoftwareSerial bluetooth(1,2);

 const int LED_PIN = 13;

void setup() {
  //USB Serial
  Serial.begin(115200);

  //Onboard LED
  pinMode(LED_PIN, OUTPUT);

  //Bluetooth
  Serial1.begin(9600);
  Serial1.println("Bluetooth active via Serial1");
  //bluetooth.begin(9600);
  //bluetooth.println("Bluetooth active");

}

int loopCount = 0;
void loop() {
  loopCount++;
  
  Serial.print("In loop with 115200: ");
  Serial.println(loopCount);

  //digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  //bluetooth.println("From Bluetooth");
  //int bdata = bluetooth.read();
  Serial1.println("From Bluetooth via Serial1");
  int bdata = Serial1.read();
  if (bdata == '1') {
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    digitalWrite(LED_PIN, HIGH);
  }

  delay(100);
}
