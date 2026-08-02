/*
 * Área27 Sinuca - ESP8266 Firmware & Embedded Web Interface
 * 
 * Hardware: ESP8266 (ESP-01 / NodeMCU / Wemos D1 Mini)
 * Embedded Files: PROGMEM (Flash Storage) + LittleFS (Data Persistence)
 * Baud Rate: 115200
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "WebPages.h"

// Wi-Fi Credentials
const char* WIFI_SSID     = "Area 27 House";
const char* WIFI_PASSWORD = "Dj20Cris@23";

// Web Server on Port 80
ESP8266WebServer server(80);

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
  if (path == "/about.html") {
    server.send_P(200, "text/html", HTML_ABOUT);
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

// API: POST /players/clear (Limpar Lista de Jogadores)
void handleClearPlayers() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  playerCount = 0;
  nextPlayerId = 1;
  savePlayersToFile();
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogadores limpos\"}");
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

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n==================================================");
  Serial.println("         ÁREA27 SINUCA - ESP8266 SERVER           ");
  Serial.println("==================================================");

  // Mount LittleFS for data persistence
  if (!LittleFS.begin()) {
    Serial.println("[LITTLEFS] ✗ Erro ao inicializar LittleFS. Formatando...");
    LittleFS.format();
    LittleFS.begin();
  }
  
  // Clean dummy files if present
  loadPlayersFromFile();

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[WIFI] Conectando a '");
  Serial.print(WIFI_SSID);
  Serial.print("' ");

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 40) {
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
    Serial.println("\n\n[WIFI] ✗ Falha ao conectar. Verifique o SSID e a Senha.");
  }

  // Setup REST API Routes
  server.on("/players",       HTTP_GET,  handleGetPlayers);
  server.on("/players",       HTTP_POST, handlePostPlayers);
  server.on("/players/clear", HTTP_POST, handleClearPlayers);
  server.on("/ranking",       HTTP_GET,  handleGetRanking);
  server.on("/match",         HTTP_POST, handlePostMatch);

  // Catch-all: Static Embedded Web Server
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404: Arquivo nao encontrado");
    }
  });

  server.begin();
  Serial.println("[SERVER] Servidor HTTP embarcado ativo na porta 80.");
}

unsigned long lastIpPrint = 0;

void loop() {
  server.handleClient();

  if (millis() - lastIpPrint > 20000) {
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
