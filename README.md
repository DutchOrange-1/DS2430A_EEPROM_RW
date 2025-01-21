# EEPROM Read / Write
EEPROM Read Write Scripts for Arduino.
This is made for the DS2430A 256-bit 1-Wire EEPROM, commonly found in old ink chips from Mimaki. 
These scripts can be used to read and write the 32 Hex values to the EEPROM. 

# Workings
This makes use of the OneWire.h library from Arduino for communication. 

# Known data that can be changed. 
Mimaki keeps a lot of information to themselves. 
From my limited reverse engineering I was able to find the following:

| Bit Position | Type of data | Notes| 
| -----------|--------------|-------|
| 0 | Ink type 


# Know Inks:

| Type | Hex Value |
|-----|------------|
|SB53| 43 |
|LH100 | 28 |
|ES3 | 15 | 
| SS21 | 20 |
| LF140 | 3C | 

Please, if you know any other ink Hex values, please open an issue tab. 
