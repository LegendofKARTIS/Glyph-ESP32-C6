#include <SPI.h>
#include <SD.h>

#define SD_CS 17 // Change this to match your Glyph board's SD card CS pin
//GMOD-- GLYPH
//3v3-- 3v3
//sck-- sck
//MO -- MO
//MI-- MI
//GND-- GND

void listFiles(File dir, int numTabs = 0) {
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            break; // No more files
        }
        for (int i = 0; i < numTabs; i++) {
            Serial.print("\t");
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            listFiles(entry, numTabs + 1); // Recursively list directories
        } else {
            Serial.print("\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("Initializing SD card...");
    
    if (!SD.begin(SD_CS)) {
        Serial.println("SD card not detected!");
        return;
    }
    
    Serial.println("SD card detected successfully!");
    
    // Print card information
    uint32_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.print("Card Size: ");
    Serial.print(cardSize);
    Serial.println(" MB");
    
    // List files on SD card
    File root = SD.open("/");
    listFiles(root);
    root.close();
}

void loop() {
    // Nothing to do in the loop
}
