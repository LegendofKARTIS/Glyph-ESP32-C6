#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);
  Wire.begin(6, 7);   // SDA = GPIO6, SCL = GPIO7
  rtc.begin();
  Serial.println("Enter time in hh:mm:ss format:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 8 && input[2] == ':' && input[5] == ':') {
      int h = input.substring(0, 2).toInt();
      int m = input.substring(3, 5).toInt();
      int s = input.substring(6, 8).toInt();

      if (isValidTime(h, m, s)) {
        DateTime now = rtc.now();
        rtc.adjust(DateTime(now.year(), now.month(), now.day(), h, m, s));
        Serial.println("✅ Time set.");
      } else {
        Serial.println("❌ Invalid time.");
      }
    } else {
      Serial.println("⚠️ Format error.");
    }
  }

  static unsigned long last = 0;
  if (millis() - last > 1000) {
    last = millis();
    DateTime now = rtc.now();
    Serial.printf("RTC Time: %02d:%02d:%02d\n", now.hour(), now.minute(), now.second());
  }
}

bool isValidTime(int h, int m, int s) {
  return (h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60);
}
