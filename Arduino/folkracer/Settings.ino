#define SETTINGS_SPEED 1
#define SETTINGS_AVG 2
#define SETTINGS_ALL 5;

struct CarSettings {
  int speed;
  int direction;
};

int getSetting(String name)
{
  if (name == "speed")
    return EEPROM.read(SETTINGS_SPEED);
  else if (name == "avg")
    return EEPROM.read(SETTINGS_AVG);
  else 
    return 0;
}

void set(String name, int value)
{
  //Trace("Setting " + name + " to " + value);
  if (name == "speed")
    EEPROM.write(SETTINGS_SPEED, value);
  else if (name == "avg")
    EEPROM.write(SETTINGS_AVG, value);
}




