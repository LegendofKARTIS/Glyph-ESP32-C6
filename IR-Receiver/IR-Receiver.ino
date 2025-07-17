#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_RECEIVE_PIN D6  // You can change this to any other GPIO

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the IR receiver
  Serial.println("IR Receiver Ready...");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("====================================");
    
    // Print decoded value in HEX
    Serial.print("Decoded Value (HEX): 0x");
    Serial.println(results.value, HEX);

    // You can also print raw timing info if needed
    Serial.println("Raw Timing Info:");
    Serial.println(resultToTimingInfo(&results));

    irrecv.resume();  // Prepare to receive the next signal
  }
}
