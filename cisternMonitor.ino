#include "user_specified.h"

// this is called when the 'thing' boots
void setup() 
{
  Serial.begin(9600);   // debug data sent over serial port
  
  initEEPROM();

  initGPIO(); // Setup input/output I/O pins  

  if(timeToTakeReading())
  {
    Serial.println("time to take a reading");
  
    connectWiFi();

    incrementSleepCounter();
  }
  else
  {
    blinkLED(1,100);
     
    // not time to take a reading yet, go back to sleep
    incrementSleepCounter();

    goToSleep();
  }
}

// this is called continuously while the 'thing' is running
void loop() 
{
  if(WiFiConnected())  
  {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    showWiFiIP();

    int waterLevel = getCisternLevel();

    Serial.println("read water level: " + String(waterLevel));
    if(waterLevel < 0)
    {
      blinkLED(1,2000);
      blinkLED(-waterLevel,500);
    }
    else
    {
      blinkLED(waterLevel,500);
    }

    if(postToThingspeak(waterLevel) < 0)
    {
      // error posting data...try again next time we wake up
      setSleepCounterToMax();
    }

    goToSleep();
  }
  else
  {
    Serial.println("[loop] no wifi");
    blinkLED(1,100);
    delay(500);
  }  
}
