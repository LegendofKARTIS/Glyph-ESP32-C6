#define BUTTON_PIN 6
#define ledPin 18 

int lastState = HIGH;  // the previous reading from the  button input pin GPIO 6
int currentState;     // the current reading from the button input pin GPIO 6
void setup() 
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}
void loop() 
{
  currentState = digitalRead(BUTTON_PIN);
  if (lastState == HIGH && currentState == LOW)
  {
    digitalWrite(ledPin, HIGH);   // Turn LED on 
    Serial.println("Boot button is pressed and LED is ON");
  }

  else if (lastState == LOW && currentState == HIGH)
  {
    digitalWrite(ledPin, LOW);   // Turn LED on 
    Serial.println("Boot button is not pressed and LED is OFF");
  }
  lastState = currentState;
}