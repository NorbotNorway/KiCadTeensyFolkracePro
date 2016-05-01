void Trace(const String& message)
{
  //Serial.println("In LOG method");
  //Serial1.println("In LOG method");
  Serial.println(message);
  Serial1.println(message);
}

void TraceNoLine(const String& message)
{
  Serial.print(message);
  Serial1.print(message);
}

