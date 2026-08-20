#include "SystemManager.h"
#include <LittleFS.h>
#include <ESP8266mDNS.h>
#include <ESP8266NetBIOS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>

SystemManager sysMgr;

SystemManager::SystemManager() : apMode(false) {}

bool SystemManager::loadWifiConfig() {
  if (!LittleFS.exists("/wifi_config.json")) return false;
  File file = LittleFS.open("/wifi_config.json", "r");
  if (!file) return false;
  String content = file.readString();
  file.close();

  int ssidPos = content.indexOf("\"ssid\"");
  if (ssidPos != -1) {
    int colonPos = content.indexOf(":", ssidPos);
    int start = content.indexOf("\"", colonPos) + 1;
    int end = content.indexOf("\"", start);
    wifiSSID = content.substring(start, end);
  }

  int passPos = content.indexOf("\"password\"");
  if (passPos != -1) {
    int colonPos = content.indexOf(":", passPos);
    int start = content.indexOf("\"", colonPos) + 1;
    int end = content.indexOf("\"", start);
    wifiPassword = content.substring(start, end);
  }

  return (wifiSSID.length() > 0);
}

void SystemManager::saveWifiConfig(const String& ssid, const String& password) {
  File file = LittleFS.open("/wifi_config.json", "w");
  if (!file) return;
  file.print("{\n  \"ssid\": \"" + ssid + "\",\n  \"password\": \"" + password + "\"\n}\n");
  file.close();
}

void SystemManager::resetWifiConfig() {
  if (LittleFS.exists("/wifi_config.json")) LittleFS.remove("/wifi_config.json");
}

bool SystemManager::isAPMode() const {
  return apMode;
}

void SystemManager::startAPMode() {
  apMode = true;
  WiFi.mode(WIFI_AP);
  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP("Area27-Sinuca-Config");

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", apIP);
  Serial.println("[AP] Modo Ponto de Acesso ativado. SSID: Area27-Sinuca-Config");
}

void SystemManager::begin() {
  bool hasSavedWifi = loadWifiConfig();

  if (hasSavedWifi) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED && timeout < 25) {
      delay(500);
      timeout++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      if (MDNS.begin("sinuca")) {
        MDNS.addService("http", "tcp", 80);
        Serial.println("[mDNS] Servidor mDNS ativo! Acesse: http://sinuca.local");
      }
      NBNS.begin("sinuca");
    } else {
      startAPMode();
    }
  } else {
    startAPMode();
  }
}

void SystemManager::loop() {
  if (apMode) {
    dnsServer.processNextRequest();
  } else {
    MDNS.update();
  }
}

String SystemManager::scanNetworks() {
  int n = WiFi.scanNetworks();
  String json = "[";
  for (int i = 0; i < n; ++i) {
    if (i > 0) json += ",";
    json += "{\"ssid\":\"" + WiFi.SSID(i) + "\",\"rssi\":" + String(WiFi.RSSI(i)) + "}";
  }
  json += "]";
  return json;
}

String SystemManager::checkUpdate(const String& currentVersion) {
  if (WiFi.status() != WL_CONNECTED) {
    return "{\"error\":\"ESP8266 não está conectado à internet Wi-Fi.\"}";
  }

  WiFiClientSecure client;
  client.setInsecure();
  client.setBufferSizes(1024, 1024);
  client.setTimeout(10000);

  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  
  String cb = String(millis());
  String urlsToTry[2] = {
    "https://raw.githubusercontent.com/djcristianosgp/Area27_Sinuca/main/Area27_Sinuca/version.json?cb=" + cb,
    "https://raw.githubusercontent.com/djcristianosgp/Area27_Sinuca/master/Area27_Sinuca/version.json?cb=" + cb
  };

  int httpCode = 0;
  String payload = "";

  for (int i = 0; i < 2; i++) {
    if (http.begin(client, urlsToTry[i])) {
      httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        http.end();
        break;
      }
      http.end();
    }
  }

  if (httpCode != HTTP_CODE_OK) {
    return "{\"error\":\"O arquivo version.json ainda não está disponível publicamente no GitHub (HTTP " + String(httpCode) + "). Realize o commit e push de version.json para a branch main.\"}";
  }

  String latestVersion = currentVersion;
  String firmwareUrl = "";
  String changelog = "";

  int verPos = payload.indexOf("\"version\":\"");
  if (verPos != -1) {
    int start = payload.indexOf("\"", verPos + 10) + 1;
    int end = payload.indexOf("\"", start);
    latestVersion = payload.substring(start, end);
  }

  int urlPos = payload.indexOf("\"firmware_url\":\"");
  if (urlPos != -1) {
    int start = payload.indexOf("\"", urlPos + 15) + 1;
    int end = payload.indexOf("\"", start);
    firmwareUrl = payload.substring(start, end);
  }

  int changePos = payload.indexOf("\"changelog\":\"");
  if (changePos != -1) {
    int start = payload.indexOf("\"", changePos + 12) + 1;
    int end = payload.indexOf("\"", start);
    changelog = payload.substring(start, end);
  }

  bool updateAvailable = (latestVersion != currentVersion && latestVersion.length() > 0);

  String jsonResponse = "{";
  jsonResponse += "\"current_version\":\"" + currentVersion + "\",";
  jsonResponse += "\"latest_version\":\"" + latestVersion + "\",";
  jsonResponse += "\"update_available\":" + String(updateAvailable ? "true" : "false") + ",";
  jsonResponse += "\"firmware_url\":\"" + firmwareUrl + "\",";
  jsonResponse += "\"changelog\":\"" + changelog + "\"";
  jsonResponse += "}";

  return jsonResponse;
}

void SystemManager::startUpdate(const String& binUrl) {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }
  
  WiFiClientSecure client;
  client.setInsecure();
  client.setBufferSizes(1024, 1024);
  ESPhttpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, binUrl);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("[OTA] HTTP update failed. Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[OTA] HTTP update: No updates.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[OTA] HTTP update OK. Rebooting...");
      break;
  }
}
