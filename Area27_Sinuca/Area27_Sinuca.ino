/*
 * Área27 Sinuca - ESP8266 Firmware & Embedded Web Interface
 * 
 * Hardware: ESP8266 (ESP-01 / NodeMCU / Wemos D1 Mini)
 * Features: Automatic Wi-Fi Captive Portal (AP Mode: Area27-Sinuca-Config)
 * Embedded Files: PROGMEM (Flash Storage) + LittleFS (Data Persistence)
 * REST API v1, TV Dashboard, Seasons, History, Hall of Fame & Tournament Bracket
 * Baud Rate: 115200
 */

#include <Arduino.h>
#include <LittleFS.h>
#include "src/config/Types.h"
#include "src/auth/AuthManager.h"
#include "src/persistence/StorageManager.h"
#include "src/players/PlayerManager.h"
#include "src/match/MatchManager.h"
#include "src/system/SystemManager.h"
#include "src/web/WebServerManager.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n[INIT] Inicializando Área27 Sinuca v2.0...");

  if (!LittleFS.begin()) {
    LittleFS.format();
    LittleFS.begin();
  }
  
  auth.begin();
  playerMgr.begin();
  matchMgr.begin();
  
  sysMgr.begin();
  webMgr.begin();
}

void loop() {
  sysMgr.loop();
  webMgr.loop();
  matchMgr.loop();
}
