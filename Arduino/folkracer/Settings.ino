/*
 * Read and write to the EEPROM
 */

int get(String name)
{
  if (name == "speed")
    return EEPROM.read(SETTING_SPEED);
  else if (name == "maxspeed")
    return EEPROM.read(SETTING_MAX_SPEED);
  else if (name == "avg")
    return EEPROM.read(SETTING_AVG);
  else if (name == "disablemotor")
    return EEPROM.read(SETTING_DISABLE_MOTOR);
  else if (name == "plotsensors")
    return EEPROM.read(SETTING_PLOT_SENSORS);
  else if (name == "plotspeed")
    return EEPROM.read(SETTING_PLOT_SPEED);
  else if (name == "steeringmin")
  {
    byte first = EEPROM.read(SETTING_STEERING_MIN);
    byte second = EEPROM.read(SETTING_STEERING_MIN+1);
    return (second << 8) + first;
  }
  else if (name == "steeringmax")
  {
    byte first = EEPROM.read(SETTING_STEERING_MAX);
    byte second = EEPROM.read(SETTING_STEERING_MAX+1);
    return (second << 8) + first;
  }
  else if (name == "crashdist")
    return EEPROM.read(SETTING_CRASH_DIST);
  else if (name == "minspeed")
    return EEPROM.read(SETTING_MIN_SPEED);
  else if (name == "turngain")
    return EEPROM.read(SETTING_TURN_GAIN);
  else if (name == "loopdelay")
    return EEPROM.read(SETTING_LOOP_DELAY);
  else if (name == "reducespeedangle")
    return EEPROM.read(SETTING_REDUCE_SPEED_ANGLE);
  else if (name == "reducespeedby")
    return EEPROM.read(SETTING_REDUCE_SPEED_BY);
  else 
    return -32768; //Int.Min
}

void set(String name, int value)
{
  //First, write the setting to EEPROM
  //Trace("Setting " + name + " to " + value);
  if (name == "speed")
    EEPROM.write(SETTING_SPEED, value);
  else if (name == "maxspeed")
    EEPROM.write(SETTING_MAX_SPEED, value);
  else if (name == "avg")
    EEPROM.write(SETTING_AVG, value);
  else if (name == "disablemotor")
    EEPROM.write(SETTING_DISABLE_MOTOR, value);
  else if (name == "plotsensors")
    EEPROM.write(SETTING_PLOT_SENSORS, value);
  else if (name == "plotspeed")
    EEPROM.write(SETTING_PLOT_SPEED, value);
  else if (name == "steeringmin")
  {
    byte first = (value >> (8*0)) & 0xff;
    byte second = (value >> (8*1)) & 0xff;
    EEPROM.write(SETTING_STEERING_MIN, first);
    EEPROM.write(SETTING_STEERING_MIN+1, second);
  }
  else if (name == "steeringmax")
  {
    byte first = (value >> (8*0)) & 0xff;
    byte second = (value >> (8*1)) & 0xff;
    EEPROM.write(SETTING_STEERING_MAX, first);
    EEPROM.write(SETTING_STEERING_MAX+1, second);
  }
  else if (name == "crashdist")
    EEPROM.write(SETTING_CRASH_DIST, value);  
  else if (name == "minspeed")
    EEPROM.write(SETTING_MIN_SPEED, value);
  else if (name == "turngain")
    EEPROM.write(SETTING_TURN_GAIN, value);
  else if (name == "loopdelay")
    EEPROM.write(SETTING_LOOP_DELAY, value);
  else if (name == "reducespeedangle")
    EEPROM.write(SETTING_REDUCE_SPEED_ANGLE, value);
  else if (name == "reducespeedby")
    EEPROM.write(SETTING_REDUCE_SPEED_BY, value);

  //And then, reload entire configuration from EEPROM
  car.config = getConfigurationFromEEPROM(); 
}

Configuration getConfigurationFromEEPROM()
{
  Configuration config;
  
  config.maxspeed = get("maxspeed");
  config.disablemotor = get("disablemotor") != 0;
  config.plotspeed = get("plotspeed") != 0;
  config.plotsensors = get("plotsensors") != 0;
  config.servo_steering_min = get("steeringmin");
  config.servo_steering_max = get("steeringmax");
  config.crashdist = get("crashdist");
  config.minspeed = get("minspeed");
  config.turngain = get("turngain");
  config.loopdelay = get("loopdelay");
  config.reducespeedangle = get("reducespeedangle");
  config.reducespeedby = get("reducespeedby");
  return config;
}

void printConfiguration()
{
  TraceNoLine("\tMaxSpeed:\t");
  Trace(car.config.maxspeed);
  TraceNoLine("\tMinSpeed:\t");
  Trace(car.config.minspeed);
  TraceNoLine("\tDisableMotor:\t");
  Trace(car.config.disablemotor);
  TraceNoLine("\tPlotSpeed:\t");
  Trace(car.config.plotspeed);
  TraceNoLine("\tPlotSensors:\t");
  Trace(car.config.plotsensors);
  TraceNoLine("\tServo Steering Min:\t");
  Trace(car.config.servo_steering_min);
  TraceNoLine("\tServo Steering Max:\t");
  Trace(car.config.servo_steering_max);
  TraceNoLine("\tCrashDist:\t");
  Trace(car.config.crashdist);
  TraceNoLine("\tTurnGain:\t");
  Trace(car.config.turngain);
  TraceNoLine("\tLoopDelay:\t");
  Trace(car.config.loopdelay);
  TraceNoLine("\tReduceSpeedAngle:\t");
  Trace(car.config.reducespeedangle);
  TraceNoLine("\tReduceSpeedBy:\t");
  Trace(car.config.reducespeedby);
}
