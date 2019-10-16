const int ledPin =  LED_BUILTIN;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
byte incomingData = 0;

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
      incomingData = Serial.read();
    if (incomingData == 10)
    {
      Serial.println("Value Read: ");
      Serial.println(incomingData);
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
    }
    else
    {
        Serial.println("Not the value that was expected.");  
    }
  }
}
