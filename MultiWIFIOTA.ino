/*
  useraid
  Base Boilerplate for ESP8266 with WiFiManager and OTA
  For Serial Debugging uncomment //#// Lines
*/

#include <Arduino.h> // Arduino Core required for PlatformIO
#include <ESP8266WiFi.h>
#include <WiFiMulti.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

WiFiMulti wm;

// Set WiFi timeout
const uint32_t connectTimeoutMs = 5000

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  
  // Putting WiFi into STA mode to connect to an AP
  WiFi.mode(WIFI_STA);

  // Add WiFi networks
  wm.addAP("EACCESS", "hostelnet");
  wm.addAP("TU", "tu@inet1");
  wm.addAP("LC", "lc@tiet1");

  // Wait for WiFi connection
  //#// Serial.println("Connecting Wifi...");
  if(wm.run() == WL_CONNECTED) {
    //#// Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // Initialize Webserver at root
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "This is the ESPWatchOLED Project.\nMore Information about this project can be found on my GitHub Page: https://github.com/useraid/ESPWatchOLED");
  });

  // Start ElegantOTA
  AsyncElegantOTA.begin(&server);
  //#// server.begin();
  //#// Serial.println("HTTP server started");
}

void loop(void) {
    // Codebase
}