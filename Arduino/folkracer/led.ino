void ledBlink(int speed)
{
  digitalWrite(LED_PIN, HIGH);
  delay(speed);
  digitalWrite(LED_PIN, LOW);
  delay(speed);
}

void ledOn()
{
  digitalWrite(LED_PIN, HIGH);
}

void ledOff()
{
  digitalWrite(LED_PIN, LOW);
}

