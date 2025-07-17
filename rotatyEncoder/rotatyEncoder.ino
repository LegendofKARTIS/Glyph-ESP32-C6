#define ENCODER_CLK 4
#define ENCODER_DT 5
#define ENCODER_SW 6  // Button Pin

volatile int position = 0;
volatile int direction = 0;
bool buttonPressed = false;

void IRAM_ATTR readEncoder() {
if (digitalRead(ENCODER_CLK) == digitalRead(ENCODER_DT)) 
{
  position--;  // Counter-clockwise
  direction = -1;
} else 
{
  position++;  // Clockwise
  direction = 1;
}
}

void IRAM_ATTR buttonISR() {
buttonPressed = true;  // Set flag when button is pressed
}

void setup() {
Serial.begin(115200);
pinMode(ENCODER_CLK, INPUT_PULLUP);
pinMode(ENCODER_DT, INPUT_PULLUP);
pinMode(ENCODER_SW, INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, CHANGE);
attachInterrupt(digitalPinToInterrupt(ENCODER_SW), buttonISR, FALLING);
}

void loop() {
static int lastPosition = 0;

// Print position update
if (lastPosition != position) {
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Direction: ");
  Serial.println(direction == 1 ? "Increasing" : "Decreasing");
  lastPosition = position;
}

// Print button press message
if (buttonPressed) {
  Serial.println("Button Pressed!");
  buttonPressed = false;  // Reset flag
}
}