//This code has been adapted to write the 32 bits
#include <OneWire.h>

#define ONE_WIRE_BUS 10  // Define the digital pin connected to DS2430A

OneWire ds(ONE_WIRE_BUS);

//0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20 // Helllo
// 0x4E, 0x69, 0x63, 0x6F, 0x0, 0x0 // Nico
// 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x6C, 0x69, 0x6E, 0x65 // Screenline


constexpr char total_memory[8][4] {
  {0x48, 0x65, 0x6C, 0x6C},
  {0x6F, 0x20, 0x4E, 0x69},
  {0x63, 0x6F, 0x2E, 0x0},
  {0x53, 0x63, 0x72, 0x65},
  {0x65, 0x6E, 0x6C, 0x69},
  {0x6E, 0x65, 0x20, 0x20},
  {0x0, 0x1, 0x0, 0x1},
  {0x0, 0x1, 0x0, 0x1}
};

char address_arr[8] {
  0x0, 0x4, 0x8, 0xC, 0x10, 0x14, 0x18, 0x1C
};


char memory[4] = {0x1, 0x2, 0x3, 0x4};
//byte positon = 19;
char start_addr = 0x0;
// 0 5 A F 14 19 27(1B) <- Last 5 digits

void setup() {
  Serial.begin(9600);

  for (byte i = 0; i < 8; i++) {
    
    //Getting values
    start_addr = address_arr[i];
    memcpy(memory, total_memory[i], sizeof(memory));
    
    //Printing Values
    Serial.print("Running memory adress: ");
    Serial.println(start_addr, HEX);
    Serial.println("Data to be sent: ");
    for(byte j = 0; j < 4; j++){
      Serial.print(memory[j], HEX);
      Serial.print("-"); 
    }
    Serial.println(); 
    
//    return 0;
//    Uploading
    modifySingleByte(start_addr);
    delay(500);
    
  }
  readEEPROM();
}

void loop() {
  //  Serial.println("Waiting 60s");
  //  delay(60000);
}

void modifySingleByte(char start_addr) {
  Serial.println(sizeof(memory));
  byte addr[8];  // To store the device address
  byte scratchpad[8];  // To read scratchpad (8 bytes + 1 CRC byte)
  //    byte newByte = 0x11;  // The new byte you want to change

  // Reset and search for devices
  ds.reset_search();
  if (!ds.search(addr)) {
    Serial.println("No DS2430A device found");
    return;
  } else {
    Serial.println("Device Found");
  }


  // Start communication with the device
  ds.reset();
  ds.select(addr);

  // Send WRITE SCRATCHPAD command (0x0F)
  ds.write(0x0F);
  ds.write(start_addr);


  for (byte i = 0; i < sizeof(memory); i++) {
    ds.write(memory[i]);
  }

  // Now read back the scratchpad to verify the written data
  ds.reset();
  ds.select(addr);
  ds.write(0xAA);  // READ SCRATCHPAD command

  // Read the data from scratchpad
  for (int i = 0; i < sizeof(memory) + 2; i++) { // 8 data bytes + 1 CRC byte
    scratchpad[i] = ds.read();
  }

  // Output the modified scratchpad data
  Serial.print("Modified Scratchpad Data: ");
  for (int i = 0; i < sizeof(memory) + 2; i++) {
    Serial.print(scratchpad[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Now, copy the scratchpad to the EEPROM
  ds.reset();
  ds.select(addr);
  ds.write(0x55);  // COPY SCRATCHPAD command

  // Wait for the copy process to complete (1 second)
  delay(1000);
  ds.write(0xA5); //This is needed for the Bus Validation
  delay(100);

  Serial.println("Scratchpad has been copied to EEPROM.");
}

void readEEPROM() {
  byte addr[8];  // To store the device address
  byte scratchpad[8];  // To read scratchpad


  // Reset and search for devices
  ds.reset_search();
  if (!ds.search(addr)) {
    Serial.println("No DS2430A device found");
    return;
  } else {
    Serial.println("Device Found");
  }

  byte data[32];

  ds.reset();
  ds.select(addr);
  ds.write(0xF0);  // READ MEMORY command
  ds.write(0x00);  // Start at address 0x00

  Serial.print("Read Data: ");
  for (byte i = 0; i < 32; i++) {
    data[i] = ds.read();
    Serial.print((char)data[i], HEX);  // Print ASCII values
    Serial.print(" ");
  }
  Serial.println();
}
