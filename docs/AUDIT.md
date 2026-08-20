# Relatório de Auditoria Técnica - Área27 Sinuca

## 1. Visão Geral
O projeto **Área27 Sinuca** é um sistema embarcado monolítico em ESP8266 para gerenciamento de partidas de sinuca, controle de ranking (ELO) e histórico. Atualmente, o projeto concentra toda a sua lógica em um único arquivo `Area27_Sinuca.ino` (~1179 linhas), misturando regras de negócio, persistência de dados (LittleFS), manipulação de rede (Wi-Fi, AP, Captive Portal) e o servidor HTTP embarcado.

## 2. Arquitetura Atual
- **Firmware Monolítico**: Toda a lógica de inicialização, loop, rotas HTTP, persistência, rede e controle de partida está em `Area27_Sinuca.ino`.
- **Servidor Web**: Utiliza `ESP8266WebServer` na porta 80. As páginas web estáticas são servidas via PROGMEM (armazenadas em `WebPages.h`) e há redundância com os arquivos na pasta `data/www/`.
- **Persistência**: Gravação direta via `LittleFS` usando concatenação de `String` para gerar JSON e uso extensivo de `String::indexOf()` / `String::substring()` para desserializar. Os arquivos incluem `/players.json`, `/matches.json`, `/wifi_config.json`.
- **Rede e OTA**: Configuração Wi-Fi via Captive Portal usando `DNSServer`. Suporta OTA puxando de um repositório no GitHub (via `ESP8266httpUpdate`).

## 3. Problemas Encontrados e Riscos

### 3.1. Segurança
- **Senhas em Texto Puro e Default**: As senhas (PINs) dos jogadores são salvas em texto puro (default `"0000"`). Não há hash.
- **PIN Administrativo Hardcoded**: O acesso admin confia na string `"0000"` verificada diretamente em rotas como `/settings/auth`.
- **Falta de Sessões/Tokens**: As requisições (como o login `/players/login`) validam a senha mas não retornam um token (JWT ou Sessão). As chamadas subsequentes confiam que o front-end enviou o ID correto sem validação de autoria real, abrindo portas para manipulação (IDOR).
- **Sem Rate Limit / Proteção Brute Force**: O sistema é totalmente vulnerável a ataques de força bruta no login.
- **Endpoints Administrativos Expostos**: A rota `/ranking/reset` (e outras) zera o ranking sem exigir autorização ou token.

### 3.2. Persistência de Dados
- **Parsing e Escrita de JSON Insegura**: A desserialização baseada em `indexOf` é frágil e propensa a falhas silenciosas ou quebra caso o esquema JSON altere minimamente (ex: espaços em branco).
- **Escrita Não Atômica**: Gravações como `LittleFS.open(..., "w")` sobrescrevem o arquivo diretamente. Uma queda de energia durante a escrita (comum em sistemas embarcados) corromperá irreversivelmente o ranking e histórico.
- **Escritas Síncronas Desnecessárias**: A gravação de jogadores ocorre a cada mudança trivial (ex: criar um jogador).
- **Nenhum Backup/Recuperação**: Se `players.json` corromper, os dados são perdidos.

### 3.3. Arquitetura de Software e Memória
- **Acoplamento Extremo**: Não há distinção entre API (HTTP) e Regras de Negócio. `handleFinishMatch()` lida com cálculos de ELO, manipulação JSON e acesso a sistema de arquivos simultaneamente.
- **Uso Excessivo de `String`**: A concatenação contínua de objetos `String` causa alta fragmentação na Heap (RAM) do ESP8266, podendo resultar em instabilidades ou travamentos (Out-Of-Memory) após tempo de execução prolongado.
- **Código Duplicado**: O front-end existe em `data/www/` mas as rotas HTTP carregam variáveis de `WebPages.h`. Isso gera confusão sobre a "fonte da verdade" do front-end.

## 4. Recomendações e Prioridades

### Fase 1: Segurança (Hardening)
- Refatorar a classe/módulo para incluir um `AuthManager`.
- Hashear os PINs na persistência.
- Implementar verificação baseada em Token/Session ID simples, retornada no Login e requerida em headers/cookies.
- Implementar interface para configuração segura inicial do PIN Admin e proteger endpoints críticos.

### Fase 2: Persistência Robusta
- Substituir parsing manual por `ArduinoJson`.
- Implementar um `StorageManager` com escrita atômica (gravar `.tmp`, deletar original, renomear `.tmp`).
- Adicionar lógica de fallback/recuperação usando `.bak`.

### Fase 3: Modularização do Firmware
- Quebrar `Area27_Sinuca.ino` em classes/modulos (SRP): `MatchManager`, `EloManager`, `PlayerManager`, `WebServer`, `StorageManager`.
- Encapsular os dados do estado do jogo (Máquina de Estados de Partida) para que a lógica não resida nos Handlers do WebServer.

### Fase 4: Frontend
- Adicionar uma camada central no JavaScript `api.js` que intercepte 401s e adicione o Token Auth.
- Corrigir a duplicação entre `data/www` e `WebPages.h` (ex: usar script Python ou Node na build do PIO).

## 5. Dependências e Riscos de Regressão
- A transição para a nova serialização de JSON deve **obrigar uma migração** suave, para garantir que quem já possui um ESP rodando com a versão anterior não perca os dados de `players.json` com o novo formato/parsing.
- Manter o comportamento do Captive Portal, mDNS e OTA intactos durante a refatoração do WebServer.

---
*Relatório finalizado em preparação para a Fase 1.*
