#define BUTTON_PIN 6
#define LED_PIN 18

int lastButtonState = HIGH;  // previous state of button (initially unpressed)
int currentButtonState;
bool ledState = false;       // stores current LED ON/OFF state

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button between GPIO9 and GND
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  currentButtonState = digitalRead(BUTTON_PIN);

  // Detect rising edge: button released after being pressed
  if (lastButtonState == LOW && currentButtonState == HIGH) {
    ledState = !ledState;  // toggle the LED state
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    if (ledState) {
      Serial.println("Button Released: LED ON");
    } else {
      Serial.println("Button Released: LED OFF");
    }
  }

  lastButtonState = currentButtonState;
}
