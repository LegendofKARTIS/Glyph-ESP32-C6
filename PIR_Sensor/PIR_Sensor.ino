#define PIR_PIN 6      // GPIO pin connected to PIR output
#define LED_PIN 14     // Onboard LED (optional)

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);  // Optional: LED indicates motion

  Serial.begin(115200);
  Serial.println("PIR Motion Sensor Initialized");
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    Serial.println("Motion Detected!");
    digitalWrite(LED_PIN, HIGH);  // Turn ON onboard LED
  } else {
    Serial.println("No motion");
    digitalWrite(LED_PIN, LOW);   // Turn OFF LED
  }

  delay(1000);  // Adjust polling rate as needed
}
