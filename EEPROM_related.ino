#include "user_specified.h"

#include <EEPROM.h>

// since I only want to post data to the cloud every 12 hours but the deep sleep
// function can't be called for that long, we need to use the EEPROM to keep track
// of how many sleeps we have done so far.

#define EEPROM_ADDRESS 0    // this EEPROM address is used to keep track of how many sleeps we have done

void initEEPROM()
{
  // https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM/examples
  EEPROM.begin(512);  
  // initialize / clear the value (EEPROM is data is initially 0xFF)
  if(EEPROM.read(EEPROM_ADDRESS) >= UPDATE_INTERVAL_HRs)
  {
    EEPROM.write(EEPROM_ADDRESS, 0);
    EEPROM.commit();
  }
}

bool timeToTakeReading()
{
  return EEPROM.read(EEPROM_ADDRESS) == 0;  // the initEEPROM function sets value to 0 when we reach UPDATE_INTERVAL_HRs
}

void incrementSleepCounter()
{
  EEPROM.write(EEPROM_ADDRESS, EEPROM.read(EEPROM_ADDRESS)+1);
  EEPROM.commit();
}

void setSleepCounterToMax()
{
  EEPROM.write(EEPROM_ADDRESS, 255);
  EEPROM.commit();
}

