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
TraceNoLine("first:" );
Trace(first);
TraceNoLine("second:");
Trace(second);
    return (second << 8) + first;
  }
  else 
    return -1;
}

void set(String name, int value)
{
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
    Trace(first);
    Trace(second);
    EEPROM.write(SETTING_STEERING_MIN, first);
    EEPROM.write(SETTING_STEERING_MIN+1, second);
    //EEPROM.write(SETTING_STEERING_MIN, value);
  }

  car.config = getConfigurationFromEEPROM(); //Reloads entire configuration everytime a value is set.
}

Configuration getConfigurationFromEEPROM()
{
  Configuration config;
  
  config.maxspeed = get("maxspeed");
  config.disablemotor = get("disablemotor") != 0;
  config.plotspeed = EEPROM.read(SETTING_PLOT_SPEED) != 0;
  config.plotsensors = EEPROM.read(SETTING_PLOT_SENSORS) != 0;
  return config;
}

void printConfiguration()
{
  TraceNoLine("\tMaxSpeed:\t");
  Trace(car.config.maxspeed);
  TraceNoLine("\tDisableMotor:\t");
  Trace(car.config.disablemotor);
  TraceNoLine("\tPlotSpeed:\t");
  Trace(car.config.plotspeed);
  TraceNoLine("\tPlotSensors:\t");
  Trace(car.config.plotsensors);
}
