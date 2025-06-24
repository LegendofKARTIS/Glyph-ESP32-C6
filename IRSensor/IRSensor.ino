#define SENSOR_PIN 7

void setup() 
{
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() 
{
  int state = digitalRead(SENSOR_PIN);
  if (state == LOW)
    Serial.println("The obstacle is present");
  else
    Serial.println("The obstacle is NOT present");
  delay(100);
}
