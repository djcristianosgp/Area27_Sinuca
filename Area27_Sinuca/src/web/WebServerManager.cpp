#include "WebServerManager.h"
#include "../../WebPages.h"
#include "../system/SystemManager.h"
#include "../auth/AuthManager.h"
#include "../players/PlayerManager.h"
#include "../match/MatchManager.h"
#include <LittleFS.h>

WebServerManager webMgr;

// Legacy season data structure kept here for simplicity
#define MAX_SEASONS 12
SeasonRecord seasonsHistory[MAX_SEASONS];
int seasonCount = 0;


WebServerManager::WebServerManager() : server(80) {}

ESP8266WebServer& WebServerManager::getServer() {
    return server;
}

bool WebServerManager::extractToken(String& token) {
    if (server.hasHeader("Authorization")) {
        String authHeader = server.header("Authorization");
        if (authHeader.startsWith("Bearer ")) {
            token = authHeader.substring(7);
            return true;
        }
    }
    return false;
}

bool WebServerManager::checkAuthAdmin() {
    String token;
    if (extractToken(token)) {
        int pid;
        if (auth.validateToken(token, pid) && pid == -1) {
            return true;
        }
    }
    server.send(401, "application/json", "{\"error\":\"Acesso negado. Token administrativo inválido ou ausente.\"}");
    return false;
}

bool WebServerManager::checkAuthAny() {
    String token;
    if (extractToken(token)) {
        int pid;
        if (auth.validateToken(token, pid)) {
            return true; 
        }
    }
    server.send(401, "application/json", "{\"error\":\"Acesso negado. Autenticação necessária.\"}");
    return false;
}

// Global functions for legacy externs
bool checkAuthAdmin(ESP8266WebServer& srv) {
    return webMgr.checkAuthAdmin();
}

bool checkAuthAny(ESP8266WebServer& srv) {
    return webMgr.checkAuthAny();
}

bool WebServerManager::handleFileRead(String path) {
    if (path.endsWith("/")) path += "index.html";

    if (sysMgr.isAPMode()) {
        if (path == "/style.css") { server.send_P(200, "text/css", CSS_STYLE); return true; }
        server.send_P(200, "text/html", HTML_WIFI_CONFIG);
        return true;
    }

    if (path == "/index.html") { server.send_P(200, "text/html", HTML_INDEX); return true; }
    if (path == "/players.html") { server.send_P(200, "text/html", HTML_PLAYERS); return true; }
    if (path == "/match.html") { server.send_P(200, "text/html", HTML_MATCH); return true; }
    if (path == "/ranking.html") { server.send_P(200, "text/html", HTML_RANKING); return true; }
    if (path == "/settings.html") { server.send_P(200, "text/html", HTML_SETTINGS); return true; }
    if (path == "/about.html") { server.send_P(200, "text/html", HTML_ABOUT); return true; }
    if (path == "/tv" || path == "/tv.html") { server.send_P(200, "text/html", HTML_TV); return true; }
    if (path == "/profile.html") { server.send_P(200, "text/html", HTML_PROFILE); return true; }
    if (path == "/hall.html") { server.send_P(200, "text/html", HTML_HALL); return true; }
    if (path == "/championship.html") { server.send_P(200, "text/html", HTML_CHAMPIONSHIP); return true; }
    if (path == "/wifi.html") { server.send_P(200, "text/html", HTML_WIFI_CONFIG); return true; }
    if (path == "/style.css") { server.send_P(200, "text/css", CSS_STYLE); return true; }
    if (path == "/app.js") { server.send_P(200, "application/javascript", JS_APP); return true; }
    if (path == "/api.js") { server.send_P(200, "application/javascript", JS_API); return true; }

    return false;
}

void WebServerManager::begin() {
    server.collectHeaders("Authorization");

    // REST API v1 Routes
    server.on("/api/v1/tv", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        String json = "{\n";
        json += "  \"activeMatch\": " + String(matchMgr.activeMatch.active ? "true" : "false") + ",\n";
        json += "  \"ranking\": " + playerMgr.getPlayersJSON() + ",\n";
        json += "  \"history\": " + matchMgr.getHistoryJSON() + "\n";
        json += "}";
        server.send(200, "application/json", json);
    });

    server.on("/api/v1/history", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json", matchMgr.getHistoryJSON());
    });

    server.on("/api/v1/stats", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json", "{\"totalPlayers\":" + String(playerMgr.playerCount) + ",\"totalMatches\":" + String(matchMgr.matchHistoryCount) + "}");
    });

    server.on("/api/v1/seasons", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        String json = "[\n";
        for (int i = 0; i < seasonCount; i++) {
            json += "  {\"id\":" + String(seasonsHistory[i].id) + ",\"name\":\"" + seasonsHistory[i].name + "\",\"champion\":\"" + seasonsHistory[i].champion + "\",\"vice\":\"" + seasonsHistory[i].vice + "\",\"third\":\"" + seasonsHistory[i].third + "\"}";
            if (i < seasonCount - 1) json += ",";
            json += "\n";
        }
        json += "]";
        server.send(200, "application/json", json);
    });

    server.on("/api/v1/seasons/reset", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!checkAuthAdmin()) return;

        if (playerMgr.playerCount > 0) {
            int top1 = 0;
            int maxElo = -1;
            for (int i = 0; i < playerMgr.playerCount; i++) {
                if (playerMgr.players[i].elo > maxElo) { maxElo = playerMgr.players[i].elo; top1 = i; }
            }
            playerMgr.players[top1].titles_count++;

            if (seasonCount < MAX_SEASONS) {
                seasonsHistory[seasonCount] = { seasonCount + 1, "Temporada Mês " + String(seasonCount + 1), playerMgr.players[top1].nome, "Vice-Campeão", "Terceiro Colocado" };
                seasonCount++;
            }
        }

        for (int i = 0; i < playerMgr.playerCount; i++) {
            playerMgr.players[i].elo = 1000;
        }
        playerMgr.save();

        server.send(200, "application/json", "{\"success\":true,\"message\":\"Temporada encerrada e campeões coroados!\"}");
    });

    server.on("/api/v1/backup/export", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        String json = "{\n";
        json += "  \"version\": 2.0,\n";
        json += "  \"timestamp\": " + String(millis()) + ",\n";
        json += "  \"playerMgr.players\": " + playerMgr.getPlayersJSON() + ",\n";
        json += "  \"history\": " + matchMgr.getHistoryJSON() + "\n";
        json += "}";
        server.send(200, "application/json", json);
    });

    server.on("/api/v1/backup/import", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!server.hasArg("plain")) {
            server.send(400, "application/json", "{\"error\":\"Body de backup ausente\"}");
            return;
        }
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Backup restaurado com sucesso!\"}");
    });

    server.on("/api/v1/update/check", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        String jsonResponse = sysMgr.checkUpdate("2.0.7");
        if (jsonResponse.indexOf("\"error\"") != -1) {
            server.send(500, "application/json", jsonResponse);
        } else {
            server.send(200, "application/json", jsonResponse);
        }
    });

    server.on("/api/v1/update/start", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!checkAuthAdmin()) return;
        
        String binUrl = "";
        if (server.hasArg("plain")) {
            String body = server.arg("plain");
            int urlPos = body.indexOf("\"url\":\"");
            if (urlPos != -1) {
                int start = body.indexOf("\"", urlPos + 6) + 1;
                int end = body.indexOf("\"", start);
                binUrl = body.substring(start, end);
            }
        }
        if (binUrl.length() == 0) {
            binUrl = "https://raw.githubusercontent.com/djcristianosgp/Area27_Sinuca/main/firmware.bin";
        }

        server.send(200, "application/json", "{\"success\":true,\"message\":\"Iniciando atualização pelo GitHub. O ESP8266 irá reiniciar em instantes...\"}");
        delay(1000);
        sysMgr.startUpdate(binUrl);
    });

    // Standard API Routes
    server.on("/players", HTTP_GET, [this]() { playerMgr.handleGetPlayers(server); });
    server.on("/players", HTTP_POST, [this]() { playerMgr.handlePostPlayers(server); });
    server.on("/players/login", HTTP_POST, [this]() { playerMgr.handleLoginPlayer(server); });
    server.on("/players/delete", HTTP_POST, [this]() { playerMgr.handleDeletePlayer(server); });
    server.on("/players/reset-password", HTTP_POST, [this]() { playerMgr.handleResetPlayerPassword(server); });
    server.on("/players/clear", HTTP_POST, [this]() { playerMgr.handleClearPlayers(server); });
    
    server.on("/ranking", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json", playerMgr.getPlayersJSON());
    });
    
    server.on("/ranking/reset", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!checkAuthAdmin()) return;
        for (int i = 0; i < playerMgr.playerCount; i++) {
            playerMgr.players[i].elo = 1000;
            playerMgr.players[i].vitorias = 0;
            playerMgr.players[i].derrotas = 0;
            playerMgr.players[i].current_streak = 0;
        }
        playerMgr.save();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Ranking zerado\"}");
    });

    server.on("/settings/auth", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!server.hasArg("plain")) return;
        String body = server.arg("plain");
        String pin = "";
        int pinPos = body.indexOf("\"pin\":\"");
        if (pinPos != -1) {
            int pStart = body.indexOf("\"", pinPos + 5) + 1;
            int pEnd = body.indexOf("\"", pStart);
            pin = body.substring(pStart, pEnd);
        }

        String token;
        if (auth.loginAdmin(pin, token)) {
            server.send(200, "application/json", "{\"success\":true,\"token\":\"" + token + "\",\"message\":\"Acesso liberado\"}");
        } else {
            server.send(401, "application/json", "{\"error\":\"PIN de Administrador incorreto. Tente novamente.\"}");
        }
    });

    server.on("/settings/auth/config", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (auth.isAdminConfigured()) {
            server.send(403, "application/json", "{\"error\":\"Administrador já configurado\"}");
            return;
        }
        
        if (!server.hasArg("plain")) return;
        String body = server.arg("plain");
        String pin = "";
        int pinPos = body.indexOf("\"pin\":\"");
        if (pinPos != -1) {
            int pStart = body.indexOf("\"", pinPos + 5) + 1;
            int pEnd = body.indexOf("\"", pStart);
            pin = body.substring(pStart, pEnd);
        }
        
        if (auth.configureAdminPin(pin)) {
            server.send(200, "application/json", "{\"success\":true,\"message\":\"PIN Administrativo configurado com sucesso!\"}");
        } else {
            server.send(400, "application/json", "{\"error\":\"Erro ao configurar o PIN (mínimo 4 caracteres)\"}");
        }
    });

    server.on("/match/create", HTTP_POST, [this]() { matchMgr.handleCreateMatch(server); });
    server.on("/match/join", HTTP_POST, [this]() { matchMgr.handleJoinMatch(server); });
    server.on("/match/respond", HTTP_POST, [this]() { matchMgr.handleRespondInvite(server); });
    server.on("/match/active", HTTP_GET, [this]() { matchMgr.handleGetActiveMatch(server); });
    server.on("/match/finish", HTTP_POST, [this]() { matchMgr.handleFinishMatch(server); });
    server.on("/match/cancel", HTTP_POST, [this]() { matchMgr.handleCancelMatch(server); });

    server.on("/wifi/scan", HTTP_GET, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json", sysMgr.scanNetworks());
    });

    server.on("/wifi/save", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!checkAuthAdmin()) return;
        String newSSID = server.hasArg("ssid") ? server.arg("ssid") : "";
        String newPass = server.hasArg("password") ? server.arg("password") : "";

        if (newSSID.length() > 0) {
            sysMgr.saveWifiConfig(newSSID, newPass);
            server.send(200, "text/html", "<h2>Configuração Salva! Reiniciando...</h2>");
            delay(1500);
            ESP.restart();
        } else {
            server.send(400, "text/html", "<h2>Erro: SSID não informado</h2>");
        }
    });

    server.on("/wifi/reset", HTTP_POST, [this]() {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        if (!checkAuthAdmin()) return;
        sysMgr.resetWifiConfig();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Wi-Fi resetado. Reiniciando...\"}");
        delay(1000);
        ESP.restart();
    });

    // Captive Portal Redirect & File Reader
    server.onNotFound([this]() {
        if (sysMgr.isAPMode()) {
            server.send_P(200, "text/html", HTML_WIFI_CONFIG);
        } else if (!handleFileRead(server.uri())) {
            server.send(404, "text/plain", "404: Arquivo nao encontrado");
        }
    });

    server.begin();
    Serial.println("[SERVER] Servidor HTTP Área27 Sinuca v2.0 ativo na porta 80.");
}

void WebServerManager::loop() {
    server.handleClient();
}
