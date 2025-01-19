#include <OneWire.h>

#define ONE_WIRE_BUS 8  // Define the digital pin connected to DS2430A

OneWire ds(ONE_WIRE_BUS);

void setup() {
    Serial.begin(9600);
    Serial.println("DS2430A Read Scratchpad Example");
}

void loop() {
    byte addr[8];
    byte data[32];

    if (!ds.search(addr)) { 
        Serial.println("No more devices found.");
        ds.reset_search();
        delay(1000);
        return;
    }

    // Check if the device is a DS2430A (family code 0x14)
    if (addr[0] != 0x14) {
        Serial.println("Not a DS2430A device!");
        return;
    }

    Serial.print("Device Found: ");
    for (byte i = 0; i < 8; i++) {
        Serial.print(addr[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    ds.reset();
    ds.select(addr);         // Select the DS2430A
//    ds.write(0xAA);          // Send READ SCRATCHPAD command (0xAA)
    ds.write(0xF0);         // Send READ MEMORY command (0xF0)
    ds.write(0x00);         // Start reading at address 0x00

    Serial.print("EEPROM Data: ");
    for (byte i = 0; i < 32; i++) {  // Read all 32 bytes
        data[i] = ds.read();
        Serial.print("0x");
        Serial.print(data[i], HEX);
        Serial.print(" , ");
    }
    Serial.println("\n");
    //10s wait
    delay(10000);
}
