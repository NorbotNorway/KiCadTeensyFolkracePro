/*
 * TODO
 * EEPROM for TurnGain
 * EEPROM for LoopDelay
 * EEPROM for ReduceSpeedAngle
 * EEPROM for ReduceSpeedBy
 * 
 */

/*
   Frodes Folkrace car for Gothenburg 2016

   Features;
   - Three GP2Y0E02B Sharp Sensors, I2C, 4-50cm
   - Servo for steering
   - Servo for motor speed
   - Bluetooth (for debugging)
      - Get telemetry back from car for analysis
      - Send commands to car for remote control
   - Two WS2812b neopixel leds
   - EEPROM (on Teensy) for configuration
*/

/*
 * A Car has some configuration values which are mostly pretty static. They are only changed when configuring the Car before a race.
 * A Car also has some running values which are updated all the time during the race, like speed, direction and state.
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
volatile startmoduleStates startmodule_state = WAITING;

struct Configuration {
  int maxspeed;
  int minspeed;
  bool disablemotor;
  bool plotspeed = false;
  bool plotsensors = false;
  int servo_steering_min = 1300; //us
  int servo_steering_max = 1700; //us
  //int connectorsensorfront;
  int crashdist;
  int turngain;
  int loopdelay;
  int reducespeedangle;
  int reducespeedby;
};

struct Car {
  int speed;
  int direction;
  Configuration config;
  //startmoduleStates state; //TODO
};

Car car;

void setup() {
  //Serial via USB
  Serial.begin(SERIAL_BAUD_USB);
  //Serial via Bluetooth
  Serial1.begin(SERIAL_BAUD_BLUETOOTH);
  delay(1000);
  Trace("******* Setup starting... ********");
  Trace("Serial started for both USB and Bluetooth");

  //Onboard LED
  pinMode(LED_PIN, OUTPUT);

  //I2C
  TraceNoLine("Starting Wire..");
  Wire.begin();
  delay(100);
  Trace("OK");

  //Connect servos
  TraceNoLine("Setting up servos...");
  servoSteering.attach(SERVO_STEERING_PIN);
  servoMotor.attach(SERVO_MOTOR_PIN);
  Trace("OK");

  //Enable IR sensors
  TraceNoLine("Setting up sensors...");
  setActiveSensor(0);
  setupIRSensors();
  Trace("OK");

  //Listen for changes on the Startmodule
  TraceNoLine("Setting up Startmodule...");
  pinMode(STARTMODULE_PIN, INPUT);
  attachInterrupt(STARTMODULE_PIN, changeStartmoduleState, CHANGE);
  startmodule_state = WAITING;
  Trace("OK");

  TraceNoLine("Getting configuration from EEPROM...");
  car.config = getConfigurationFromEEPROM();
  Trace("OK");

  Trace("Current configuration:");
  printConfiguration();

  Trace("******* Setup completed! ********");
}

void loop() {

//  int a = getAveragSensorDistanceInCm(7);
//  int r = getSensorDistanceInCm(7);
//  TraceNoLine(a);
//  TraceNoLine(",");
//  Trace(r);
//  return;

  //Any incoming bluetooth commands?
  while (Serial1.available())
  {
    //Trace("Incoming command...");
    String command = Serial1.readStringUntil('\r');
    Run(command);
  }

  if (startmodule_state == WAITING)
  {
    carWait();
  }
  else if (startmodule_state == RUNNING)
  {
    carDrive();
  }
  else if (startmodule_state == STOP)
  {
    carStop();
  }
  else if (startmodule_state == MANUAL)
  {
    //Trace("In MANUAL mode");
  }
  else
  {
    TraceNoLine("Unknown startmodule_state: ");
    Trace(startmodule_state);
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
  delay(car.config.loopdelay);
}

