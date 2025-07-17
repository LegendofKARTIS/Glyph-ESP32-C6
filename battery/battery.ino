#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Hello";
const char* password = "caspercasper1234";

// ADC configuration
#define BATTERY_PIN A0
const float VOLTAGE_DIVIDER_RATIO = 2;      // 200k:200k divider
const float ADC_REF_VOLTAGE = 3.3;            // ESP32 ADC reference
const float CALIBRATION_FACTOR = 1.14;      // Calibrated so 3.6V → 1.8V at A0
const float MIN_VOLTAGE = 3.2;                // Battery empty
const float MAX_VOLTAGE = 4.2;                // Battery full

WebServer server(80);


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

// HTML page handler
void handleRoot() {
  int rawADC;
  float v_adc;
  float batteryVoltage = readBatteryVoltage(rawADC, v_adc);
  int batteryPercent = calculateBatteryPercentage(batteryVoltage);

  String html = R"=====( 
<!DOCTYPE html>
<html>
<head>
  <title>KARTIS YT</title>
  <style>
    body { font-family: Arial; text-align: center; margin: 30px; background: #f4f4f4; }
    .box { max-width: 600px; margin: auto; padding: 20px; background: white; border: 1px solid #ccc; border-radius: 10px; }
    .voltage { font-size: 2.5em; color: #2c3e50; margin-bottom: 10px; }
    .percent { font-size: 2.2em; color: #4CAF50; font-weight: bold; margin-bottom: 10px; }
    .bar-container { background-color: #eee; border-radius: 10px; width: 100%; height: 30px; margin-top: 15px; }
    .bar-fill { height: 30px; background-color: #4CAF50; border-radius: 10px; width: %PERCENTAGE%%; transition: width 0.5s; }
    .debug { text-align: left; margin-top: 20px; background: #f9f9f9; padding: 15px; border-radius: 5px; }
    .label { font-weight: bold; color: #333; }
  </style>
  <meta http-equiv="refresh" content="5">
</head>
<body>
  <div class="box">
    <h1>Kartis' ESP32 Battery Monitor System</h1>
    <br>
    <div class="voltage">Battery Voltage: %VOLTAGE% V</div>
    <div class="percent">%PERCENTAGE%% Charged</div>
    <div class="bar-container">
      <div class="bar-fill"></div>
    </div>
    <div class="debug">
      <div><span class="label">Raw ADC Value:</span> %RAW%</div>
      <div><span class="label">Voltage at A0 (measured):</span> %V_ADC% V</div>
      <div><span class="label">Expected A0 Voltage @ 3.6V Battery:</span> 1.800 V</div>
      <div><span class="label">Divider Ratio:</span> %DIVIDER%</div>
      <div><span class="label">ADC Reference Voltage:</span> %ADC_REF% V</div>
      <div><span class="label">Calibration Factor:</span> %CALIB%</div>
      <div><span class="label">IP Address:</span> %IP%</div>
      <div><span class="label">Uptime:</span> %UPTIME% seconds</div>
    </div>
  </div>
  <h4>Subscribe Kartis <a href=" https://www.youtube.com/@kartis_ ">click here</a></h4>
</body>
</html>
)=====";

  html.replace("%VOLTAGE%", String(batteryVoltage, 3));
  html.replace("%PERCENTAGE%", String(batteryPercent));
  html.replace("%RAW%", String(rawADC));
  html.replace("%V_ADC%", String(v_adc, 3));
  html.replace("%DIVIDER%", String(VOLTAGE_DIVIDER_RATIO, 1));
  html.replace("%ADC_REF%", String(ADC_REF_VOLTAGE, 2));
  html.replace("%CALIB%", String(CALIBRATION_FACTOR, 3));
  html.replace("%IP%", WiFi.localIP().toString());
  html.replace("%UPTIME%", String(millis() / 1000));

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);           // 12-bit ADC
  analogSetAttenuation(ADC_11db);     // Full-scale input ~3.3V
  pinMode(BATTERY_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
