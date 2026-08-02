# 🎱 Área27 Sinuca - ESP8266 Firmware & Interface Web Embarcada

Sistema completo de gerenciamento de partidas, cadastro de jogadores, ranking ELO e controle de sinuca rodando nativamente no microcontrolador **ESP8266** (ESP-01, NodeMCU ou Wemos D1 Mini).

---

## 🌟 Funcionalidades

- 🔑 **Cadastro e Login de Jogadores:**
  - Cadastro obrigatório com **Nome**, **Telefone** e **Senha PIN de 4 dígitos numéricos**.
  - Login seguro via perfil ou número de telefone + PIN.
- 🎱 **Modo Partida Flexível:**
  - **Código Alfanumérico da Sala (4 Caracteres):** Permite que outros jogadores entrem digitando o código gerado ou selecionando perfis da lista.
  - **Convites com Aceite / Recusa:** Jogadores convidados recebem um card em tempo real para **Aceitar** (`✅`) ou **Recusar** (`❌`) o convite antes do início.
  - **Botão de Cancelamento de Partida (`🚫 Cancelar Partida`):** Permite interromper e resetar a sala ativa a qualquer momento.
- 🏆 **3 Modalidades de Jogo:**
  1. **Par ou Ímpar (Individual - 2 Jogadores)**
  2. **Par ou Ímpar (Em Dupla - 4 Jogadores)**
  3. **5 Bolas (3 Jogadores)**
- 📊 **Ranking ELO Persistente:**
  - Cálculo automático de pontuação ELO, vitórias e derrotas após cada partida.
  - Persistência em memória Flash via **LittleFS** (`/players.json`).
- 🔒 **Painel de Configurações Administrativo:**
  - Acesso protegido por **PIN de Administrador (`0000`)**.
  - Recurso para **Trocar de Rede Wi-Fi**, **Zerar Ranking** ou **Excluir Todos os Jogadores**.
- 📶 **Portal Captivo (Modo Ponto de Acesso):**
  - Se não houver Wi-Fi configurado, o ESP8266 inicia a rede `Area27-Sinuca-Config` com portal captivo em `http://192.168.4.1/`.

---

## 📁 Estrutura do Projeto

```text
Área27 Sinuca/
├── Area27_Sinuca/
│   ├── Area27_Sinuca.ino      # Código principal C++ do firmware ESP8266
│   ├── WebPages.h             # Páginas web e scripts embarcados em PROGMEM (Flash)
│   └── data/
│       └── www/              # Arquivos web fonte espelho para LittleFS
│           ├── index.html
│           ├── players.html
│           ├── match.html
│           ├── ranking.html
│           ├── settings.html
│           ├── about.html
│           ├── style.css
│           └── app.js
├── platformio.ini             # Configuração para compilação via PlatformIO
├── README.md                  # Documentação oficial do projeto
└── .gitignore                 # Filtros de repositório Git
```

---

## 🛠️ Tecnologias Utilizadas

- **Microcontrolador:** ESP8266 (ESP-01 / NodeMCU v2)
- **Linguagem C++:** Arduino Framework (`ESP8266WiFi`, `ESP8266WebServer`, `DNSServer`, `LittleFS`)
- **Frontend Web:** HTML5, Vanilla CSS3 (Mobile First Dark Theme), Vanilla JavaScript (REST Fetch API).

---

## 🚀 Como Compilar e Enviar

### Opção 1: Arduino IDE
1. Abra a pasta `Area27_Sinuca` na **Arduino IDE**.
2. Instale as bibliotecas necessárias para ESP8266 (`ESP8266WiFi`, `ESP8266WebServer`, `LittleFS`).
3. Selecione a placa **Generic ESP8266 Module** ou **NodeMCU 1.0**.
4. Defina a velocidade da Serial para `115200`.
5. Clique em **Carregar (Upload)**.

### Opção 2: PlatformIO (VS Code)
1. Abra a pasta raiz no VS Code com a extensão PlatformIO.
2. Selecione o ambiente (`env:esp01_1m` ou `env:nodemcuv2`).
3. Execute o comando **Build** e **Upload**.

---

## ⚙️ Credenciais Padrão do Sistema

- **PIN de Administrador para Configurações:** `0000`
- **SSID do Ponto de Acesso AP (Sem Wi-Fi):** `Area27-Sinuca-Config`
- **IP do Portal Captivo:** `http://192.168.4.1/`

---

## 📄 Licença

Desenvolvido para **Área27 Sinuca**. Todos os direitos reservados.
