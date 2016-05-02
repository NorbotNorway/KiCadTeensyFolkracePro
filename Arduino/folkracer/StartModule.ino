void changeStartmoduleState()
{
  bool sm_value = digitalRead(STARTMODULE_PIN);
  if (startmodule_state == WAITING && sm_value == true)
    startmodule_state = RUNNING;
  else if (startmodule_state == RUNNING && sm_value == false)
    startmodule_state = STOP;
}

