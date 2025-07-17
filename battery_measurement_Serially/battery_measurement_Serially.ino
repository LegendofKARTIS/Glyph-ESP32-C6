
// ADC configuration
#define BATTERY_PIN A0
const float VOLTAGE_DIVIDER_RATIO = 2.0;       // 200k:200k divider
const float ADC_REF_VOLTAGE = 3.3;             // ESP32 ADC reference
const float CALIBRATION_FACTOR = 1.14;         // Calibrated so 3.6V → 1.8V at A0
const float MIN_VOLTAGE = 3.2;                 // Battery empty
const float MAX_VOLTAGE = 4.2;                 // Battery full

// Read battery voltage and A0
float readBatteryVoltage(int& rawADC, float& v_adc) {
  rawADC = analogRead(BATTERY_PIN);
  v_adc = (rawADC / 4095.0) * ADC_REF_VOLTAGE * CALIBRATION_FACTOR;
  float batteryVoltage = v_adc * VOLTAGE_DIVIDER_RATIO;
  return batteryVoltage;
}

// Map float
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Battery percentage
int calculateBatteryPercentage(float voltage) {
  voltage = constrain(voltage, MIN_VOLTAGE, MAX_VOLTAGE);
  float percent = mapFloat(voltage, MIN_VOLTAGE, MAX_VOLTAGE, 0, 100);
  return (int)percent;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);           // 12-bit ADC
  analogSetAttenuation(ADC_11db);     // Full-scale input ~3.3V
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  int rawADC;
  float v_adc;
  float batteryVoltage = readBatteryVoltage(rawADC, v_adc);
  int batteryPercent = calculateBatteryPercentage(batteryVoltage);

  Serial.println("=== Battery Monitor ===");
  Serial.printf("Raw ADC Value: %d\n", rawADC);
  Serial.printf("Voltage at A0: %.3f V\n", v_adc);
  Serial.printf("Battery Voltage: %.3f V\n", batteryVoltage);
  Serial.printf("Battery Percentage: %d%%\n", batteryPercent);
  Serial.println();

  delay(2000); // Update every 2 seconds
}
