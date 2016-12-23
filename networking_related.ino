#include "user_specified.h"

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

void connectWiFi()
{
  Serial.println();
  Serial.println("Connecting to: " + String(WiFiSSID));
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);

  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WiFiSSID, WiFiPSK);
}

bool WiFiConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

void showWiFiIP()
{
  Serial.println(WiFi.localIP());
}

// https://techtutorialsx.wordpress.com/2016/07/21/esp8266-post-requests/
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/BasicHttpClient/BasicHttpClient.ino#L10
int postToThingspeak(int level)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wifi not connected");
    return -1;
  }
   
  String thingspeakURL = "http://api.thingspeak.com/update?api_key=";
  thingspeakURL += String(THINGSPEAK_KEY) + "&field1=" + String(level);

  //Serial.println("GET " + thingspeakURL);
  Serial.println("sending data to thingspeak");
  
  HTTPClient http;
  http.begin(thingspeakURL);
  int httpCode = http.GET();
  String payload = http.getString();  // response
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  if(httpCode == 200)
  {
    Serial.println("posted data to thingspeak");
    return 0;
  }
  else
  {
    Serial.println("unknown HTTP return code when posting data to thingspeak");
    return -2;
  }
}
