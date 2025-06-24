// Pin number of the LED
const int led = 1; // which is Digital pin D0 in GLYPH-C3

// Pin number of the Potentiometer
const int pot = 2; //, which is Analog pin A1 in GLYPH-C3

// Setting PWM Properties like Frequency and Resolution
const int freq = 5000; // LEDC PWM channel’s Frequency Range is 10 Hz - 40 MHz.So, set a Frequency value in this range

const int resolution = 8; // The Default Resolution for LEDC PWM is 8 bits

void setup()
{
// Initialize the Serial Monitor Baud Rate as 115200 (you can also set it to 9600)
Serial.begin(115200); 

pinMode(led, OUTPUT); // Set LED to be an output pin
pinMode(pot, INPUT); // Set Potentiometer to be an input pin

// Setting up the LEDC pin with the PWM Properties and Attaching this pin to ADC Channel 0, where the Potentiometer is connected
ledcAttachChannel(led,freq,resolution,0); 
}

void loop()
{
// Read the Analog input voltage between 0 V and 3.3 V from the Potentiometer and map it into corresponding integer values between 0 and 4095 using C3's 12-bit ADC8
int potvalue = analogRead(pot); 

// Changing the Potentiometer's ADC range from 0 -4095  to the LED PWM duty cycle range 0 - 255 (As we are using 8-bit resolution for PWM) using the equation (255.0/4095.0)*potvalue
int brightness = (255.0/4095.0)*potvalue;

ledcWrite(led, brightness); // Changing the LED brightness by setting the above PWM Duty cycle
Serial.println("Pot. value: ");
Serial.println(potvalue);
// Print the LED brightness value onto Serial Monitor 
Serial.print("Led Brightness is:");
Serial.println(brightness);
delay(200);
}
