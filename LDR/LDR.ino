// Define the pin where the LDR is connected
const int ldrPin = 3;  // Analog pin A3

void setup() {
  // Start serial communication for monitoring
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from LDR
  int ldrValue = analogRead(ldrPin);

  // Print the LDR value to the Serial Monitor
  if (ldrValue < 300){
    Serial.println("Light is Present");
  }
  else{
    Serial.println("Room is Dark");
  }

  // Small delay for stability
  delay(500);
}
