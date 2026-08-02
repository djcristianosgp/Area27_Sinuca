/*
 * Área27 Sinuca - ESP8266 Firmware & REST API Server
 * 
 * Hardware: ESP8266 (ESP-01 / NodeMCU / Wemos D1 Mini)
 * File System: LittleFS (/data/www/)
 * Baud Rate: 115200
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

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

#define MAX_PLAYERS 30
Player players[MAX_PLAYERS];
int playerCount = 0;
int nextPlayerId = 1;

// Helper: Content-Type MIME determination
String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  if (filename.endsWith(".css"))  return "text/css";
  if (filename.endsWith(".js"))   return "application/javascript";
  if (filename.endsWith(".ico"))  return "image/x-icon";
  if (filename.endsWith(".json")) return "application/json";
  return "text/plain";
}

// Save Players state to LittleFS (/players.json)
void savePlayersToFile() {
  File file = LittleFS.open("/players.json", "w");
  if (!file) {
    Serial.println("Erro ao abrir /players.json para escrita");
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
  Serial.println("Dados dos jogadores salvos no LittleFS.");
}

// Load Players state from LittleFS (/players.json)
void loadPlayersFromFile() {
  if (!LittleFS.exists("/players.json")) {
    Serial.println("Nenhum arquivo /players.json encontrado. Inicializando lista vazia.");
    // Exemplo de dados iniciais (se desejar)
    players[0] = {1, "Jogador 1", "27999999999", 1000, 0, 0};
    players[1] = {2, "Jogador 2", "27888888888", 1000, 0, 0};
    playerCount = 2;
    nextPlayerId = 3;
    savePlayersToFile();
    return;
  }

  File file = LittleFS.open("/players.json", "r");
  if (!file) return;

  String content = file.readString();
  file.close();

  // Simple JSON Parser to avoid external memory-heavy libraries on ESP8266
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

  Serial.printf("Carregados %d jogadores do LittleFS.\n", playerCount);
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

// Serve Static Files from LittleFS (/www/ or /)
bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";

  // Check if file exists in /www/ or root
  String pathWithGz = "/www" + path + ".gz";
  String pathWww    = "/www" + path;

  if (LittleFS.exists(pathWithGz)) {
    File file = LittleFS.open(pathWithGz, "r");
    server.sendHeader("Content-Encoding", "gzip");
    server.sendHeader("Cache-Control", "max-age=86400");
    server.streamFile(file, getContentType(path));
    file.close();
    return true;
  }

  if (LittleFS.exists(pathWww)) {
    File file = LittleFS.open(pathWww, "r");
    server.sendHeader("Cache-Control", "max-age=86400");
    server.streamFile(file, getContentType(path));
    file.close();
    return true;
  }

  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    server.sendHeader("Cache-Control", "max-age=86400");
    server.streamFile(file, getContentType(path));
    file.close();
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
  delay(500);
  Serial.println("\n--- Área27 Sinuca ESP8266 Server ---");

  // Mount LittleFS
  if (!LittleFS.begin()) {
    Serial.println("Erro ao inicializar o LittleFS!");
  } else {
    Serial.println("LittleFS inicializado com sucesso.");
    loadPlayersFromFile();
  }

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(WIFI_SSID);

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 40) {
    delay(500);
    Serial.print(".");
    timeout++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ Conectado com sucesso!");
    Serial.print("Endereço IP no Wi-Fi: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n✗ Falha ao conectar no Wi-Fi. Verifique o SSID e a Senha.");
  }

  // Setup REST API Routes
  server.on("/players", HTTP_GET, handleGetPlayers);
  server.on("/players", HTTP_POST, handlePostPlayers);
  server.on("/ranking", HTTP_GET, handleGetRanking);
  server.on("/match",   HTTP_POST, handlePostMatch);

  // Catch-all: Static Web Server
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404: Arquivo nao encontrado");
    }
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado na porta 80.");
}

void loop() {
  server.handleClient();
}
