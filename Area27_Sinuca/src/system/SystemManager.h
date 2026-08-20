#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>

class SystemManager {
private:
    DNSServer dnsServer;
    bool apMode;
    String wifiSSID;
    String wifiPassword;

    bool loadWifiConfig();

public:
    SystemManager();
    void begin();
    void loop();
    
    bool isAPMode() const;
    void startAPMode();
    void saveWifiConfig(const String& ssid, const String& password);
    void resetWifiConfig();
    
    String scanNetworks();
    
    String checkUpdate(const String& currentVersion);
    void startUpdate(const String& binUrl);
};

extern SystemManager sysMgr;

#endif
