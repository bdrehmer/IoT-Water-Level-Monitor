// The ESP is a 32-bit processor and the maximum value for a 32-bit unsigned integer is 4294967295 or 0xffffffff, or 71 minutes.

//const uint SLEEP_DURATION_us = 3600000000;  // 1 hour - for deployment

const uint SLEEP_DURATION_us = 2000000;  // 2 sec - for debugging

void goToSleep()
{
  Serial.println("going to sleep");
  ESP.deepSleep(SLEEP_DURATION_us);
}
