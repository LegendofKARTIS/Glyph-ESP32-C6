const int RELAY_1 = 3;  // GPIO2 for first relay
const int RELAY_2 = 2;  // GPIO3 for second relay

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Configure relay pins as outputs
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  
  // Initialize Both Relay Channels to OFF state (relays are typically Active LOW- Means they are OFF when a HIGH Signal is Applied and vice-versa)
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  
  Serial.println("Relay Module Initialized"); //Print that Relay Module is Initialized
}
void loop(){
  // Turn ON Relay 1
  digitalWrite(RELAY_1, LOW);
  Serial.println("Turning on Relay 1");
  delay(2000);
  
  // Turn OFF Relay 1
  digitalWrite(RELAY_1, HIGH);
  Serial.println("Turning off Relay 1");
  delay(1000);
  
}

