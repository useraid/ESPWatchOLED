/*
  useraid
  Base Boilerplate for ESP8266 with WiFiManager and OTA
  Debugging is ON by Default
*/

#include <Arduino.h> // Arduino Core required for PlatformIO
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>

WiFiManager wm;

void setup() {
  // Serial initialization for debugging
  Serial.begin(115200);

  // WiFiManager Captive Portal Init
  bool connection;
  connection = wm.autoConnect("ESPWatchOLED","meowlol"); // Config AP
  
  // Restart on Connection Failure
  if(!connection) { 
        Serial.println("Failed to connect"); 
        ESP.restart();
 
  }
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Wifi connecting...");
  }
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
  
  // Serial Debug Parameters for OTA
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();

  // Init Setup Here

}

void loop() {
  ArduinoOTA.handle();

  // Codebase Here

}
