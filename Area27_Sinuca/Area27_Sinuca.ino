/*
 * Área27 Sinuca - ESP8266 Firmware & Embedded Web Interface
 * 
 * Hardware: ESP8266 (ESP-01 / NodeMCU / Wemos D1 Mini)
 * Features: Automatic Wi-Fi Captive Portal (AP Mode: Area27-Sinuca-Config)
 * Embedded Files: PROGMEM (Flash Storage) + LittleFS (Data Persistence)
 * Baud Rate: 115200
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
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

// In-Memory Player Structure
struct Player {
  int id;
  String nome;
  String telefone;
  int elo;
  int vitorias;
  int derrotas;
};

#define MAX_PLAYERS 50
Player players[MAX_PLAYERS];
int playerCount = 0;
int nextPlayerId = 1;

// Load Wi-Fi Config from LittleFS (/wifi_config.json)
bool loadWifiConfig() {
  if (!LittleFS.exists("/wifi_config.json")) {
    Serial.println("[WIFI] Nenhum Wi-Fi salvo. Entrando em Modo Configuracao (AP).");
    wifiSSID = "";
    wifiPassword = "";
    return false;
  }

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

  Serial.print("[WIFI] Rede salva no LittleFS: '");
  Serial.print(wifiSSID);
  Serial.println("'");

  return (wifiSSID.length() > 0);
}

// Save Wi-Fi Config to LittleFS (/wifi_config.json)
void saveWifiConfig(String ssid, String password) {
  File file = LittleFS.open("/wifi_config.json", "w");
  if (!file) return;

  file.print("{\n");
  file.print("  \"ssid\": \"" + ssid + "\",\n");
  file.print("  \"password\": \"" + password + "\"\n");
  file.print("}\n");
  file.close();
  Serial.println("[WIFI] Novas configuracoes salvas no LittleFS.");
}

// Save Players state to LittleFS (/players.json)
void savePlayersToFile() {
  File file = LittleFS.open("/players.json", "w");
  if (!file) {
    Serial.println("[STORAGE] ✗ Erro ao abrir /players.json");
    return;
  }

  file.print("[\n");
  for (int i = 0; i < playerCount; i++) {
    file.print("  {\n");
    file.print("    \"id\":" + String(players[i].id) + ",\n");
    file.print("    \"nome\":\"" + players[i].nome + "\",\n");
    file.print("    \"telefone\":\"" + players[i].telefone + "\",\n");
    file.print("    \"elo\":" + String(players[i].elo) + ",\n");
    file.print("    \"vitorias\":" + String(players[i].vitorias) + ",\n");
    file.print("    \"derrotas\":" + String(players[i].derrotas) + "\n");
    file.print("  }");
    if (i < playerCount - 1) file.print(",");
    file.print("\n");
  }
  file.print("]\n");
  file.close();
  Serial.println("[STORAGE] ✓ Dados dos jogadores salvos.");
}

// Load Players state from LittleFS (/players.json)
void loadPlayersFromFile() {
  if (!LittleFS.exists("/players.json")) {
    Serial.println("[STORAGE] Criando /players.json vazio...");
    playerCount = 0;
    nextPlayerId = 1;
    savePlayersToFile();
    return;
  }

  File file = LittleFS.open("/players.json", "r");
  if (!file) return;

  String content = file.readString();
  file.close();

  if (content.indexOf("Jogador 1") != -1 || content.indexOf("Jogador 2") != -1) {
    Serial.println("[STORAGE] Jogadores dummy detectados. Purgando dados antigos...");
    playerCount = 0;
    nextPlayerId = 1;
    savePlayersToFile();
    return;
  }

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

    int eloPos = content.indexOf("\"elo\":", telEnd);
    int eloEnd = content.indexOf(",", eloPos);
    int elo = content.substring(eloPos + 6, eloEnd).toInt();

    int vitPos = content.indexOf("\"vitorias\":", eloEnd);
    int vitEnd = content.indexOf(",", vitPos);
    int vit = content.substring(vitPos + 11, vitEnd).toInt();

    int derPos = content.indexOf("\"derrotas\":", vitEnd);
    int derEnd = content.indexOf("\n", derPos);
    if (derEnd == -1) derEnd = content.indexOf("}", derPos);
    int der = content.substring(derPos + 11, derEnd).toInt();

    players[playerCount] = {id, nome, tel, elo, vit, der};
    if (id >= nextPlayerId) nextPlayerId = id + 1;
    playerCount++;

    searchPos = derEnd;
  }

  Serial.printf("[STORAGE] Carregados %d jogadores.\n", playerCount);
}

// Convert Players Array to JSON String
String getPlayersJSON() {
  String json = "[\n";
  for (int i = 0; i < playerCount; i++) {
    json += "  {\n";
    json += "    \"id\":" + String(players[i].id) + ",\n";
    json += "    \"nome\":\"" + players[i].nome + "\",\n";
    json += "    \"telefone\":\"" + players[i].telefone + "\",\n";
    json += "    \"elo\":" + String(players[i].elo) + ",\n";
    json += "    \"vitorias\":" + String(players[i].vitorias) + ",\n";
    json += "    \"derrotas\":" + String(players[i].derrotas) + "\n";
    json += "  }";
    if (i < playerCount - 1) json += ",";
    json += "\n";
  }
  json += "]";
  return json;
}

// Serve Static Pages directly from Flash (PROGMEM)
bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";

  Serial.print("[HTTP] Serve: ");
  Serial.println(path);

  if (isAPMode) {
    if (path == "/style.css") {
      server.send_P(200, "text/css", CSS_STYLE);
      return true;
    }
    server.send_P(200, "text/html", HTML_WIFI_CONFIG);
    return true;
  }

  if (path == "/index.html") {
    server.send_P(200, "text/html", HTML_INDEX);
    return true;
  }
  if (path == "/players.html") {
    server.send_P(200, "text/html", HTML_PLAYERS);
    return true;
  }
  if (path == "/match.html") {
    server.send_P(200, "text/html", HTML_MATCH);
    return true;
  }
  if (path == "/ranking.html") {
    server.send_P(200, "text/html", HTML_RANKING);
    return true;
  }
  if (path == "/settings.html") {
    server.send_P(200, "text/html", HTML_SETTINGS);
    return true;
  }
  if (path == "/about.html") {
    server.send_P(200, "text/html", HTML_ABOUT);
    return true;
  }
  if (path == "/wifi.html") {
    server.send_P(200, "text/html", HTML_WIFI_CONFIG);
    return true;
  }
  if (path == "/style.css") {
    server.send_P(200, "text/css", CSS_STYLE);
    return true;
  }
  if (path == "/app.js") {
    server.send_P(200, "application/javascript", JS_APP);
    return true;
  }

  return false;
}

// API: GET /wifi/scan
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

// API: POST /wifi/save (Handles both HTML Form POST and JSON POST)
void handleWifiSave() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  
  String newSSID = "";
  String newPass = "";

  if (server.hasArg("ssid")) {
    newSSID = server.arg("ssid");
  }
  if (server.hasArg("password")) {
    newPass = server.arg("password");
  }

  if (newSSID.length() == 0 && server.hasArg("plain")) {
    String body = server.arg("plain");
    int ssidPos = body.indexOf("\"ssid\"");
    if (ssidPos != -1) {
      int colonPos = body.indexOf(":", ssidPos);
      int start = body.indexOf("\"", colonPos) + 1;
      int end = body.indexOf("\"", start);
      newSSID = body.substring(start, end);
    }
    int passPos = body.indexOf("\"password\"");
    if (passPos != -1) {
      int colonPos = body.indexOf(":", passPos);
      int start = body.indexOf("\"", colonPos) + 1;
      int end = body.indexOf("\"", start);
      newPass = body.substring(start, end);
    }
  }

  if (newSSID.length() > 0) {
    Serial.print("[WIFI] Salvando nova rede: '");
    Serial.print(newSSID);
    Serial.println("'");
    saveWifiConfig(newSSID, newPass);

    String htmlResponse = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Wi-Fi Salvo</title>
  <style>
    body { background: #121212; color: #ffffff; font-family: -apple-system, sans-serif; text-align: center; padding: 40px 20px; }
    .card { max-width: 400px; margin: 0 auto; background: #1E1E1E; padding: 30px; border-radius: 12px; border: 1px solid #2A2A2A; box-shadow: 0 4px 12px rgba(0,0,0,0.4); }
    .icon { font-size: 3rem; margin-bottom: 12px; }
    h2 { color: #3B93C1; margin-bottom: 10px; }
    p { color: #BBBBBB; font-size: 0.95rem; line-height: 1.5; margin-bottom: 16px; }
  </style>
</head>
<body>
  <div class="card">
    <div class="icon">✓</div>
    <h2>Configuração Salva!</h2>
    <p>O ESP8266 está reiniciando para se conectar à rede Wi-Fi <strong>)rawliteral" + newSSID + R"rawliteral(</strong>.</p>
    <p>Reconecte o seu celular na sua rede de casa para usar o sistema.</p>
  </div>
</body>
</html>
)rawliteral";

    server.send(200, "text/html", htmlResponse);
    delay(1500);
    ESP.restart();
  } else {
    server.send(400, "text/html", "<h2>Erro: Nome da rede Wi-Fi nao informado.</h2>");
  }
}

// API: POST /wifi/reset
void handleWifiReset() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (LittleFS.exists("/wifi_config.json")) {
    LittleFS.remove("/wifi_config.json");
  }
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Wi-Fi resetado. Reiniciando...\"}");
  delay(1000);
  ESP.restart();
}

// API: GET /players
void handleGetPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", getPlayersJSON());
}

// API: POST /players
void handlePostPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
    return;
  }

  String body = server.arg("plain");

  int nomePos = body.indexOf("\"nome\":\"");
  if (nomePos == -1) nomePos = body.indexOf("\"nome\": \"");
  if (nomePos == -1) {
    server.send(400, "application/json", "{\"error\":\"Nome invalido\"}");
    return;
  }
  int nomeStart = body.indexOf("\"", nomePos + 6) + 1;
  int nomeEnd   = body.indexOf("\"", nomeStart);
  String nome   = body.substring(nomeStart, nomeEnd);

  String telefone = "";
  int telPos = body.indexOf("\"telefone\":\"");
  if (telPos == -1) telPos = body.indexOf("\"telefone\": \"");
  if (telPos != -1) {
    int telStart = body.indexOf("\"", telPos + 10) + 1;
    int telEnd   = body.indexOf("\"", telStart);
    telefone     = body.substring(telStart, telEnd);
  }

  if (playerCount < MAX_PLAYERS) {
    players[playerCount] = {nextPlayerId++, nome, telefone, 1000, 0, 0};
    playerCount++;
    savePlayersToFile();

    server.send(201, "application/json", "{\"success\":true,\"id\":" + String(nextPlayerId - 1) + "}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Limite de jogadores atingido\"}");
  }
}

// API: POST /players/delete
void handleDeletePlayer() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
    return;
  }

  String body = server.arg("plain");
  int idPos = body.indexOf("\"id\":");
  if (idPos == -1) {
    server.send(400, "application/json", "{\"error\":\"ID ausente\"}");
    return;
  }
  int targetId = body.substring(idPos + 5).toInt();

  int targetIndex = -1;
  for (int i = 0; i < playerCount; i++) {
    if (players[i].id == targetId) {
      targetIndex = i;
      break;
    }
  }

  if (targetIndex != -1) {
    for (int i = targetIndex; i < playerCount - 1; i++) {
      players[i] = players[i + 1];
    }
    playerCount--;
    savePlayersToFile();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogador excluido\"}");
  } else {
    server.send(404, "application/json", "{\"error\":\"Jogador nao encontrado\"}");
  }
}

// API: POST /players/clear
void handleClearPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  playerCount = 0;
  nextPlayerId = 1;
  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogadores limpos\"}");
}

// API: POST /ranking/reset
void handleResetRanking() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  for (int i = 0; i < playerCount; i++) {
    players[i].elo = 1000;
    players[i].vitorias = 0;
    players[i].derrotas = 0;
  }
  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Ranking zerado com sucesso\"}");
}

// API: GET /ranking
void handleGetRanking() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", getPlayersJSON());
}

// API: POST /match
void handlePostMatch() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
    return;
  }

  String body = server.arg("plain");

  int pAPos = body.indexOf("\"playerA\":");
  int pAVal = body.substring(pAPos + 10).toInt();

  int pBPos = body.indexOf("\"playerB\":");
  int pBVal = body.substring(pBPos + 10).toInt();

  int winPos = body.indexOf("\"winner\":");
  int winVal = body.substring(winPos + 9).toInt();

  Player* pA = nullptr;
  Player* pB = nullptr;

  for (int i = 0; i < playerCount; i++) {
    if (players[i].id == pAVal) pA = &players[i];
    if (players[i].id == pBVal) pB = &players[i];
  }

  if (!pA || !pB || (winVal != pAVal && winVal != pBVal)) {
    server.send(400, "application/json", "{\"error\":\"Jogadores invalidos\"}");
    return;
  }

  // ELO Rating Calculation (K = 32)
  float expectedA = 1.0 / (1.0 + pow(10.0, (pB->elo - pA->elo) / 400.0));
  float expectedB = 1.0 / (1.0 + pow(10.0, (pA->elo - pB->elo) / 400.0));

  float scoreA = (winVal == pAVal) ? 1.0 : 0.0;
  float scoreB = (winVal == pBVal) ? 1.0 : 0.0;

  pA->elo += (int)(32 * (scoreA - expectedA));
  pB->elo += (int)(32 * (scoreB - expectedB));

  if (winVal == pAVal) {
    pA->vitorias++;
    pB->derrotas++;
  } else {
    pB->vitorias++;
    pA->derrotas++;
  }

  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Partida registrada com sucesso.\"}");
}

void startAPMode() {
  isAPMode = true;
  WiFi.mode(WIFI_AP);
  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP("Area27-Sinuca-Config");

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  Serial.println("\n\n==================================================");
  Serial.println("  📶 MODO PONTO DE ACESSO (AP) ATIVADO!");
  Serial.println("  1. Conecte no Wi-Fi: 'Area27-Sinuca-Config'");
  Serial.println("  2. Acesse no navegador: http://192.168.4.1/");
  Serial.println("==================================================\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n==================================================");
  Serial.println("         ÁREA27 SINUCA - ESP8266 SERVER           ");
  Serial.println("==================================================");

  if (!LittleFS.begin()) {
    Serial.println("[LITTLEFS] ✗ Formatando LittleFS...");
    LittleFS.format();
    LittleFS.begin();
  }
  
  loadPlayersFromFile();
  bool hasSavedWifi = loadWifiConfig();

  if (hasSavedWifi) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    Serial.print("[WIFI] Conectando a '");
    Serial.print(wifiSSID);
    Serial.print("' ");

    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED && timeout < 25) {
      delay(500);
      Serial.print(".");
      timeout++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n\n==================================================");
      Serial.println("  ✓ CONECTADO COM SUCESSO AO WI-FI!");
      Serial.print(  "  ➜ ENDEREÇO IP DO ESP: http://");
      Serial.println(WiFi.localIP());
      Serial.println("==================================================\n");
    } else {
      Serial.println("\n\n[WIFI] ✗ Falha ao conectar no Wi-Fi salvo. Iniciando Modo AP...");
      startAPMode();
    }
  } else {
    Serial.println("[WIFI] Nenhum Wi-Fi configurado. Iniciando Modo AP...");
    startAPMode();
  }

  // Setup REST API Routes
  server.on("/players",       HTTP_GET,  handleGetPlayers);
  server.on("/players",       HTTP_POST, handlePostPlayers);
  server.on("/players/delete",HTTP_POST, handleDeletePlayer);
  server.on("/players/clear", HTTP_POST, handleClearPlayers);
  server.on("/ranking",       HTTP_GET,  handleGetRanking);
  server.on("/ranking/reset", HTTP_POST, handleResetRanking);
  server.on("/match",         HTTP_POST, handlePostMatch);
  server.on("/wifi/scan",     HTTP_GET,  handleWifiScan);
  server.on("/wifi/save",     HTTP_POST, handleWifiSave);
  server.on("/wifi/reset",    HTTP_POST, handleWifiReset);

  // Captive Portal Redirect / Static Web Server
  server.onNotFound([]() {
    if (isAPMode) {
      server.send_P(200, "text/html", HTML_WIFI_CONFIG);
    } else if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404: Arquivo nao encontrado");
    }
  });

  server.begin();
  Serial.println("[SERVER] Servidor HTTP embarcado ativo na porta 80.");
}

unsigned long lastIpPrint = 0;

void loop() {
  if (isAPMode) {
    dnsServer.processNextRequest();
  }

  server.handleClient();

  if (!isAPMode && millis() - lastIpPrint > 20000) {
    lastIpPrint = millis();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("➜ ESP8266 ONLINE | Acesse no navegador: http://");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("[WIFI] Reconectando à rede...");
      WiFi.reconnect();
    }
  }
}
