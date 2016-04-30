void Run(String command)
{
  if (command == "help") {
    Trace("Usage:");
    Trace("led.on");
    Trace("led.off");
    Trace("settings");
  }
  else if (command == "led.on") {
      digitalWrite(LED_PIN, HIGH);
      Trace("->LED turned ON");
  }
  else if (command == "led.off")
  {
    digitalWrite(LED_PIN, LOW);
    Trace("->LED turned OFF");
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
    int speed = getSetting("speed");
    Trace("Speed");
    Trace(speed);
  }
  else if (command.startsWith("speed "))
  {
    int newSpeed = command.substring(command.indexOf(' '), 10).toInt();
    set("speed", newSpeed);
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

