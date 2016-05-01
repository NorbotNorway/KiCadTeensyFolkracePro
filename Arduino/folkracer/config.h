//TCA9548APWR (https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout?view=all)
#define TCA_ADDRESS 0x70

const int SERVO_STEERING_MIN = 1300; //us
const int SERVO_STEERING_MAX = 1700; //us
const int SERVO_MOTOR_MAX = 1900;
const int SERVO_MOTOR_MIN = 1100;
const int LED_SLOW_BLINK = 750; //ms
const int LED_FAST_BLINK = 200; //ms

//Serial
const int SERIAL_BAUD_USB = 9600;
const int SERIAL_BAUD_BLUETOOTH = 9600;

//Pins
const int LED_PIN = 13;
const int SERVO_MOTOR_PIN = 3;
const int SERVO_STEERING_PIN = 4;
const int STARTMODULE_PIN = 5;

//Startmodule
enum startmoduleStates {
  WAITING,
  RUNNING,
  STOP,
  MANUAL
};
