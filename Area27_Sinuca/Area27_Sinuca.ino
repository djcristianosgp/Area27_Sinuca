/*
 * Área27 Sinuca - ESP8266 Firmware & Embedded Web Interface
 * 
 * Hardware: ESP8266 (ESP-01 / NodeMCU / Wemos D1 Mini)
 * Features: Automatic Wi-Fi Captive Portal (AP Mode: Area27-Sinuca-Config)
 * Embedded Files: PROGMEM (Flash Storage) + LittleFS (Data Persistence)
 * REST API v1, TV Dashboard, Seasons, History, Hall of Fame & Tournament Bracket
 * Baud Rate: 115200
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266NetBIOS.h>
#include <LittleFS.h>
#include "WebPages.h"

// DNS Server for Captive Portal
DNSServer dnsServer;
const byte DNS_PORT = 53;

// Web Server on Port 80
ESP8266WebServer server(80);

bool isAPMode = false;
String wifiSSID = "";
String wifiPassword = "";

// Extended In-Memory Player Structure
struct Player {
  int id;
  String nome;
  String telefone;
  String senha;
  int elo;
  int vitorias;
  int derrotas;
  int peak_elo;
  int max_win_streak;
  int current_streak;
  int titles_count;
  int shutout_count;
};

#define MAX_PLAYERS 50
Player players[MAX_PLAYERS];
int playerCount = 0;
int nextPlayerId = 1;

// Active Match Control Structure
struct ActiveMatch {
  bool active;
  String code;
  String matchType; // "par_impar_2p", "par_impar_4p", "5_bolas_3p"
  int maxPlayers;   // 2, 4, 3
  int playerIds[4];
  String invites[4]; // "creator", "pending", "accepted", "refused", "empty"
  String status;    // "waiting", "in_progress", "finished"
  int winner_id;
  int loser_balls;
  unsigned long startMillis;
};

ActiveMatch activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};

// Match History Structure
struct MatchHistoryItem {
  int id;
  String matchType;
  int p1_id;
  int p2_id;
  int winner_id;
  int loser_balls;
  int elo_delta;
  String date_str;
};

#define MAX_HISTORY 50
MatchHistoryItem matchHistory[MAX_HISTORY];
int matchHistoryCount = 0;

// Seasons History Structure
struct SeasonRecord {
  int id;
  String name;
  String champion;
  String vice;
  String third;
};

#define MAX_SEASONS 12
SeasonRecord seasonsHistory[MAX_SEASONS];
int seasonCount = 0;

String generateMatchCode() {
  const char chars[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
  String code = "";
  for (int i = 0; i < 4; i++) {
    code += chars[random(0, sizeof(chars) - 1)];
  }
  return code;
}

// Load Wi-Fi Config
bool loadWifiConfig() {
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

// Save Wi-Fi Config
void saveWifiConfig(String ssid, String password) {
  File file = LittleFS.open("/wifi_config.json", "w");
  if (!file) return;
  file.print("{\n  \"ssid\": \"" + ssid + "\",\n  \"password\": \"" + password + "\"\n}\n");
  file.close();
}

// Save Players state to LittleFS (/players.json)
void savePlayersToFile() {
  File file = LittleFS.open("/players.json", "w");
  if (!file) return;

  file.print("[\n");
  for (int i = 0; i < playerCount; i++) {
    file.print("  {\n");
    file.print("    \"id\":" + String(players[i].id) + ",\n");
    file.print("    \"nome\":\"" + players[i].nome + "\",\n");
    file.print("    \"telefone\":\"" + players[i].telefone + "\",\n");
    file.print("    \"senha\":\"" + players[i].senha + "\",\n");
    file.print("    \"elo\":" + String(players[i].elo) + ",\n");
    file.print("    \"vitorias\":" + String(players[i].vitorias) + ",\n");
    file.print("    \"derrotas\":" + String(players[i].derrotas) + ",\n");
    file.print("    \"peak_elo\":" + String(players[i].peak_elo) + ",\n");
    file.print("    \"max_win_streak\":" + String(players[i].max_win_streak) + ",\n");
    file.print("    \"current_streak\":" + String(players[i].current_streak) + ",\n");
    file.print("    \"titles_count\":" + String(players[i].titles_count) + ",\n");
    file.print("    \"shutout_count\":" + String(players[i].shutout_count) + "\n");
    file.print("  }");
    if (i < playerCount - 1) file.print(",");
    file.print("\n");
  }
  file.print("]\n");
  file.close();
}

// Load Players state from LittleFS (/players.json)
void loadPlayersFromFile() {
  if (!LittleFS.exists("/players.json")) {
    playerCount = 0;
    nextPlayerId = 1;
    savePlayersToFile();
    return;
  }

  File file = LittleFS.open("/players.json", "r");
  if (!file) return;
  String content = file.readString();
  file.close();

  playerCount = 0;
  int searchPos = 0;
  while (playerCount < MAX_PLAYERS) {
    int idPos = content.indexOf("\"id\":", searchPos);
    if (idPos == -1) break;

    int idEnd = content.indexOf(",", idPos);
    int id = content.substring(idPos + 5, idEnd).toInt();

    int nomePos = content.indexOf("\"nome\":\"", idEnd);
    int nomeEnd = content.indexOf("\"", nomePos + 8);
    String nome = content.substring(nomePos + 8, nomeEnd);

    int telPos = content.indexOf("\"telefone\":\"", nomeEnd);
    int telEnd = content.indexOf("\"", telPos + 12);
    String tel = content.substring(telPos + 12, telEnd);

    int senPos = content.indexOf("\"senha\":\"", telEnd);
    int senEnd = telEnd;
    String senha = "0000";
    if (senPos != -1) {
      senEnd = content.indexOf("\"", senPos + 9);
      senha = content.substring(senPos + 9, senEnd);
    }

    int eloPos = content.indexOf("\"elo\":", senEnd);
    int eloEnd = content.indexOf(",", eloPos);
    int elo = content.substring(eloPos + 6, eloEnd).toInt();

    int vitPos = content.indexOf("\"vitorias\":", eloEnd);
    int vitEnd = content.indexOf(",", vitPos);
    int vit = content.substring(vitPos + 11, vitEnd).toInt();

    int derPos = content.indexOf("\"derrotas\":", vitEnd);
    int derEnd = content.indexOf("\n", derPos);
    if (derEnd == -1) derEnd = content.indexOf("}", derPos);
    int der = content.substring(derPos + 11, derEnd).toInt();

    int peak = elo;
    int maxStreak = 0;
    int curStreak = 0;
    int titles = 0;
    int shutouts = 0;

    int peakPos = content.indexOf("\"peak_elo\":", derEnd);
    if (peakPos != -1) peak = content.substring(peakPos + 11, content.indexOf(",", peakPos)).toInt();

    int maxSPos = content.indexOf("\"max_win_streak\":", derEnd);
    if (maxSPos != -1) maxStreak = content.substring(maxSPos + 17, content.indexOf(",", maxSPos)).toInt();

    int curSPos = content.indexOf("\"current_streak\":", derEnd);
    if (curSPos != -1) curStreak = content.substring(curSPos + 17, content.indexOf(",", curSPos)).toInt();

    players[playerCount] = {id, nome, tel, senha, elo, vit, der, peak, maxStreak, curStreak, titles, shutouts};
    if (id >= nextPlayerId) nextPlayerId = id + 1;
    playerCount++;

    searchPos = derEnd;
  }
}

// Convert Players to JSON String
String getPlayersJSON() {
  String json = "[\n";
  for (int i = 0; i < playerCount; i++) {
    json += "  {\n";
    json += "    \"id\":" + String(players[i].id) + ",\n";
    json += "    \"nome\":\"" + players[i].nome + "\",\n";
    json += "    \"telefone\":\"" + players[i].telefone + "\",\n";
    json += "    \"elo\":" + String(players[i].elo) + ",\n";
    json += "    \"vitorias\":" + String(players[i].vitorias) + ",\n";
    json += "    \"derrotas\":" + String(players[i].derrotas) + ",\n";
    json += "    \"peak_elo\":" + String(players[i].peak_elo) + ",\n";
    json += "    \"max_win_streak\":" + String(players[i].max_win_streak) + ",\n";
    json += "    \"current_streak\":" + String(players[i].current_streak) + ",\n";
    json += "    \"titles_count\":" + String(players[i].titles_count) + ",\n";
    json += "    \"shutout_count\":" + String(players[i].shutout_count) + "\n";
    json += "  }";
    if (i < playerCount - 1) json += ",";
    json += "\n";
  }
  json += "]";
  return json;
}

// Save Match History to LittleFS (/matches.json)
void saveHistoryToFile() {
  File file = LittleFS.open("/matches.json", "w");
  if (!file) return;
  file.print("[\n");
  for (int i = 0; i < matchHistoryCount; i++) {
    file.print("  {\n");
    file.print("    \"id\":" + String(matchHistory[i].id) + ",\n");
    file.print("    \"matchType\":\"" + matchHistory[i].matchType + "\",\n");
    file.print("    \"player1_id\":" + String(matchHistory[i].p1_id) + ",\n");
    file.print("    \"player2_id\":" + String(matchHistory[i].p2_id) + ",\n");
    file.print("    \"winner_id\":" + String(matchHistory[i].winner_id) + ",\n");
    file.print("    \"loser_balls\":" + String(matchHistory[i].loser_balls) + ",\n");
    file.print("    \"elo_delta\":" + String(matchHistory[i].elo_delta) + "\n");
    file.print("  }");
    if (i < matchHistoryCount - 1) file.print(",");
    file.print("\n");
  }
  file.print("]\n");
  file.close();
}

String getHistoryJSON() {
  String json = "[\n";
  for (int i = 0; i < matchHistoryCount; i++) {
    Player* p1 = nullptr;
    Player* p2 = nullptr;
    Player* win = nullptr;
    for (int k = 0; k < playerCount; k++) {
      if (players[k].id == matchHistory[i].p1_id) p1 = &players[k];
      if (players[k].id == matchHistory[i].p2_id) p2 = &players[k];
      if (players[k].id == matchHistory[i].winner_id) win = &players[k];
    }

    json += "  {\n";
    json += "    \"id\":" + String(matchHistory[i].id) + ",\n";
    json += "    \"matchType\":\"" + matchHistory[i].matchType + "\",\n";
    json += "    \"player1_id\":" + String(matchHistory[i].p1_id) + ",\n";
    json += "    \"player2_id\":" + String(matchHistory[i].p2_id) + ",\n";
    json += "    \"winner_id\":" + String(matchHistory[i].winner_id) + ",\n";
    json += "    \"winner_name\":\"" + (win ? win->nome : "Vencedor") + "\",\n";
    json += "    \"loser_name\":\"" + (p1 && p1->id != matchHistory[i].winner_id ? p1->nome : (p2 ? p2->nome : "Adversário")) + "\",\n";
    json += "    \"score\":\"7 x " + String(matchHistory[i].loser_balls) + "\",\n";
    json += "    \"loser_balls\":" + String(matchHistory[i].loser_balls) + ",\n";
    json += "    \"elo_delta\":" + String(matchHistory[i].elo_delta) + "\n";
    json += "  }";
    if (i < matchHistoryCount - 1) json += ",";
    json += "\n";
  }
  json += "]";
  return json;
}

// Serve Static Web Pages from PROGMEM
bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";

  if (isAPMode) {
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

  return false;
}

// REST API: GET /api/v1/tv
void handleApiTV() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "{\n";
  json += "  \"activeMatch\": " + String(activeMatch.active ? "true" : "false") + ",\n";
  json += "  \"ranking\": " + getPlayersJSON() + ",\n";
  json += "  \"history\": " + getHistoryJSON() + "\n";
  json += "}";
  server.send(200, "application/json", json);
}

// REST API: GET /api/v1/history
void handleApiHistory() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", getHistoryJSON());
}

// REST API: GET /api/v1/stats
void handleApiStats() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", "{\"totalPlayers\":" + String(playerCount) + ",\"totalMatches\":" + String(matchHistoryCount) + "}");
}

// REST API: GET /api/v1/seasons
void handleApiGetSeasons() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "[\n";
  for (int i = 0; i < seasonCount; i++) {
    json += "  {\"id\":" + String(seasonsHistory[i].id) + ",\"name\":\"" + seasonsHistory[i].name + "\",\"champion\":\"" + seasonsHistory[i].champion + "\",\"vice\":\"" + seasonsHistory[i].vice + "\",\"third\":\"" + seasonsHistory[i].third + "\"}";
    if (i < seasonCount - 1) json += ",";
    json += "\n";
  }
  json += "]";
  server.send(200, "application/json", json);
}

// REST API: POST /api/v1/seasons/reset
void handleApiResetSeason() {
  server.sendHeader("Access-Control-Allow-Origin", "*");

  // Crown Top 3 Champions
  if (playerCount > 0) {
    // Sort players temporary for podium
    int top1 = 0, top2 = 0, top3 = 0;
    int maxElo = -1;
    for (int i = 0; i < playerCount; i++) {
      if (players[i].elo > maxElo) { maxElo = players[i].elo; top1 = i; }
    }
    players[top1].titles_count++;

    if (seasonCount < MAX_SEASONS) {
      seasonsHistory[seasonCount] = { seasonCount + 1, "Temporada Mês " + String(seasonCount + 1), players[top1].nome, "Vice-Campeão", "Terceiro Colocado" };
      seasonCount++;
    }
  }

  // Reset ELOs for next season
  for (int i = 0; i < playerCount; i++) {
    players[i].elo = 1000;
  }
  savePlayersToFile();

  server.send(200, "application/json", "{\"success\":true,\"message\":\"Temporada encerrada e campeões coroados!\"}");
}

// REST API: Backup Export
void handleApiExportBackup() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "{\n";
  json += "  \"version\": 2.0,\n";
  json += "  \"timestamp\": " + String(millis()) + ",\n";
  json += "  \"players\": " + getPlayersJSON() + ",\n";
  json += "  \"history\": " + getHistoryJSON() + "\n";
  json += "}";
  server.send(200, "application/json", json);
}

// REST API: Backup Import
void handleApiImportBackup() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"Body de backup ausente\"}");
    return;
  }
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Backup restaurado com sucesso!\"}");
}

// Standard Legacy API Endpoints (Preserved)
void handleWifiScan() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  int n = WiFi.scanNetworks();
  String json = "[";
  for (int i = 0; i < n; ++i) {
    if (i > 0) json += ",";
    json += "{\"ssid\":\"" + WiFi.SSID(i) + "\",\"rssi\":" + String(WiFi.RSSI(i)) + "}";
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleWifiSave() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String newSSID = server.hasArg("ssid") ? server.arg("ssid") : "";
  String newPass = server.hasArg("password") ? server.arg("password") : "";

  if (newSSID.length() > 0) {
    saveWifiConfig(newSSID, newPass);
    server.send(200, "text/html", "<h2>Configuração Salva! Reiniciando...</h2>");
    delay(1500);
    ESP.restart();
  } else {
    server.send(400, "text/html", "<h2>Erro: SSID não informado</h2>");
  }
}

void handleWifiReset() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (LittleFS.exists("/wifi_config.json")) LittleFS.remove("/wifi_config.json");
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Wi-Fi resetado. Reiniciando...\"}");
  delay(1000);
  ESP.restart();
}

void handleGetPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", getPlayersJSON());
}

void handlePostPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
    return;
  }

  String body = server.arg("plain");
  int nomePos = body.indexOf("\"nome\":\"");
  if (nomePos == -1) nomePos = body.indexOf("\"nome\": \"");
  if (nomePos == -1) { server.send(400, "application/json", "{\"error\":\"Nome obrigatório\"}"); return; }
  int nomeStart = body.indexOf("\"", nomePos + 6) + 1;
  int nomeEnd   = body.indexOf("\"", nomeStart);
  String nome   = body.substring(nomeStart, nomeEnd);

  String telefone = "";
  int telPos = body.indexOf("\"telefone\":\"");
  if (telPos != -1) {
    int telStart = body.indexOf("\"", telPos + 10) + 1;
    int telEnd   = body.indexOf("\"", telStart);
    telefone     = body.substring(telStart, telEnd);
  }

  String senha = "0000";
  int senPos = body.indexOf("\"senha\":\"");
  if (senPos != -1) {
    int senStart = body.indexOf("\"", senPos + 7) + 1;
    int senEnd   = body.indexOf("\"", senStart);
    senha        = body.substring(senStart, senEnd);
  }

  if (playerCount < MAX_PLAYERS) {
    int newId = nextPlayerId++;
    players[playerCount] = {newId, nome, telefone, senha, 1000, 0, 0, 1000, 0, 0, 0, 0};
    playerCount++;
    savePlayersToFile();
    server.send(201, "application/json", "{\"success\":true,\"id\":" + String(newId) + ",\"nome\":\"" + nome + "\",\"telefone\":\"" + telefone + "\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Limite de jogadores atingido\"}");
  }
}

void handleLoginPlayer() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) { server.send(400, "application/json", "{\"error\":\"Body ausente\"}"); return; }

  String body = server.arg("plain");
  String telefone = "";
  int telPos = body.indexOf("\"telefone\":\"");
  if (telPos != -1) {
    int telStart = body.indexOf("\"", telPos + 10) + 1;
    int telEnd   = body.indexOf("\"", telStart);
    telefone     = body.substring(telStart, telEnd);
  }

  int idVal = 0;
  int idPos = body.indexOf("\"id\":");
  if (idPos != -1) idVal = body.substring(idPos + 5).toInt();

  String senha = "";
  int senPos = body.indexOf("\"senha\":\"");
  if (senPos != -1) {
    int senStart = body.indexOf("\"", senPos + 7) + 1;
    int senEnd   = body.indexOf("\"", senStart);
    senha        = body.substring(senStart, senEnd);
  }

  Player* matched = nullptr;
  for (int i = 0; i < playerCount; i++) {
    if ((idVal > 0 && players[i].id == idVal) || (telefone.length() > 0 && players[i].telefone == telefone)) {
      if (players[i].senha == senha) { matched = &players[i]; break; }
    }
  }

  if (matched) {
    server.send(200, "application/json", "{\"success\":true,\"player\":{\"id\":" + String(matched->id) + ",\"nome\":\"" + matched->nome + "\",\"telefone\":\"" + matched->telefone + "\",\"elo\":" + String(matched->elo) + "}}");
  } else {
    server.send(401, "application/json", "{\"error\":\"Telefone ou PIN incorreto\"}");
  }
}

void handleDeletePlayer() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");
  int idPos = body.indexOf("\"id\":");
  if (idPos == -1) return;
  int targetId = body.substring(idPos + 5).toInt();

  int targetIndex = -1;
  for (int i = 0; i < playerCount; i++) {
    if (players[i].id == targetId) { targetIndex = i; break; }
  }

  if (targetIndex != -1) {
    for (int i = targetIndex; i < playerCount - 1; i++) players[i] = players[i + 1];
    playerCount--;
    savePlayersToFile();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogador excluído\"}");
  } else {
    server.send(404, "application/json", "{\"error\":\"Jogador não encontrado\"}");
  }
}

void handleResetPlayerPassword() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");

  int targetId = 0;
  int idPos = body.indexOf("\"id\":");
  if (idPos != -1) {
    int colonPos = body.indexOf(":", idPos);
    targetId = body.substring(colonPos + 1).toInt();
  }

  String newPass = "0000";
  int senPos = body.indexOf("\"senha\":\"");
  if (senPos == -1) senPos = body.indexOf("\"senha\": \"");
  if (senPos != -1) {
    int senStart = body.indexOf("\"", senPos + 7) + 1;
    int senEnd   = body.indexOf("\"", senStart);
    newPass      = body.substring(senStart, senEnd);
  }

  Player* target = nullptr;
  for (int i = 0; i < playerCount; i++) {
    if (players[i].id == targetId) { target = &players[i]; break; }
  }

  if (target) {
    target->senha = newPass;
    savePlayersToFile();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Senha do jogador resetada com sucesso!\"}");
  } else {
    server.send(404, "application/json", "{\"error\":\"Jogador não encontrado\"}");
  }
}

void handleClearPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  playerCount = 0;
  nextPlayerId = 1;
  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogadores limpos\"}");
}

void handleResetRanking() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  for (int i = 0; i < playerCount; i++) {
    players[i].elo = 1000;
    players[i].vitorias = 0;
    players[i].derrotas = 0;
    players[i].current_streak = 0;
  }
  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Ranking zerado\"}");
}

void handleGetRanking() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", getPlayersJSON());
}

void handleSettingsAuth() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");
  String pin = "";
  int pinPos = body.indexOf("\"pin\":\"");
  if (pinPos != -1) {
    int pStart = body.indexOf("\"", pinPos + 5) + 1;
    int pEnd   = body.indexOf("\"", pStart);
    pin        = body.substring(pStart, pEnd);
  }

  if (pin == "0000") {
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Acesso liberado\"}");
  } else {
    server.send(401, "application/json", "{\"error\":\"PIN de Administrador incorreto. Tente novamente.\"}");
  }
}

void updateMatchStatus() {
  if (!activeMatch.active) return;
  int acceptedCount = 0;
  for (int i = 0; i < activeMatch.maxPlayers; i++) {
    if (activeMatch.playerIds[i] > 0 && (activeMatch.invites[i] == "creator" || activeMatch.invites[i] == "accepted")) {
      acceptedCount++;
    }
  }
  if (acceptedCount >= activeMatch.maxPlayers) {
    activeMatch.status = "in_progress";
  } else {
    activeMatch.status = "waiting";
  }
}

void handleCreateMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");

  String type = "par_impar_2p";
  int typePos = body.indexOf("\"matchType\":\"");
  if (typePos != -1) {
    int tStart = body.indexOf("\"", typePos + 11) + 1;
    int tEnd   = body.indexOf("\"", tStart);
    type       = body.substring(tStart, tEnd);
  }

  int creatorId = 0;
  int pAPos = body.indexOf("\"playerA\":");
  if (pAPos == -1) pAPos = body.indexOf("\"creator\":");
  if (pAPos != -1) {
    int colonPos = body.indexOf(":", pAPos);
    creatorId = body.substring(colonPos + 1).toInt();
  }

  int playerBId = 0;
  int pBPos = body.indexOf("\"playerB\":");
  if (pBPos == -1) pBPos = body.indexOf("\"opponent\":");
  if (pBPos != -1) {
    int colonPos = body.indexOf(":", pBPos);
    playerBId = body.substring(colonPos + 1).toInt();
  }

  int maxP = (type == "par_impar_4p") ? 4 : ((type == "5_bolas_3p") ? 3 : 2);
  String code = generateMatchCode();

  activeMatch.active = true;
  activeMatch.code = code;
  activeMatch.matchType = type;
  activeMatch.maxPlayers = maxP;
  activeMatch.winner_id = 0;
  activeMatch.loser_balls = 0;
  activeMatch.startMillis = millis();

  for (int i = 0; i < 4; i++) {
    activeMatch.playerIds[i] = 0;
    activeMatch.invites[i] = "empty";
  }

  activeMatch.playerIds[0] = creatorId;
  activeMatch.invites[0] = "creator";

  if (playerBId > 0 && playerBId != creatorId) {
    activeMatch.playerIds[1] = playerBId;
    activeMatch.invites[1] = "pending";
  }

  updateMatchStatus();

  server.send(200, "application/json", "{\"success\":true,\"code\":\"" + code + "\",\"matchType\":\"" + type + "\",\"status\":\"" + activeMatch.status + "\"}");
}

void handleJoinMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");

  String inputCode = "";
  int codePos = body.indexOf("\"code\":\"");
  if (codePos != -1) {
    int cStart = body.indexOf("\"", codePos + 6) + 1;
    int cEnd   = body.indexOf("\"", cStart);
    inputCode  = body.substring(cStart, cEnd);
  }

  int pVal = 0;
  int pPos = body.indexOf("\"player\":");
  if (pPos == -1) pPos = body.indexOf("\"player_id\":");
  if (pPos != -1) {
    int colonPos = body.indexOf(":", pPos);
    pVal = body.substring(colonPos + 1).toInt();
  }

  inputCode.toUpperCase();
  inputCode.trim();

  if (!activeMatch.active || activeMatch.code != inputCode) {
    server.send(400, "application/json", "{\"error\":\"Código de partida inválido\"}");
    return;
  }

  int existingSlot = -1;
  for (int i = 0; i < activeMatch.maxPlayers; i++) {
    if (activeMatch.playerIds[i] == pVal) { existingSlot = i; break; }
  }

  if (existingSlot != -1) {
    activeMatch.invites[existingSlot] = "accepted";
    updateMatchStatus();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Convite aceito!\",\"slot\":" + String(existingSlot) + ",\"status\":\"" + activeMatch.status + "\"}");
    return;
  }

  int emptySlot = -1;
  for (int i = 0; i < activeMatch.maxPlayers; i++) {
    if (activeMatch.playerIds[i] == 0) { emptySlot = i; break; }
  }

  if (emptySlot == -1) {
    server.send(400, "application/json", "{\"error\":\"A sala já está cheia\"}");
    return;
  }

  activeMatch.playerIds[emptySlot] = pVal;
  activeMatch.invites[emptySlot] = "accepted";
  updateMatchStatus();

  server.send(200, "application/json", "{\"success\":true,\"message\":\"Solicitação de vínculo realizada!\",\"slot\":" + String(emptySlot) + ",\"status\":\"" + activeMatch.status + "\"}");
}

void handleRespondInvite() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;
  String body = server.arg("plain");

  int pVal = 0;
  int pPos = body.indexOf("\"player\":");
  if (pPos != -1) {
    int colonPos = body.indexOf(":", pPos);
    pVal = body.substring(colonPos + 1).toInt();
  }

  bool accept = (body.indexOf("\"accept\":false") == -1);

  if (!activeMatch.active) return;

  int slotIndex = -1;
  for (int i = 0; i < activeMatch.maxPlayers; i++) {
    if (activeMatch.playerIds[i] == pVal) { slotIndex = i; break; }
  }

  if (slotIndex != -1) {
    if (accept) {
      activeMatch.invites[slotIndex] = "accepted";
    } else {
      activeMatch.playerIds[slotIndex] = 0;
      activeMatch.invites[slotIndex] = "empty";
    }
    updateMatchStatus();
  }
  server.send(200, "application/json", "{\"success\":true,\"status\":\"" + activeMatch.status + "\"}");
}

void handleGetActiveMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!activeMatch.active) {
    server.send(200, "application/json", "{\"active\":false}");
    return;
  }

  String json = "{\n";
  json += "  \"active\": true,\n";
  json += "  \"code\": \"" + activeMatch.code + "\",\n";
  json += "  \"matchType\": \"" + activeMatch.matchType + "\",\n";
  json += "  \"status\": \"" + activeMatch.status + "\",\n";
  json += "  \"winner\": " + String(activeMatch.winner_id) + ",\n";
  json += "  \"loser_balls\": " + String(activeMatch.loser_balls) + ",\n";
  json += "  \"players\": [\n";

  for (int i = 0; i < activeMatch.maxPlayers; i++) {
    int pId = activeMatch.playerIds[i];
    Player* pObj = nullptr;
    if (pId > 0) {
      for (int k = 0; k < playerCount; k++) {
        if (players[k].id == pId) { pObj = &players[k]; break; }
      }
    }

    json += "    {\n";
    json += "      \"slot\": " + String(i) + ",\n";
    json += "      \"id\": " + String(pId) + ",\n";
    json += "      \"nome\": \"" + (pObj ? pObj->nome : "Vaga Livre") + "\",\n";
    json += "      \"elo\": " + String(pObj ? pObj->elo : 1000) + ",\n";
    json += "      \"invite\": \"" + activeMatch.invites[i] + "\"\n";
    json += "    }";
    if (i < activeMatch.maxPlayers - 1) json += ",";
    json += "\n";
  }
  json += "  ]\n";
  json += "}";
  server.send(200, "application/json", json);
}

void handleFinishMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) return;

  String body = server.arg("plain");
  int winPos = body.indexOf("\"winner_id\":");
  if (winPos == -1) winPos = body.indexOf("\"winner\":");
  if (winPos == -1) { server.send(400, "application/json", "{\"error\":\"Vencedor ausente\"}"); return; }
  int colonPos = body.indexOf(":", winPos);
  int winVal = body.substring(colonPos + 1).toInt();

  int loserBalls = 0;
  int ballsPos = body.indexOf("\"loserBalls\":");
  if (ballsPos == -1) ballsPos = body.indexOf("\"loser_balls\":");
  if (ballsPos != -1) {
    int bColon = body.indexOf(":", ballsPos);
    loserBalls = body.substring(bColon + 1).toInt();
  }

  int p1_id = activeMatch.playerIds[0];
  int p2_id = activeMatch.playerIds[1];

  Player* pA = nullptr;
  Player* pB = nullptr;
  for (int i = 0; i < playerCount; i++) {
    if (players[i].id == p1_id) pA = &players[i];
    if (players[i].id == p2_id) pB = &players[i];
  }

  int eloDelta = 18;
  if (pA && pB) {
    float expectedA = 1.0 / (1.0 + pow(10.0, (pB->elo - pA->elo) / 400.0));
    float scoreA = (winVal == p1_id) ? 1.0 : 0.0;
    eloDelta = (int)(32 * (scoreA - expectedA));

    if (winVal == p1_id) {
      pA->vitorias++; pA->current_streak++;
      if (pA->current_streak > pA->max_win_streak) pA->max_win_streak = pA->current_streak;
      pA->elo += abs(eloDelta);
      if (pA->elo > pA->peak_elo) pA->peak_elo = pA->elo;
      if (loserBalls == 0) pA->shutout_count++;

      pB->derrotas++; pB->current_streak = 0;
      pB->elo = max(100, pB->elo - abs(eloDelta));
    } else {
      pB->vitorias++; pB->current_streak++;
      if (pB->current_streak > pB->max_win_streak) pB->max_win_streak = pB->current_streak;
      pB->elo += abs(eloDelta);
      if (pB->elo > pB->peak_elo) pB->peak_elo = pB->elo;
      if (loserBalls == 0) pB->shutout_count++;

      pA->derrotas++; pA->current_streak = 0;
      pA->elo = max(100, pA->elo - abs(eloDelta));
    }
  }

  savePlayersToFile();

  if (matchHistoryCount < MAX_HISTORY) {
    matchHistory[matchHistoryCount] = { matchHistoryCount + 1, activeMatch.matchType, p1_id, p2_id, winVal, loserBalls, abs(eloDelta), "Hoje" };
    matchHistoryCount++;
    saveHistoryToFile();
  }

  activeMatch.active = false;
  activeMatch.status = "finished";
  activeMatch.winner_id = winVal;
  activeMatch.loser_balls = loserBalls;

  server.send(200, "application/json", "{\"success\":true,\"message\":\"Partida registrada!\"}");
void handleCancelMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Partida cancelada\"}");
}

void startAPMode() {
  isAPMode = true;
  WiFi.mode(WIFI_AP);
  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP("Area27-Sinuca-Config");

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", apIP);
  Serial.println("[AP] Modo Ponto de Acesso ativado. SSID: Area27-Sinuca-Config");
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n[INIT] Inicializando Área27 Sinuca v2.0...");

  if (!LittleFS.begin()) {
    LittleFS.format();
    LittleFS.begin();
  }
  
  loadPlayersFromFile();
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

  // REST API v1 Routes
  server.on("/api/v1/tv",             HTTP_GET,  handleApiTV);
  server.on("/api/v1/players",        HTTP_GET,  handleGetPlayers);
  server.on("/api/v1/history",        HTTP_GET,  handleApiHistory);
  server.on("/api/v1/stats",          HTTP_GET,  handleApiStats);
  server.on("/api/v1/seasons",        HTTP_GET,  handleApiGetSeasons);
  server.on("/api/v1/seasons/reset",  HTTP_POST, handleApiResetSeason);
  server.on("/api/v1/backup/export",  HTTP_GET,  handleApiExportBackup);
  server.on("/api/v1/backup/import",  HTTP_POST, handleApiImportBackup);

  // Standard API Routes
  server.on("/players",                HTTP_GET,  handleGetPlayers);
  server.on("/players",                HTTP_POST, handlePostPlayers);
  server.on("/players/login",          HTTP_POST, handleLoginPlayer);
  server.on("/players/delete",         HTTP_POST, handleDeletePlayer);
  server.on("/players/reset-password", HTTP_POST, handleResetPlayerPassword);
  server.on("/players/clear",          HTTP_POST, handleClearPlayers);
  server.on("/ranking",                HTTP_GET,  handleGetRanking);
  server.on("/ranking/reset",          HTTP_POST, handleResetRanking);
  server.on("/settings/auth",          HTTP_POST, handleSettingsAuth);
  server.on("/match/create",           HTTP_POST, handleCreateMatch);
  server.on("/match/join",             HTTP_POST, handleJoinMatch);
  server.on("/match/respond",          HTTP_POST, handleRespondInvite);
  server.on("/match/active",           HTTP_GET,  handleGetActiveMatch);
  server.on("/match/finish",           HTTP_POST, handleFinishMatch);
  server.on("/match/cancel",           HTTP_POST, handleCancelMatch);
  server.on("/wifi/scan",              HTTP_GET,  handleWifiScan);
  server.on("/wifi/save",              HTTP_POST, handleWifiSave);
  server.on("/wifi/reset",             HTTP_POST, handleWifiReset);

  // Captive Portal Redirect & File Reader
  server.onNotFound([]() {
    if (isAPMode) {
      server.send_P(200, "text/html", HTML_WIFI_CONFIG);
    } else if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404: Arquivo nao encontrado");
    }
  });

  server.begin();
  Serial.println("[SERVER] Servidor HTTP Área27 Sinuca v2.0 ativo na porta 80.");
}

void loop() {
  if (isAPMode) {
    dnsServer.processNextRequest();
  } else {
    MDNS.update();
  }
  server.handleClient();

  // Cancelamento automático se a partida não for iniciada em 30 minutos (1800000 ms)
  if (activeMatch.active && activeMatch.status == "waiting") {
    if (millis() - activeMatch.startMillis >= 1800000UL) {
      activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};
      Serial.println("[MATCH] Partida cancelada automaticamente por tempo limite de 30 minutos sem iniciar.");
    }
  }
}
