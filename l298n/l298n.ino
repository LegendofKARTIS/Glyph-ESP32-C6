#define in1 9
#define in2 14
#define in3 15
#define in4 18

void setup() {
  Serial.begin(115200);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  StopAll();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    Serial.print("Received: ");
    Serial.println(cmd);
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': // Forward only
      moveForward();
      break;
    case 'B': // Backward only
      moveBackward();
      break;
    case 'L': // Left only
      turnLeft();
      break;
    case 'R': // Right only
      turnRight();
      break;
    case 'S':
      StopAll();
      break;
    default:
      break;
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
}

void turnLeft() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void StopAll() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
