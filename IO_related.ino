// output LED
#define THING_LED 5

// inputs
#define SENSOR_1 14
#define SENSOR_2 4
#define SENSOR_3 13
#define SENSOR_4 12

void initGPIO()
{
    // outputs
  pinMode(THING_LED, OUTPUT);
  digitalWrite(THING_LED, HIGH); // LED off
  // inputs
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
  pinMode(SENSOR_3, INPUT_PULLUP);
  pinMode(SENSOR_4, INPUT_PULLUP);
}

// note: inputs are configured as PULL_UP and are active low
int getCisternLevel()
{
  int s1 = digitalRead(SENSOR_1);
  int s2 = digitalRead(SENSOR_2);
  int s3 = digitalRead(SENSOR_3);
  int s4 = digitalRead(SENSOR_4);

  if(s1 == HIGH && s2 == HIGH && s3 == HIGH && s4 == HIGH)
    return 0;
  else if(s1 == LOW && s2 == HIGH && s3 == HIGH && s4 == HIGH)
    return 1;
  else if(s1 == LOW && s2 == LOW && s3 == HIGH && s4 == HIGH)
    return 2;
  else if(s1 == LOW && s2 == LOW && s3 == LOW && s4 == HIGH)
    return 3;
  else if(s1 == LOW && s2 == LOW && s3 == LOW && s4 == LOW)
    return 4;
  else if(s1 == LOW && s2 == LOW && s3 == LOW && s4 == LOW)
    return 5;
  else
  {
    // abnormal reading...not all sensors are active that should be.
    // return negative number indicating the error and the sensor readings
    int level = 0;
    
    if(s1 == LOW)
      level += 1;
    
    if(s2 == LOW)
      level += 2;
    
    if(s3 == LOW)
      level += 4;
    
    if(s4 == LOW)
      level +=8;

    level *= -1;
      
    return level;
  }  
}

void blinkLED(int numberOfTimes, float interval_ms)
{
  for(int i=0; i < numberOfTimes; i++)
  {
    digitalWrite(THING_LED, LOW); // LED on
    delay(interval_ms);
    digitalWrite(THING_LED, HIGH); // LED off
    delay(interval_ms);
  }
}
