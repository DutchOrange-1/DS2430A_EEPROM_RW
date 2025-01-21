# EEPROM Read / Write
EEPROM Read Write Scripts for Arduino.
This is made for the DS2430A 256-bit 1-Wire EEPROM, commonly found in old ink chips from Mimaki. 
These scripts can be used to read and write the 32 Hex values to the EEPROM. 

# Workings
This makes use of the OneWire.h library from Arduino for communication. 
This data was found when using the Mimaki JV5-320**D**S

# Known data that can be changed. 
Mimaki keeps a lot of information to themselves. 
From my limited reverse engineering, I was able to find the following:
7
| Bit Position | Type of data | Notes| 
| -----------|--------------|-------|
| 1 | Ink type | Limited Inks know, check the bottom of page |
| 2 | Unknown | Number is same across all inks of the same machine | 
| 3
| 4 | Unknown | Number is same across all inks of the same machine | 
| 5
| 6
| 7
| 8
| 9
| 10
| 11
| 12
| 13 | Expiary date | Make sure to change this before it expires. Change the number only slightly 18-> 19, or 20->21. I suspect these numbers represent the time after manufacture | 
| 14
| 15 | Unknown | Number is same across all inks of the same machine | 
| 16 | Unknown | Number is same across all inks of the same machine | 
| 17 | Unknown | Number is same across all inks of the same machine | 
| 18
| 19
| 20
| 21
| 22 | Unknown | Number is same across all inks of the same machine (All Zeros) | 
| 23
| 24
| 25 | Unknown | Number is same across all inks of same machine (All 20) | 
| 26 | Unknown | Number is same across all inks of same machine (All 20) | 
| 27 | Unknown | Number is same across all inks of same machine (All Zeros) | 
| 28 | Unknown | Number is same across all inks of same machine (All Zeros) | 
| 29
| 30
| 31 | Ink Level | I recommend just increasing this value by small amounts | 
| 32



# Know Inks:

| Type | Hex Value |
|-----|------------|
|SB53| 43 |
|LH100 | 28 |
|ES3 | 15 | 
| SS21 | 20 |
| LF140 | 3C | 

Please, if you know any other ink Hex values, please open an issue tab. 
