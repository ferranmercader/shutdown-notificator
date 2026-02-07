/*
  ESP32 Healthchecks.io Heartbeat Snippet (ULTRA LOW POWER)
  Optimized for minimum battery consumption using Deep Sleep, Static IP and Disabled Serial.
*/

#include <WiFi.h>
#include <HTTPClient.h>

// --- DEBUG MODE (Set to 0 for maximum power saving, 1 to see logs) ---
#define DEBUG 0

#if DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTF(...)
  #define DEBUG_PRINTLN(x)
#endif

// --- CONFIGURATION ---
const char* ssid = "TU_SSID_AQUI";
const char* password = "TU_PASSWORD_AQUI";
const char* hc_url = "https://hc-ping.com/TU_UUID_AQUI";

// Interval between pings in SECONDS
const uint64_t INTERVAL_SECONDS = 60; 

// --- STATIC IP (Speeds up connection by ~2-4 seconds) ---
IPAddress local_IP(192, 168, 1, 150); 
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); 

void sendHeartbeat() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    DEBUG_PRINT("Sending heartbeat...");
    http.begin(hc_url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      DEBUG_PRINTF("OK (%d)\n", httpCode);
    } else {
      DEBUG_PRINTF("Error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void setup() {
#if DEBUG
  Serial.begin(115200);
  delay(10); 
#endif

  // Fast WiFi connection with Static IP
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    DEBUG_PRINTLN("Static IP Failed to configure");
  }

  WiFi.begin(ssid, password);
  DEBUG_PRINT("Connecting to WiFi");
  
  // Wait max 10 seconds for connection
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(50);
    DEBUG_PRINT(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    DEBUG_PRINTLN("\nConnected!");
    sendHeartbeat();
  } else {
    DEBUG_PRINTLN("\nFailed to connect.");
  }

  // Cleanup and Go to Sleep
  DEBUG_PRINTLN("Going to Deep Sleep...");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  
  esp_sleep_enable_timer_wakeup(INTERVAL_SECONDS * 1000000ULL);
  esp_deep_sleep_start();
}

void loop() {
}
