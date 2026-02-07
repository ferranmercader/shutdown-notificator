/*
  ESP32 Healthchecks.io Heartbeat Snippet (MVP)
  Standard version without power optimizations. Compatible with Arduino IDE.
*/

#include <WiFi.h>
#include <HTTPClient.h>

// --- CONFIGURATION ---
const char* ssid = "TU_SSID_AQUI";
const char* password = "TU_PASSWORD_AQUI";
const char* hc_url = "https://hc-ping.com/TU_UUID_AQUI";

// Ping interval (e.g., every 1 minute)
const unsigned long interval = 1 * 60 * 1000;
unsigned long lastPing = 0;

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  
  // Initial ping
  sendHeartbeat();
}

void loop() {
  if (millis() - lastPing >= interval) {
    sendHeartbeat();
  }
}

void sendHeartbeat() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.print("Sending heartbeat...");
    http.begin(hc_url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.printf("OK (%d)\n", httpCode);
      lastPing = millis();
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
