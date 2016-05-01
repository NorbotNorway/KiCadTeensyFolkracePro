//TCA9548APWR (https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout?view=all)
#define TCA_ADDRESS 0x70



//Serial
const int SERIAL_BAUD_USB = 115200;
const int SERIAL_BAUD_BLUETOOTH = 9600;

//Pins
const int LED_PIN = 13;

//Startmodule
enum startmoduleStates {
  WAITING,
  RUNNING,
  STOP,
  MANUAL
};
