void Run(String command)
{
  if (command == "help") {
    Trace("Usage:");
    Trace("led on");
    Trace("led off");
    Trace("get <setting>");
    Trace("set <setting> <value>");
   // Trace("settings");
  }
  else if (command == "led.on") {
      ledOn();
      Trace("->LED turned ON");
  }
  else if (command == "led.off")
  {
    ledOff();
    Trace("->LED turned OFF");
  }
  else if (command.startsWith("led.blink"))
  {
    int blinkCount = command.substring(command.indexOf(' '), 15).toInt();
    for (int i = 0; i < blinkCount; i++)
      ledBlink(200);
    TraceNoLine("->LED blink ");
    Trace(blinkCount);
  }
  else if (command.startsWith("state"))
  {
    String newState = command.substring(command.indexOf(' '), 10);
    //TODO, set new state
  }
  else if (command.startsWith("avg"))
  {
    int newAvg = command.substring(command.indexOf(' '), 10).toInt();
    set("avg", newAvg);
  }
  else if (command.startsWith("steering") || command.startsWith("turn"))
  {
    int newDirection = command.substring(command.indexOf(' '), 15).toInt();
    turnTo(newDirection);
  }
  else if (command.startsWith("sensor"))
  {
    int sensornumber = command.substring(command.indexOf(' '), 10).toInt();
    //Trace(sensornumber);
    int cm = getSensorDistanceInCm(sensornumber);
    Trace(cm);
  }
  else if (command == "speed")
  {
    int speed = get("speed");
    TraceNoLine("Speed: ");
    Trace(speed);
  }
  else if (command.startsWith("speed "))
  {
    int newSpeed = command.substring(command.indexOf(' '), 10).toInt();
    //set("speed", newSpeed);
    setSpeed(newSpeed);
  }
  else if (command.startsWith("set "))
  {
    //For example 'set maxspeed 50'
    String name = command.substring(command.indexOf(' '), command.lastIndexOf(' ')).trim();
    int value = command.substring(command.lastIndexOf(' '), command.length()).toInt();
    set(name, value);
    //EEPROM.write(SETTING_MAX_SPEED, value);
    //int newValue = EEPROM.read(SETTING_MAX_SPEED);
    TraceNoLine("-->" + name + " set to: ");
    Trace(value);
    //Trace(newValue);
  }
  else if (command.startsWith("get "))
  {
    //For example 'get maxspeed'
    String name = command.substring(command.indexOf(' '), command.length()).trim();
    Trace("->" + name + "<-");
    int value = get(name);
    Trace(value);
  }
  else if (command  == "wait")
  {
    startmodule_state = WAITING;
    TraceNoLine("->In state: ");
    Trace(startmodule_state);
  }
  else if (command == "start" || command == "drive")
  {
    startmodule_state = RUNNING;
    TraceNoLine("->In state: ");
    Trace(startmodule_state);
  }
  else if (command == "stop")
  {
    startmodule_state = STOP;
    TraceNoLine("->In state: ");
    Trace(startmodule_state);
  }
  else if (command == "manual")
  {
    startmodule_state = MANUAL;
    TraceNoLine("->In state: ");
    Trace(startmodule_state);
    ledOn();
  }
  else if (command == "setting")
  {
    Trace("TODO: Print out all settings");
  }
  else if (command == "reboot")
  {
    
  }
  else{
    String error = "->Unknown command: " + command;
    Trace(error);
  }
}


