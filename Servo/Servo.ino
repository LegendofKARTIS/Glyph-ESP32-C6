#include <ESP32Servo.h>

Servo myServo;

#define SERVO_PIN 14  // Connect SG90 Signal pin to GPIO 5

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);       // SG90 expects 50 Hz
  myServo.attach(SERVO_PIN, 500, 2400); // Min and max pulse widths in microseconds
  Serial.println("Servo ready!");
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 10) {
    myServo.write(pos);
    Serial.print("Moving to: ");
    Serial.println(pos);
    delay(500);
  }

  for (int pos = 180; pos >= 0; pos -= 10) {
    myServo.write(pos);
    Serial.print("Moving to: ");
    Serial.println(pos);
    delay(500);
  }
}
