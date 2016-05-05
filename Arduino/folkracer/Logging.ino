/*
 * Write to serial, both USB and Bluetooth (or whatever is on Serial1)
 */

void Trace(const String& message)
{
  Serial.println(message);
  Serial1.println(message);
}

void TraceNoLine(const String& message)
{
  Serial.print(message);
  Serial1.print(message);
}


