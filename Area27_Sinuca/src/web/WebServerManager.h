#ifndef WEB_SERVER_MANAGER_H
#define WEB_SERVER_MANAGER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

class WebServerManager {
private:
    ESP8266WebServer server;
    bool handleFileRead(String path);

public:
    WebServerManager();
    void begin();
    void loop();
    
    // Auth helpers used by other managers
    bool extractToken(String& token);
    bool checkAuthAdmin();
    bool checkAuthAny();

    // The raw server instance for backward compatibility with other managers
    ESP8266WebServer& getServer();
};

extern WebServerManager webMgr;

// For legacy extern references in PlayerManager and MatchManager
bool checkAuthAdmin(ESP8266WebServer& server);
bool checkAuthAny(ESP8266WebServer& server);

#endif
