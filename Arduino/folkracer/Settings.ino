
//#define SETTINGS_ALL 5;


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
}




