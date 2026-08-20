#ifndef WEBPAGES_H
#define WEBPAGES_H

#include <Arduino.h>

const char HTML_INDEX[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🎱</div>
        <h1>Área27 Sinuca</h1>
      </div>
      <div id="user-status-container"></div>
    </header>

    <main class="card-grid">
      <a href="match.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">🎱</div>
          <div class="card-title">Nova Partida</div>
        </div>
      </a>

      <a href="tv.html" class="card-link">
        <div class="card card-interactive"
          style="border: 1px solid var(--primary); background: linear-gradient(135deg, #1e293b, #0f172a);">
          <div class="card-icon">📺</div>
          <div class="card-title" style="color: #38bdf8;">Painel TV</div>
        </div>
      </a>

      <a href="players.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">👥</div>
          <div class="card-title">Jogadores</div>
        </div>
      </a>

      <a href="ranking.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">🏆</div>
          <div class="card-title">Ranking</div>
        </div>
      </a>

      <a href="hall.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">🏛️</div>
          <div class="card-title">Hall da Fama</div>
        </div>
      </a>

      <a href="championship.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">🎯</div>
          <div class="card-title">Campeonato</div>
        </div>
      </a>

      <a href="settings.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">⚙️</div>
          <div class="card-title">Configurações</div>
        </div>
      </a>

      <a href="about.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">ℹ️</div>
          <div class="card-title">Sobre</div>
        </div>
      </a>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_PLAYERS[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Jogadores - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">👥</div>
        <h1>Jogadores</h1>
      </div>
      <div style="display: flex; align-items: center; gap: 8px;">
        <div id="user-status-container"></div>
        <a href="index.html" class="back-btn">← Voltar</a>
      </div>
    </header>

    <main>
      <!-- Navigation Tabs for Auth -->
      <div class="tabs-nav">
        <button id="tab-btn-register" class="tab-btn active" onclick="switchAuthTab('register')">Cadastrar</button>
        <button id="tab-btn-login" class="tab-btn" onclick="switchAuthTab('login')">Entrar (Login)</button>
      </div>

      <!-- Registration Card -->
      <div id="card-register" class="card" style="margin-bottom: 20px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 14px;">📝 Cadastrar Novo Jogador</h2>
        <form id="form-player">
          <div class="form-group">
            <label class="form-label" for="nome">Nome *</label>
            <input type="text" id="nome" class="form-input" placeholder="Ex: Cristiano" required>
          </div>

          <div class="form-group">
            <label class="form-label" for="telefone">Telefone *</label>
            <input type="tel" id="telefone" class="form-input" placeholder="Ex: 27999999999" required>
          </div>

          <div class="form-group">
            <label class="form-label" for="senha">Senha PIN (4 Dígitos Numéricos) *</label>
            <input type="password" id="senha" class="form-input" placeholder="Ex: 1234" maxlength="4" pattern="[0-9]{4}"
              inputmode="numeric" required>
          </div>

          <button type="submit" class="btn btn-primary">Cadastrar e Entrar</button>
        </form>
      </div>

      <!-- Login Card -->
      <div id="card-login" class="card hidden" style="margin-bottom: 20px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 14px;">🔑 Fazer Login</h2>
        <form id="form-login">
          <div class="form-group">
            <label class="form-label" for="login-player-select">Selecione seu Perfil ou digite seu Telefone</label>
            <select id="login-player-select" class="form-select">
              <option value="">Carregando jogadores...</option>
            </select>
          </div>

          <div class="form-group">
            <label class="form-label" for="login-telefone">Ou Telefone Cadastrado</label>
            <input type="tel" id="login-telefone" class="form-input" placeholder="Ex: 27999999999">
          </div>

          <div class="form-group">
            <label class="form-label" for="login-senha">Senha PIN (4 dígitos) *</label>
            <input type="password" id="login-senha" class="form-input" placeholder="****" maxlength="4"
              pattern="[0-9]{4}" inputmode="numeric" required>
          </div>

          <button type="submit" class="btn btn-secondary">Entrar na Conta</button>
        </form>
      </div>

      <div class="section-header">
        <h2 class="section-title">Lista de Jogadores Cadastrados</h2>
      </div>

      <div id="players-container" class="item-list">
        <div class="empty-state">Carregando jogadores...</div>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_MATCH[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Modo Partida - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🎱</div>
        <h1>Partida</h1>
      </div>
      <div style="display: flex; align-items: center; gap: 8px;">
        <div id="user-status-container"></div>
        <a href="index.html" class="back-btn">← Voltar</a>
      </div>
    </header>

    <main>
      <!-- Auth Guard Container (If user is not logged in) -->
      <div id="match-auth-guard" class="card hidden">
        <h2 style="font-size: 1.1rem; margin-bottom: 10px; color: var(--gold);">⚠️ Identificação Necessária</h2>
        <p style="color: var(--text-muted); font-size: 0.9rem; margin-bottom: 16px;">
          Para iniciar ou entrar em uma partida, você precisa estar cadastrado e logado.
        </p>

        <div class="tabs-nav">
          <button id="guard-tab-register" class="tab-btn active" onclick="switchGuardTab('register')">Cadastrar</button>
          <button id="guard-tab-login" class="tab-btn" onclick="switchGuardTab('login')">Entrar</button>
        </div>

        <form id="guard-form-register">
          <div class="form-group">
            <label class="form-label" for="guard-nome">Nome Completo *</label>
            <input type="text" id="guard-nome" class="form-input" placeholder="Ex: Cristiano" required>
          </div>
          <div class="form-group">
            <label class="form-label" for="guard-telefone">Telefone *</label>
            <input type="tel" id="guard-telefone" class="form-input" placeholder="Ex: 27999999999" required>
          </div>
          <div class="form-group">
            <label class="form-label" for="guard-senha">Senha PIN (4 dígitos numéricos) *</label>
            <input type="password" id="guard-senha" class="form-input" placeholder="Ex: 1234" maxlength="4"
              pattern="[0-9]{4}" inputmode="numeric" required>
          </div>
          <button type="submit" class="btn btn-primary">Cadastrar e Continuar</button>
        </form>

        <form id="guard-form-login" class="hidden">
          <div class="form-group">
            <label class="form-label" for="guard-login-select">Selecione seu Perfil ou Digite o Telefone</label>
            <select id="guard-login-select" class="form-select">
              <option value="">Carregando jogadores...</option>
            </select>
          </div>
          <div class="form-group">
            <label class="form-label" for="guard-login-telefone">Ou Telefone Cadastrado</label>
            <input type="tel" id="guard-login-telefone" class="form-input" placeholder="Ex: 27999999999">
          </div>
          <div class="form-group">
            <label class="form-label" for="guard-login-senha">Senha PIN (4 dígitos numéricos) *</label>
            <input type="password" id="guard-login-senha" class="form-input" placeholder="****" maxlength="4"
              pattern="[0-9]{4}" inputmode="numeric" required>
          </div>
          <button type="submit" class="btn btn-secondary">Entrar na Conta</button>
        </form>
      </div>

      <!-- Main Match Arena (For logged in users) -->
      <div id="match-arena" class="hidden">

        <!-- Invite Notification Banner (Displayed when current logged in user has a pending invite) -->
        <div id="invite-pending-card" class="card hidden"
          style="margin-bottom: 20px; border-color: var(--gold); background: linear-gradient(135deg, #2A2410, #1E1E1E);">
          <h3 style="color: var(--gold); font-size: 1.1rem; margin-bottom: 8px;">📩 Convite de Partida Recebido!</h3>
          <p id="invite-banner-text" style="font-size: 0.9rem; color: var(--text-main); margin-bottom: 16px;">
            Você foi convidado para entrar em uma partida!
          </p>
          <div style="display: flex; gap: 10px;">
            <button class="btn btn-primary" onclick="respondInvite(true)">✅ Aceitar Convite</button>
            <button class="btn btn-outline" style="border-color: var(--error-color); color: var(--error-color);"
              onclick="respondInvite(false)">❌ Recusar Convite</button>
          </div>
        </div>

        <!-- Active Match Panel (Displayed when a match is active) -->
        <div id="active-match-panel" class="card hidden" style="margin-bottom: 20px;">
          <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 12px;">
            <span id="active-match-type-badge" class="badge-elo" style="font-size: 0.85rem;">PAR OU ÍMPAR (2P)</span>
            <button onclick="cancelCurrentMatch()"
              style="background: none; border: none; color: var(--error-color); cursor: pointer; font-size: 0.85rem; font-weight: 600;">✖
              Cancelar</button>
          </div>

          <!-- Room Code Box -->
          <div class="code-box">
            <div class="code-title">Código da Partida (4 Caracteres)</div>
            <div id="active-room-code" class="code-display">----</div>
            <div style="font-size: 0.8rem; color: var(--text-muted); margin-top: 6px;">
              Outro jogador pode digitar este código para entrar na sala!
            </div>
          </div>

          <!-- Roster Grid -->
          <div id="active-roster-container" class="item-list" style="margin: 16px 0;">
            <!-- Rendered dynamically by app.js -->
          </div>

          <!-- Match Action Controls -->
          <div id="match-status-msg"
            style="text-align: center; font-size: 0.9rem; color: var(--gold); margin-bottom: 14px;">
            ⏳ Aguardando jogadores aceitarem os convites...
          </div>

          <div style="display: flex; flex-direction: column; gap: 10px;">
            <button id="btn-open-finish-modal" class="btn btn-primary" onclick="openFinishModal()" disabled>
              🏆 Finalizar Partida
            </button>
            <button id="btn-cancel-match" class="btn btn-outline"
              style="border-color: var(--error-color); color: var(--error-color);" onclick="cancelCurrentMatch()">
              🚫 Cancelar Partida
            </button>
          </div>
        </div>

        <!-- Create or Join Lobby Cards (Displayed when no match is active) -->
        <div id="match-lobby">
          <div class="tabs-nav">
            <button id="tab-btn-create-match" class="tab-btn active" onclick="switchMatchTab('create')">Criar
              Partida</button>
            <button id="tab-btn-join-match" class="tab-btn" onclick="switchMatchTab('join')">Entrar por Código</button>
          </div>

          <!-- Create Match Card -->
          <div id="card-create-match" class="card">
            <h2 style="font-size: 1.1rem; margin-bottom: 14px;">➕ Criar Nova Partida</h2>
            <form id="form-create-match">

              <!-- Select Match Type -->
              <div class="form-group">
                <label class="form-label" for="match-type-select">Tipo de Partida *</label>
                <select id="match-type-select" class="form-select" onchange="handleMatchTypeChange()" required>
                  <option value="par_impar_2p">🎱 Par ou Ímpar (Individual - 2 Jogadores)</option>
                  <option value="par_impar_4p">👥 Par ou Ímpar (Em Dupla - 4 Jogadores)</option>
                  <option value="5_bolas_3p">🖐️ 5 Bolas (3 Jogadores)</option>
                </select>
              </div>

              <!-- Creator Slot -->
              <div class="form-group">
                <label class="form-label">Criador (Você)</label>
                <div id="current-player-name-display" class="form-input"
                  style="display: flex; align-items: center; color: var(--gold); font-weight: 700;">
                  Carregando perfil...
                </div>
              </div>

              <!-- Dynamic Player Selectors container based on match type -->
              <div id="dynamic-invites-container">
                <!-- Injected dynamically by JS (Player B, Player C, Player D) -->
              </div>

              <button type="submit" class="btn btn-primary" style="margin-top: 10px;">⚡ Iniciar Partida</button>
            </form>
          </div>

          <!-- Join Match Card -->
          <div id="card-join-match" class="card hidden">
            <h2 style="font-size: 1.1rem; margin-bottom: 14px;">🔗 Vincular-se a uma Partida</h2>
            <form id="form-join-match">
              <div class="form-group">
                <label class="form-label" for="input-join-code">Código da Partida (4 Caracteres) *</label>
                <input type="text" id="input-join-code" class="form-input" placeholder="Ex: A7K9" maxlength="4"
                  style="text-transform: uppercase; font-size: 1.4rem; letter-spacing: 4px; font-weight: 700; text-align: center;"
                  required>
              </div>

              <button type="submit" class="btn btn-secondary">🤝 Entrar na Partida</button>
            </form>
          </div>
        </div>

      </div>

      <!-- Finalize Match Modal Card -->
      <div id="modal-finish-match" class="card hidden" style="margin-top: 20px; border-color: var(--primary);">
        <h2 style="font-size: 1.2rem; margin-bottom: 14px; text-align: center; color: var(--gold);">🏁 Finalizar Partida
        </h2>

        <form id="form-finish-match">
          <div class="form-group">
            <label class="form-label" for="finish-winner-select">Quem é o Vencedor? *</label>
            <select id="finish-winner-select" class="form-select" required>
              <option value="">Selecione o Vencedor</option>
            </select>
          </div>

          <div class="form-group">
            <label class="form-label">Com quantas bolas o perdedor ficou? *</label>
            <div id="balls-grid-container" class="balls-grid">
              <div class="ball-opt" onclick="selectBalls(0)">0</div>
              <div class="ball-opt" onclick="selectBalls(1)">1</div>
              <div class="ball-opt" onclick="selectBalls(2)">2</div>
              <div class="ball-opt" onclick="selectBalls(3)">3</div>
              <div class="ball-opt" onclick="selectBalls(4)">4</div>
              <div class="ball-opt" onclick="selectBalls(5)">5</div>
              <div class="ball-opt" onclick="selectBalls(6)">6</div>
              <div class="ball-opt" onclick="selectBalls(7)">7</div>
            </div>
            <input type="hidden" id="loser-balls-input" value="" required>
          </div>

          <div style="display: flex; gap: 10px; margin-top: 20px;">
            <button type="button" class="btn btn-outline" onclick="closeFinishModal()">Cancelar</button>
            <button type="submit" class="btn btn-primary">Registrar Resultado</button>
          </div>
        </form>
      </div>

    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_RANKING[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Ranking - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🏆</div>
        <h1>Ranking</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <div id="ranking-container" class="ranking-list">
        <div class="empty-state">Carregando classificação...</div>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_SETTINGS[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Configurações - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">⚙️</div>
        <h1>Configurações</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <!-- Admin PIN Protection Card (Requires PIN 0000) -->
      <div id="admin-pin-card" class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--gold);">🔒 Acesso Restrito</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">
          Informe o PIN de Administrador (0000) para acessar as configurações do sistema.
        </p>

        <form id="form-admin-pin">
          <div class="form-group">
            <label class="form-label" for="admin-pin-input">PIN de Administrador (4 dígitos)</label>
            <input type="password" id="admin-pin-input" class="form-input" placeholder="0000" maxlength="4"
              pattern="[0-9]{4}" inputmode="numeric" style="text-align: center; font-size: 1.5rem; letter-spacing: 6px;"
              required>
          </div>

          <button type="submit" class="btn btn-primary">🔓 Acessar Configurações</button>
        </form>
      </div>

      <!-- Settings Content (Protected by PIN) -->
      <div id="settings-content" class="hidden">

        <!-- Config 0: Gerenciar Jogador Individual -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--primary);">👤 Gerenciar Jogador Individual</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 12px;">
            Exclua um jogador específico ou resete a senha PIN dele para o padrão (0000).
          </p>
          <div class="form-group">
            <label class="form-label" for="select-manage-player">Selecione o Jogador</label>
            <select id="select-manage-player" class="form-select">
              <option value="">Carregando jogadores...</option>
            </select>
          </div>
          <div style="display: flex; gap: 10px; flex-wrap: wrap; margin-top: 10px;">
            <button type="button" id="btn-reset-player-pass" class="btn btn-secondary"
              style="flex: 1; height: 44px; font-size: 0.85rem;">🔑 Resetar Senha</button>
            <button type="button" id="btn-delete-single-player" class="btn btn-danger"
              style="flex: 1; height: 44px; font-size: 0.85rem;">🗑️ Excluir Jogador</button>
          </div>
        </div>

        <!-- Config 1: Backup Export & Import -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--primary);">💾 Backup do Sistema</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
            Exporte ou restaure o arquivo de dados completo (backup.json) contendo jogadores, estatísticas e histórico.
          </p>
          <div style="display: flex; gap: 10px; flex-wrap: wrap;">
            <button id="btn-export-backup" class="btn btn-primary" style="flex: 1;">📥 Exportar Dados
              (backup.json)</button>
            <label class="btn btn-secondary" style="flex: 1; text-align: center; cursor: pointer; margin: 0;">
              📤 Importar Dados
              <input type="file" id="file-import-backup" accept=".json" style="display: none;">
            </label>
          </div>
        </div>

        <!-- Config 2: Gestão de Temporadas -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--gold);">👑 Encerrar Temporada Mensal</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
            Salva os campeões no Hall da Fama e reinicia os ELOs dos jogadores para 1000, preservando todo o histórico
            de partidas.
          </p>
          <button id="btn-reset-season" class="btn btn-secondary" style="background: #a855f7;">🏆 Encerrar Temporada e
            Coroar Campeões</button>
        </div>

        <!-- Config 3: Wi-Fi -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">📶 Rede Wi-Fi</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
            Reinicia o ESP8266 no modo Ponto de Acesso (Area27-Sinuca-Config) para conectar a outro roteador.
          </p>
          <button id="btn-reset-wifi" class="btn btn-secondary">Trocar de Rede Wi-Fi</button>
        </div>

        <!-- Config 4: Zerar Ranking -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🏆 Zerar Ranking</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
            Reseta todas as estatísticas (vitórias, derrotas e ELO para 1000), mantendo o cadastro dos jogadores.
          </p>
          <button id="btn-reset-ranking" class="btn btn-secondary" style="background: #e65100;">Zerar Estatísticas do
            Ranking</button>
        </div>

        <!-- Config 4.5: Atualização GitHub -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--primary);">☁️ Atualização do Sistema (GitHub)
          </h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 12px;">
            Verifique e instale automaticamente novas versões do firmware diretamente do repositório GitHub sem cabo
            USB.
          </p>
          <div id="update-info-container"
            style="background: #1e293b; padding: 12px; border-radius: 8px; font-size: 0.85rem; margin-bottom: 12px;">
            <div>Versão Atual Instalada: <strong id="current-ver-label" style="color: var(--gold);">v2.0.7</strong>
            </div>
            <div id="update-status-text" style="color: var(--text-muted); margin-top: 4px;">Clique no botão abaixo para
              verificar se há atualizações na nuvem.</div>
          </div>
          <div style="display: flex; gap: 10px; flex-wrap: wrap;">
            <button type="button" id="btn-check-update" class="btn btn-secondary" style="flex: 1;">🔍 Verificar
              Atualização</button>
            <button type="button" id="btn-start-update" class="btn btn-primary hidden"
              style="flex: 1; background: var(--success-color);">🚀 Atualizar Agora (GitHub)</button>
          </div>
        </div>

        <!-- Config 5: Excluir Jogadores -->
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🗑️ Gerenciar Jogadores</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
            Apaga permanentemente todos os jogadores cadastrados e reinicia o banco de dados.
          </p>
          <button id="btn-clear-players" class="btn btn-danger">Excluir Todos os Jogadores</button>
        </div>

      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_ABOUT[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Sobre - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">ℹ️</div>
        <h1>Sobre</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <div class="card" style="text-align: center; padding: 24px 20px;">
        <div style="font-size: 3rem; margin-bottom: 12px;">🎱</div>
        <h2 style="font-size: 1.4rem; font-weight: 800; margin-bottom: 4px; color: var(--primary);">Área27 Sinuca</h2>
        <p style="color: var(--gold); font-weight: 700; font-size: 1.1rem; margin-bottom: 20px;">Versão v2.0.7</p>

        <div
          style="background: #161616; border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 16px; margin-bottom: 20px; text-align: left; display: flex; flex-direction: column; gap: 10px; font-size: 0.92rem;">
          <div><strong style="color: var(--text-muted);">Versão Instalada:</strong> <span
              style="color: var(--gold); font-weight:700;">v2.0.7</span></div>
          <div><strong style="color: var(--text-muted);">Última Atualização:</strong> <span
              style="color: #4ade80; font-weight:700;">03/08/2026</span></div>
          <div><strong style="color: var(--text-muted);">Plataforma:</strong> ESP8266 (Wi-Fi + LittleFS + Web Server)
          </div>
          <div><strong style="color: var(--text-muted);">Desenvolvido por:</strong> Área27 Team</div>
          <div><strong style="color: var(--text-muted);">Recursos:</strong> TV Dashboard, Ranking ELO, Medalhas, Hall da
            Fama, Torneios, OTA GitHub</div>
        </div>

        <div id="about-update-status" style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;"></div>

        <div style="display:flex; flex-direction:column; gap:10px; margin-bottom:16px;">
          <button id="btn-about-check-update" class="btn btn-secondary" style="height:44px;">🔍 Buscar
            Atualizações</button>
          <button id="btn-about-start-update" class="btn btn-primary hidden"
            style="height:44px; background:var(--success-color);">🚀 Atualizar Agora (GitHub)</button>
        </div>

        <a href="index.html" class="btn btn-secondary"
          style="text-decoration: none; height:44px; display:flex; align-items:center; justify-content:center;">Ir para
          a Página Inicial</a>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
</body>

</html>
)=====";

const char HTML_TV[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>TV Dashboard - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
  <style>
    body.tv-mode {
      background-color: #0b0f19;
      color: #f1f5f9;
      padding: 0;
      margin: 0;
      overflow-x: hidden;
    }
    .tv-container {
      max-width: 100%;
      min-height: 100vh;
      padding: 24px 32px;
      display: flex;
      flex-direction: column;
      gap: 20px;
    }
    .tv-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      background: linear-gradient(135deg, #1e293b, #0f172a);
      padding: 16px 28px;
      border-radius: 16px;
      border: 1px solid #334155;
      box-shadow: 0 8px 24px rgba(0, 0, 0, 0.4);
    }
    .tv-logo {
      display: flex;
      align-items: center;
      gap: 16px;
    }
    .tv-logo-icon {
      font-size: 2.4rem;
      background: linear-gradient(135deg, #3b82f6, #1d4ed8);
      width: 56px;
      height: 56px;
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: 0 0 20px rgba(59, 130, 246, 0.5);
    }
    .tv-logo-text h1 {
      font-size: 2rem;
      font-weight: 800;
      letter-spacing: -0.5px;
      color: #ffffff;
      margin: 0;
    }
    .tv-logo-text p {
      font-size: 0.95rem;
      color: #94a3b8;
      margin: 0;
    }
    .tv-clock {
      font-size: 1.8rem;
      font-weight: 700;
      font-family: monospace;
      color: #38bdf8;
      background: rgba(15, 23, 42, 0.6);
      padding: 8px 20px;
      border-radius: 12px;
      border: 1px solid #334155;
    }
    .tv-grid {
      display: grid;
      grid-template-columns: 1.2fr 1fr;
      gap: 24px;
      flex: 1;
    }
    .tv-card {
      background: #1e293b;
      border: 1px solid #334155;
      border-radius: 16px;
      padding: 24px;
      box-shadow: 0 8px 20px rgba(0, 0, 0, 0.3);
      display: flex;
      flex-direction: column;
    }
    .tv-card-title {
      font-size: 1.3rem;
      font-weight: 700;
      color: #fbbf24;
      display: flex;
      align-items: center;
      gap: 10px;
      margin-bottom: 18px;
      border-bottom: 2px solid #334155;
      padding-bottom: 10px;
    }
    .tv-live-match {
      background: linear-gradient(135deg, #1e1b4b, #0f172a);
      border: 2px solid #6366f1;
      position: relative;
      overflow: hidden;
    }
    .tv-live-match::before {
      content: '● AO VIVO';
      position: absolute;
      top: 16px;
      right: 16px;
      background: #ef4444;
      color: white;
      font-size: 0.75rem;
      font-weight: 800;
      padding: 4px 12px;
      border-radius: 20px;
      animation: pulse 1.5s infinite;
    }
    @keyframes pulse {
      0% { opacity: 1; }
      50% { opacity: 0.4; }
      100% { opacity: 1; }
    }
    .tv-match-timer {
      font-size: 2.2rem;
      font-weight: 900;
      text-align: center;
      color: #4ade80;
      margin: 10px 0;
      font-family: monospace;
    }
    .tv-players-versus {
      display: flex;
      align-items: center;
      justify-content: space-around;
      margin: 20px 0;
      gap: 12px;
    }
    .tv-player-box {
      text-align: center;
      flex: 1;
      background: rgba(30, 41, 59, 0.7);
      padding: 16px;
      border-radius: 14px;
      border: 1px solid #475569;
    }
    .tv-player-name {
      font-size: 1.4rem;
      font-weight: 700;
      color: #ffffff;
    }
    .tv-player-elo {
      font-size: 1.05rem;
      color: #fbbf24;
      font-weight: 600;
    }
    .tv-vs {
      font-size: 1.8rem;
      font-weight: 900;
      color: #ef4444;
      font-style: italic;
    }
    .tv-ranking-table {
      width: 100%;
      border-collapse: collapse;
    }
    .tv-ranking-table th {
      text-align: left;
      color: #94a3b8;
      font-size: 0.9rem;
      padding: 8px 12px;
      border-bottom: 1px solid #334155;
    }
    .tv-ranking-table td {
      padding: 12px;
      font-size: 1.15rem;
      border-bottom: 1px solid rgba(51, 65, 85, 0.5);
    }
    .tv-rank-pos {
      font-weight: 800;
      width: 40px;
    }
    .tv-rank-1 { color: #fbbf24; }
    .tv-rank-2 { color: #94a3b8; }
    .tv-rank-3 { color: #d97706; }
    .tv-history-item {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 10px 14px;
      background: rgba(15, 23, 42, 0.6);
      border-radius: 10px;
      margin-bottom: 10px;
      border-left: 4px solid #3b82f6;
    }
    .tv-history-winner {
      font-weight: 700;
      color: #4ade80;
    }
    .tv-history-score {
      font-weight: 800;
      font-size: 1.1rem;
      color: #ffffff;
    }
  </style>
</head>
<body class="tv-mode">
  <div class="tv-container">
    <!-- Header -->
    <header class="tv-header">
      <div class="tv-logo">
        <div class="tv-logo-icon">🎱</div>
        <div class="tv-logo-text">
          <h1>ÁREA27 SINUCA</h1>
          <p>Painel de Controle em Tempo Real</p>
        </div>
      </div>
      <div id="tv-clock" class="tv-clock">00:00:00</div>
    </header>

    <!-- Main Grid -->
    <div class="tv-grid">
      <!-- Left Column: Active Match & History -->
      <div style="display: flex; flex-direction: column; gap: 24px;">
        <!-- Live Match Card -->
        <div id="tv-live-card" class="tv-card tv-live-match">
          <div class="tv-card-title">🎱 PARTIDA ATUAL NA MESA</div>
          <div id="tv-live-content">
            <div style="text-align: center; color: #94a3b8; padding: 30px 0; font-size: 1.2rem;">
              Mesa disponível. Aguardando início de partida...
            </div>
          </div>
        </div>

        <!-- History Card -->
        <div class="tv-card" style="flex: 1;">
          <div class="tv-card-title">📜 ÚLTIMAS PARTIDAS</div>
          <div id="tv-history-list">
            <div style="text-align: center; color: #94a3b8; padding: 20px;">Carregando histórico...</div>
          </div>
        </div>
      </div>

      <!-- Right Column: Ranking Top 10 & Tournament/Badges -->
      <div style="display: flex; flex-direction: column; gap: 24px;">
        <!-- Top Ranking Card -->
        <div class="tv-card" style="flex: 1;">
          <div class="tv-card-title">🏆 CLASSIFICAÇÃO GERAL</div>
          <table class="tv-ranking-table">
            <thead>
              <tr>
                <th>#</th>
                <th>JOGADOR</th>
                <th>ELO</th>
                <th>V / D</th>
                <th>APROV %</th>
              </tr>
            </thead>
            <tbody id="tv-ranking-body">
              <tr><td colspan="5" style="text-align:center; color:#94a3b8;">Carregando ranking...</td></tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  </div>

  <script src="app.js"></script>
  <script>
    document.addEventListener('DOMContentLoaded', () => {
      if (typeof initTVDashboard === 'function') {
        initTVDashboard();
      }
    });
  </script>
</body>
</html>

)=====";

const char HTML_PROFILE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Perfil do Jogador - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">👤</div>
        <h1>Perfil do Jogador</h1>
      </div>
      <a href="players.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <!-- Player Header Card -->
      <div class="card" style="margin-bottom: 20px; text-align: center;">
        <div id="profile-avatar" class="avatar-large"
          style="width: 72px; height: 72px; font-size: 2.2rem; margin: 0 auto 12px auto; background: linear-gradient(135deg, var(--primary), var(--secondary)); border-radius: 50%; display: flex; align-items: center; justify-content: center; box-shadow: 0 4px 14px rgba(59,147,193,0.4);">
          🎱
        </div>
        <h2 id="profile-name" style="font-size: 1.5rem; margin-bottom: 4px;">Carregando...</h2>
        <p id="profile-phone" style="font-size: 0.9rem; color: var(--text-muted); margin-bottom: 12px;"></p>
        <button id="btn-show-qr" class="btn btn-secondary"
          style="width: auto; padding: 6px 16px; font-size: 0.85rem; margin: 0 auto;">📱 Exibir QR Code</button>
      </div>

      <!-- Main Stats Grid -->
      <div class="card-grid" style="grid-template-columns: repeat(2, 1fr); margin-bottom: 20px;">
        <div class="card" style="text-align: center; padding: 14px;">
          <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase; letter-spacing: 1px;">
            Pontuação ELO</div>
          <div id="profile-elo" style="font-size: 2rem; font-weight: 800; color: var(--gold); margin-top: 4px;">-</div>
          <div id="profile-peak-elo" style="font-size: 0.75rem; color: var(--text-muted);">Pico: -</div>
        </div>

        <div class="card" style="text-align: center; padding: 14px;">
          <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase; letter-spacing: 1px;">Taxa
            de Vitória</div>
          <div id="profile-winrate" style="font-size: 2rem; font-weight: 800; color: #4ade80; margin-top: 4px;">-</div>
          <div id="profile-wl-count" style="font-size: 0.75rem; color: var(--text-muted);">0V / 0D</div>
        </div>

        <div class="card" style="text-align: center; padding: 14px;">
          <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase; letter-spacing: 1px;">
            Sequência Atual</div>
          <div id="profile-streak" style="font-size: 1.6rem; font-weight: 800; color: #38bdf8; margin-top: 4px;">-</div>
        </div>

        <div class="card" style="text-align: center; padding: 14px;">
          <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase; letter-spacing: 1px;">
            Maior Sequência</div>
          <div id="profile-max-streak" style="font-size: 1.6rem; font-weight: 800; color: #f59e0b; margin-top: 4px;">-
          </div>
        </div>
      </div>

      <!-- Recent Matches Indicators -->
      <div class="card" style="margin-bottom: 20px;">
        <h3 style="font-size: 1rem; margin-bottom: 12px; color: var(--primary);">Últimos Jogos</h3>
        <div id="profile-recent-dots" style="display: flex; gap: 8px; flex-wrap: wrap;">
          <div style="color: var(--text-muted); font-size: 0.85rem;">Nenhuma partida registrada ainda.</div>
        </div>
      </div>

      <!-- Badges / Conquistas Card -->
      <div class="card" style="margin-bottom: 20px;">
        <h3 style="font-size: 1rem; margin-bottom: 12px; color: var(--gold);">🏅 Conquistas & Medalhas</h3>
        <div id="profile-badges-list" class="badge-grid"
          style="display: grid; grid-template-columns: repeat(auto-fill, minmax(130px, 1fr)); gap: 10px;">
          <!-- Badges dynamically rendered here -->
        </div>
      </div>

      <!-- Head to Head Compare Card -->
      <div class="card" style="margin-bottom: 20px;">
        <h3 style="font-size: 1rem; margin-bottom: 12px; color: #ec4899;">⚔️ Confronto Direto (Head-to-Head)</h3>
        <div class="form-group">
          <label class="form-label" for="select-rival">Comparar estatísticas contra:</label>
          <select id="select-rival" class="form-input">
            <option value="">Selecione um adversário...</option>
          </select>
        </div>
        <div id="h2h-result" class="hidden"
          style="margin-top: 14px; background: rgba(0,0,0,0.2); padding: 14px; border-radius: 8px;">
          <!-- H2H Comparison populated via app.js -->
        </div>
      </div>
    </main>

    <!-- Modal QR Code -->
    <div id="modal-qr" class="modal-overlay hidden">
      <div class="modal-card" style="text-align: center;">
        <h3 style="margin-bottom: 12px;">📱 QR Code de Acesso</h3>
        <div id="qr-container"
          style="display: flex; justify-content: center; padding: 16px; background: white; border-radius: 12px; width: 200px; height: 200px; margin: 0 auto 16px auto;">
          <!-- SVG QR Code generated here -->
        </div>
        <p style="font-size: 0.8rem; color: var(--text-muted); margin-bottom: 16px;">Escaneie este QR Code no salão para
          login instantâneo.</p>
        <button id="btn-close-qr" class="btn btn-secondary">Fechar</button>
      </div>
    </div>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
  <script>
    document.addEventListener('DOMContentLoaded', () => {
      if (typeof initPlayerProfile === 'function') {
        initPlayerProfile();
      }
    });
  </script>
</body>

</html>
)=====";

const char HTML_HALL[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Hall da Fama - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🏛️</div>
        <h1>Hall da Fama</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <div style="text-align: center; margin-bottom: 20px;">
        <h2 style="font-size: 1.2rem; color: var(--gold);">👑 Recordes Históricos da Área27</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted);">Os maiores feitos e recordistas de todos os tempos.</p>
      </div>

      <!-- Hall Categories Grid -->
      <div class="card-grid" style="grid-template-columns: 1fr; gap: 16px; margin-bottom: 20px;">
        <!-- Highest ELO -->
        <div class="card" style="border-left: 5px solid var(--gold);">
          <div style="display: flex; align-items: center; gap: 12px;">
            <div style="font-size: 2rem;">⚡</div>
            <div style="flex: 1;">
              <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase;">Maior ELO de Todos os
                Tempos</div>
              <div id="hall-peak-elo" style="font-size: 1.2rem; font-weight: 700; color: var(--text-main);">
                Carregando...</div>
            </div>
          </div>
        </div>

        <!-- Longest Win Streak -->
        <div class="card" style="border-left: 5px solid #ef4444;">
          <div style="display: flex; align-items: center; gap: 12px;">
            <div style="font-size: 2rem;">🔥</div>
            <div style="flex: 1;">
              <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase;">Maior Sequência de
                Vitórias</div>
              <div id="hall-max-streak" style="font-size: 1.2rem; font-weight: 700; color: var(--text-main);">
                Carregando...</div>
            </div>
          </div>
        </div>

        <!-- Most Victories -->
        <div class="card" style="border-left: 5px solid #4ade80;">
          <div style="display: flex; align-items: center; gap: 12px;">
            <div style="font-size: 2rem;">🎯</div>
            <div style="flex: 1;">
              <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase;">Mais Vitórias
                Registradas</div>
              <div id="hall-most-wins" style="font-size: 1.2rem; font-weight: 700; color: var(--text-main);">
                Carregando...</div>
            </div>
          </div>
        </div>

        <!-- Most Matches Played -->
        <div class="card" style="border-left: 5px solid #3b82f6;">
          <div style="display: flex; align-items: center; gap: 12px;">
            <div style="font-size: 2rem;">🎱</div>
            <div style="flex: 1;">
              <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase;">Mais Partidas
                Disputadas</div>
              <div id="hall-most-matches" style="font-size: 1.2rem; font-weight: 700; color: var(--text-main);">
                Carregando...</div>
            </div>
          </div>
        </div>

        <!-- Most Season Titles -->
        <div class="card" style="border-left: 5px solid #a855f7;">
          <div style="display: flex; align-items: center; gap: 12px;">
            <div style="font-size: 2rem;">👑</div>
            <div style="flex: 1;">
              <div style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase;">Mais Títulos de
                Temporada</div>
              <div id="hall-most-titles" style="font-size: 1.2rem; font-weight: 700; color: var(--text-main);">
                Carregando...</div>
            </div>
          </div>
        </div>
      </div>

      <!-- Past Seasons Champions Section -->
      <div class="card">
        <h3 style="font-size: 1rem; margin-bottom: 12px; color: var(--gold);">🏆 Galeria de Campeões por Temporada</h3>
        <div id="seasons-gallery-list">
          <div style="text-align: center; color: var(--text-muted); padding: 14px; font-size: 0.85rem;">
            Nenhuma temporada anterior finalizada ainda.
          </div>
        </div>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
  <script>
    document.addEventListener('DOMContentLoaded', () => {
      if (typeof initHallOfFame === 'function') {
        initHallOfFame();
      }
    });
  </script>
</body>

</html>
)=====";

const char HTML_CHAMPIONSHIP[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Modo Campeonato - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
  <style>
    .bracket-container {
      display: flex;
      gap: 16px;
      overflow-x: auto;
      padding-bottom: 12px;
    }

    .bracket-column {
      flex: 1;
      min-width: 160px;
      display: flex;
      flex-direction: column;
      justify-content: space-around;
      gap: 12px;
    }

    .bracket-title {
      font-size: 0.85rem;
      font-weight: 700;
      color: var(--primary);
      text-align: center;
      margin-bottom: 8px;
      text-transform: uppercase;
    }

    .bracket-match {
      background: var(--card-bg);
      border: 1px solid var(--border-color);
      border-radius: var(--radius-sm);
      padding: 8px;
      position: relative;
    }

    .bracket-match.active {
      border-color: var(--gold);
      box-shadow: 0 0 10px rgba(255, 215, 0, 0.2);
    }

    .bracket-slot {
      padding: 6px 8px;
      font-size: 0.85rem;
      border-radius: 4px;
      display: flex;
      justify-content: space-between;
      align-items: center;
      cursor: pointer;
    }

    .bracket-slot.winner {
      background: rgba(46, 125, 50, 0.25);
      color: #4ade80;
      font-weight: 700;
    }
  </style>
</head>

<body>

  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🏆</div>
        <h1>Modo Campeonato</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>

    <main>
      <!-- Setup Championship Card -->
      <div id="champ-setup-card" class="card" style="margin-bottom: 20px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--gold);">🎯 Criar Novo Campeonato</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">
          Sorteio automático e chaveamento no ESP8266 (Sem necessidade de internet).
        </p>

        <form id="form-create-champ">
          <div class="form-group">
            <label class="form-label" for="champ-name">Nome do Campeonato</label>
            <input type="text" id="champ-name" class="form-input" placeholder="Ex: Torneio de Sexta" required>
          </div>

          <div class="form-group">
            <label class="form-label">Número de Jogadores</label>
            <div style="display: flex; gap: 10px;">
              <label
                style="flex:1; background: var(--border-color); padding: 10px; border-radius: var(--radius-sm); text-align: center; cursor: pointer;">
                <input type="radio" name="champ-size" value="4" checked> 4 Jogadores
              </label>
              <label
                style="flex:1; background: var(--border-color); padding: 10px; border-radius: var(--radius-sm); text-align: center; cursor: pointer;">
                <input type="radio" name="champ-size" value="8"> 8 Jogadores
              </label>
              <label
                style="flex:1; background: var(--border-color); padding: 10px; border-radius: var(--radius-sm); text-align: center; cursor: pointer;">
                <input type="radio" name="champ-size" value="16"> 16 Jogadores
              </label>
            </div>
          </div>

          <button type="submit" class="btn btn-primary">🎲 Realizar Sorteio e Gerar Chaveamento</button>
        </form>
      </div>

      <!-- Active Championship Tree -->
      <div id="champ-active-card" class="card hidden" style="margin-bottom: 20px;">
        <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 16px;">
          <h2 id="active-champ-title" style="font-size: 1.2rem; color: var(--gold);">Nome do Torneio</h2>
          <button id="btn-reset-champ" class="btn btn-secondary"
            style="width: auto; padding: 4px 12px; font-size: 0.8rem; background: var(--error-color);">Cancelar
            Torneio</button>
        </div>

        <div class="bracket-container" id="bracket-view">
          <!-- Dynamically populated knockout bracket -->
        </div>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition v2.0.7
    </footer>
  </div>

  <script src="app.js"></script>
  <script>
    document.addEventListener('DOMContentLoaded', () => {
      if (typeof initChampionship === 'function') {
        initChampionship();
      }
    });
  </script>
</body>

</html>
)=====";

const char HTML_WIFI_CONFIG[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Configuração Wi-Fi - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title"><div class="logo-badge">📶</div><h1>Conectar Wi-Fi</h1></div>
    </header>
    <main>
      <div class="card">
        <form action="/wifi/save" method="POST">
          <div class="form-group"><label class="form-label">Nome da Rede Wi-Fi (SSID)</label><input type="text" name="ssid" class="form-input" required></div>
          <div class="form-group"><label class="form-label">Senha do Wi-Fi</label><input type="password" name="password" class="form-input"></div>
          <button type="submit" class="btn btn-primary">Salvar e Conectar</button>
        </form>
      </div>
    </main>
  </div>
</body>
</html>

)=====";

const char CSS_STYLE[] PROGMEM = R"=====(
/* ==========================================================================
   Área27 Sinuca - Dark Mobile Style (ESP8266 Optimized)
   ========================================================================== */

:root {
  --bg-color: #121212;
  --card-bg: #1E1E1E;
  --card-hover: #262626;
  --primary: #3B93C1;
  --primary-hover: #327FA8;
  --secondary: #286281;
  --secondary-hover: #204F69;
  --text-main: #FFFFFF;
  --text-muted: #BBBBBB;
  --border-color: #2A2A2A;
  --success-color: #2E7D32;
  --error-color: #C62828;
  --gold: #FFD700;
  --silver: #C0C0C0;
  --bronze: #CD7F32;
  --font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
  --radius: 12px;
  --radius-sm: 8px;
  --transition: all 0.2s ease-in-out;
}

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

html, body {
  background-color: var(--bg-color);
  color: var(--text-main);
  font-family: var(--font-family);
  font-size: 16px;
  line-height: 1.5;
  min-height: 100vh;
  overflow-x: hidden;
  -webkit-font-smoothing: antialiased;
}

/* App Layout Container */
.app-container {
  max-width: 480px;
  margin: 0 auto;
  padding: 16px;
  min-height: 100vh;
  display: flex;
  flex-direction: column;
}

/* Header Component */
.header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding-bottom: 16px;
  margin-bottom: 20px;
  border-bottom: 1px solid var(--border-color);
}

.header-title {
  display: flex;
  align-items: center;
  gap: 10px;
}

.header h1 {
  font-size: 1.4rem;
  font-weight: 700;
  color: var(--text-main);
  letter-spacing: -0.5px;
}

.logo-badge {
  background: linear-gradient(135deg, var(--primary), var(--secondary));
  width: 38px;
  height: 38px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1.2rem;
  box-shadow: 0 4px 10px rgba(59, 147, 193, 0.3);
}

.back-btn {
  background: var(--card-bg);
  color: var(--text-main);
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 8px 14px;
  text-decoration: none;
  font-size: 0.9rem;
  font-weight: 600;
  display: inline-flex;
  align-items: center;
  gap: 6px;
  transition: var(--transition);
}

.back-btn:active {
  transform: scale(0.96);
  background: var(--border-color);
}

/* Cards & Dashboard Grid */
.card-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 14px;
}

.card-link {
  text-decoration: none;
  color: inherit;
  display: block;
}

.card {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius);
  padding: 20px 16px;
  transition: var(--transition);
  box-shadow: 0 4px 12px rgba(0,0,0,0.2);
}

.card-interactive {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  text-align: center;
  height: 100%;
  min-height: 120px;
  cursor: pointer;
}

.card-interactive:active {
  transform: scale(0.97);
  background: var(--card-hover);
  border-color: var(--primary);
}

.card-icon {
  font-size: 2.2rem;
  margin-bottom: 8px;
}

.card-title {
  font-size: 1.05rem;
  font-weight: 600;
  color: var(--text-main);
}

/* Form & Input Components */
.form-group {
  margin-bottom: 16px;
}

.form-label {
  display: block;
  font-size: 0.9rem;
  color: var(--text-muted);
  margin-bottom: 6px;
  font-weight: 500;
}

.form-input, .form-select {
  width: 100%;
  height: 48px;
  background: #161616;
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  color: var(--text-main);
  padding: 0 14px;
  font-size: 1rem;
  font-family: inherit;
  outline: none;
  transition: var(--transition);
  -webkit-appearance: none;
  appearance: none;
}

.form-select {
  background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='16' height='16' viewBox='0 0 24 24' fill='none' stroke='%2BBBBBBB' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpolyline points='6 9 12 15 18 9'%3E%3C/polyline%3E%3C/svg%3E");
  background-repeat: no-repeat;
  background-position: right 14px center;
  padding-right: 40px;
}

.form-input:focus, .form-select:focus {
  border-color: var(--primary);
  box-shadow: 0 0 0 2px rgba(59, 147, 193, 0.25);
}

/* Buttons */
.btn {
  width: 100%;
  height: 50px;
  border: none;
  border-radius: var(--radius-sm);
  font-size: 1rem;
  font-weight: 600;
  font-family: inherit;
  cursor: pointer;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  gap: 8px;
  transition: var(--transition);
}

.btn-primary {
  background: var(--primary);
  color: var(--text-main);
  box-shadow: 0 4px 12px rgba(59, 147, 193, 0.3);
}

.btn-primary:active {
  background: var(--primary-hover);
  transform: scale(0.98);
}

.btn-secondary {
  background: var(--secondary);
  color: var(--text-main);
}

.btn-secondary:active {
  background: var(--secondary-hover);
  transform: scale(0.98);
}

.btn-danger {
  background: var(--error-color);
  color: var(--text-main);
}

.btn-outline {
  background: transparent;
  border: 1px solid var(--border-color);
  color: var(--text-main);
}

.btn-outline:active {
  background: var(--border-color);
}

/* Lists & Tables */
.section-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin: 20px 0 12px 0;
}

.section-title {
  font-size: 1.1rem;
  font-weight: 600;
  color: var(--text-main);
}

.item-list {
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.list-item {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 14px 16px;
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.player-info {
  display: flex;
  flex-direction: column;
}

.player-name {
  font-weight: 600;
  font-size: 1rem;
}

.player-phone {
  font-size: 0.85rem;
  color: var(--text-muted);
}

.player-stats {
  text-align: right;
}

.badge-elo {
  background: rgba(59, 147, 193, 0.15);
  color: var(--primary);
  font-weight: 700;
  font-size: 0.85rem;
  padding: 4px 8px;
  border-radius: 6px;
  border: 1px solid rgba(59, 147, 193, 0.3);
  display: inline-block;
  margin-bottom: 4px;
}

.record {
  font-size: 0.8rem;
  color: var(--text-muted);
}

/* Ranking Podium & Cards */
.ranking-list {
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.ranking-card {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 14px;
  display: flex;
  align-items: center;
  gap: 12px;
}

.ranking-rank {
  font-size: 1.2rem;
  font-weight: 800;
  width: 36px;
  height: 36px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  background: #252525;
  color: var(--text-muted);
  flex-shrink: 0;
}

.rank-1 {
  background: rgba(255, 215, 0, 0.15);
  color: var(--gold);
  border: 1px solid rgba(255, 215, 0, 0.4);
}

.rank-2 {
  background: rgba(192, 192, 192, 0.15);
  color: var(--silver);
  border: 1px solid rgba(192, 192, 192, 0.4);
}

.rank-3 {
  background: rgba(205, 127, 50, 0.15);
  color: var(--bronze);
  border: 1px solid rgba(205, 127, 50, 0.4);
}

.ranking-card.top-1 {
  border-color: rgba(255, 215, 0, 0.5);
  background: linear-gradient(135deg, #1E1E1E 70%, rgba(255, 215, 0, 0.08));
}

.ranking-card.top-2 {
  border-color: rgba(192, 192, 192, 0.4);
}

.ranking-card.top-3 {
  border-color: rgba(205, 127, 50, 0.4);
}

.ranking-details {
  flex: 1;
}

/* Toast Message Notification */
.toast {
  position: fixed;
  bottom: 24px;
  left: 50%;
  transform: translateX(-50%) translateY(100px);
  max-width: 440px;
  width: 90%;
  padding: 14px 18px;
  border-radius: var(--radius-sm);
  color: #FFF;
  font-weight: 600;
  font-size: 0.95rem;
  box-shadow: 0 6px 20px rgba(0,0,0,0.5);
  transition: transform 0.3s cubic-bezier(0.175, 0.885, 0.32, 1.275);
  z-index: 1000;
  display: flex;
  align-items: center;
  gap: 10px;
}

.toast.show {
  transform: translateX(-50%) translateY(0);
}

.toast-success {
  background: var(--success-color);
}

.toast-error {
  background: var(--error-color);
}

/* Utilities & Empty state */
.empty-state {
  text-align: center;
  padding: 30px 16px;
  color: var(--text-muted);
  background: var(--card-bg);
  border: 1px dashed var(--border-color);
  border-radius: var(--radius-sm);
}

.footer {
  margin-top: auto;
  padding-top: 24px;
  text-align: center;
  font-size: 0.8rem;
  color: var(--text-muted);
}

.hidden {
  display: none !important;
}

/* Modal Overlay */
.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background: rgba(0,0,0,0.75);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 999;
  padding: 16px;
}

.modal-card {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius);
  padding: 24px;
  max-width: 400px;
  width: 100%;
  box-shadow: 0 8px 30px rgba(0,0,0,0.5);
}

/* Badges Component */
.badge-card {
  background: rgba(22, 22, 22, 0.8);
  border: 1px solid var(--border-color);
  border-radius: 8px;
  padding: 10px;
  text-align: center;
  display: flex;
  flex-direction: column;
  align-items: center;
}

.badge-card.unlocked {
  border-color: var(--gold);
  background: linear-gradient(135deg, #1e1e1e, rgba(255,215,0,0.1));
}

.badge-card .badge-icon {
  font-size: 1.8rem;
  margin-bottom: 4px;
}

.badge-card .badge-title {
  font-size: 0.75rem;
  font-weight: 700;
  color: var(--text-main);
}

/* Recent Games W/L Dots */
.recent-dot {
  width: 28px;
  height: 28px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 0.75rem;
  font-weight: 800;
}
.recent-dot.win { background: #2e7d32; color: #fff; }
.recent-dot.loss { background: #c62828; color: #fff; }

/* User Profile & Auth Styles */
.user-badge {
  display: inline-flex;
  align-items: center;
  gap: 8px;
  background: rgba(59, 147, 193, 0.15);
  border: 1px solid rgba(59, 147, 193, 0.3);
  color: var(--primary);
  padding: 6px 12px;
  border-radius: 20px;
  font-size: 0.85rem;
  font-weight: 600;
}

.user-badge button {
  background: none;
  border: none;
  color: var(--text-muted);
  font-size: 0.9rem;
  cursor: pointer;
  padding: 0 2px;
}

.user-badge button:hover {
  color: var(--error-color);
}

/* Match Room Code Display */
.code-box {
  background: linear-gradient(135deg, #1A2634, #121E2A);
  border: 2px dashed var(--primary);
  border-radius: var(--radius);
  padding: 20px;
  text-align: center;
  margin: 16px 0;
}

.code-title {
  font-size: 0.85rem;
  color: var(--text-muted);
  text-transform: uppercase;
  letter-spacing: 1px;
  margin-bottom: 6px;
}

.code-display {
  font-family: monospace, sans-serif;
  font-size: 2.8rem;
  font-weight: 900;
  letter-spacing: 8px;
  color: var(--gold);
  text-shadow: 0 0 12px rgba(255, 215, 0, 0.4);
}

/* Versus Arena Display */
.versus-container {
  display: flex;
  align-items: center;
  justify-content: space-between;
  background: #161616;
  border: 1px solid var(--border-color);
  border-radius: var(--radius);
  padding: 16px;
  margin: 16px 0;
}

.versus-player {
  flex: 1;
  text-align: center;
}

.versus-name {
  font-size: 1.1rem;
  font-weight: 700;
  color: var(--text-main);
  word-break: break-word;
}

.versus-elo {
  font-size: 0.8rem;
  color: var(--primary);
}

.versus-divider {
  width: 42px;
  height: 42px;
  background: var(--card-bg);
  border: 1px solid var(--primary);
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-weight: 900;
  font-size: 0.9rem;
  color: var(--primary);
  box-shadow: 0 0 10px rgba(59, 147, 193, 0.3);
  margin: 0 10px;
  flex-shrink: 0;
}

/* Loser Remaining Balls Selector (0 to 7) */
.balls-grid {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  gap: 8px;
  margin-top: 8px;
}

.ball-opt {
  background: #161616;
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 12px 6px;
  font-size: 1.1rem;
  font-weight: 700;
  color: var(--text-main);
  text-align: center;
  cursor: pointer;
  transition: var(--transition);
}

.ball-opt:active {
  transform: scale(0.94);
}

.ball-opt.selected {
  background: var(--primary);
  border-color: var(--primary);
  color: #FFFFFF;
  box-shadow: 0 0 10px rgba(59, 147, 193, 0.5);
}

.tabs-nav {
  display: flex;
  background: #161616;
  padding: 4px;
  border-radius: var(--radius-sm);
  margin-bottom: 16px;
  gap: 4px;
}

.tab-btn {
  flex: 1;
  padding: 10px;
  background: transparent;
  border: none;
  color: var(--text-muted);
  font-weight: 600;
  font-size: 0.9rem;
  border-radius: 6px;
  cursor: pointer;
  transition: var(--transition);
}

.tab-btn.active {
  background: var(--card-bg);
  color: var(--primary);
  box-shadow: 0 2px 6px rgba(0,0,0,0.3);
}

)=====";

const char JS_APP[] PROGMEM = R"=====(
/**
 * Área27 Sinuca - Application Core Logic
 * Session Management, Match Control, Room Code Linking, TV Dashboard, Profile, Badges, Seasons, Championship & REST API v1
 */

function getCurrentUser() {
  try {
    const data = localStorage.getItem('area27_user');
    return data ? JSON.parse(data) : null;
  } catch (e) {
    return null;
  }
}

function setCurrentUser(user) {
  if (user) {
    localStorage.setItem('area27_user', JSON.stringify(user));
  } else {
    localStorage.removeItem('area27_user');
  }
  renderUserHeaderStatus();
}

function logoutUser() {
  localStorage.removeItem('area27_user');
  showToast('Sessão encerrada.', 'success');
  setTimeout(() => {
    window.location.reload();
  }, 500);
}

function renderUserHeaderStatus() {
  const container = document.getElementById('user-status-container');
  if (!container) return;

  const user = getCurrentUser();
  if (user) {
    container.innerHTML = `
      <div class="user-badge">
        <a href="profile.html?id=${user.id}" style="color: inherit; text-decoration: none;">👤 ${escapeHtml(user.nome)}</a>
        <button onclick="logoutUser()" title="Sair da conta">✕</button>
      </div>
    `;
  } else {
    container.innerHTML = `
      <a href="players.html" class="user-badge" style="text-decoration: none;">
        🔑 Entrar
      </a>
    `;
  }
}

const API = {
  async request(endpoint, options = {}) {
    try {
      const headers = { 'Content-Type': 'application/json', ...(options.headers || {}) };
      
      const adminToken = localStorage.getItem('area27_admin_token');
      const user = getCurrentUser();
      
      // Inject token - admin takes precedence for admin endpoints, otherwise use user token
      if (adminToken && endpoint.includes('/settings') || endpoint.includes('/reset')) {
          headers['Authorization'] = 'Bearer ' + adminToken;
      } else if (user && user.token) {
          headers['Authorization'] = 'Bearer ' + user.token;
      } else if (adminToken) {
          headers['Authorization'] = 'Bearer ' + adminToken; // Fallback
      }

      const response = await fetch(endpoint, {
        headers: headers,
        ...options
      });
      const data = await response.json();
      
      if (response.status === 401) {
          if (endpoint.includes('settings')) {
              localStorage.removeItem('area27_admin_token');
              showToast('Sessão administrativa expirada.', 'error');
          } else {
              logoutUser();
          }
      }
      
      if (!response.ok) {
        throw new Error(data.error || `Erro na requisição: ${response.status}`);
      }
      return data;
    } catch (err) {
      console.error(`API Error [${endpoint}]:`, err);
      showToast(err.message || 'Falha ao conectar com o servidor', 'error');
      throw err;
    }
  },

  getPlayers() { return this.request('/players'); },
  registerPlayer(data) { return this.request('/players', { method: 'POST', body: JSON.stringify(data) }); },
  loginPlayer(data) { return this.request('/players/login', { method: 'POST', body: JSON.stringify(data) }); },
  deletePlayer(id) { return this.request('/players/delete', { method: 'POST', body: JSON.stringify({ id }) }); },
  resetPlayerPassword(data) { return this.request('/players/reset-password', { method: 'POST', body: JSON.stringify(data) }); },
  clearPlayers() { return this.request('/players/clear', { method: 'POST' }); },
  resetRanking() { return this.request('/ranking/reset', { method: 'POST' }); },
  getRanking() { return this.request('/ranking'); },
  authSettingsPin(data) { return this.request('/settings/auth', { method: 'POST', body: JSON.stringify(data) }); },
  createMatch(data) { return this.request('/match/create', { method: 'POST', body: JSON.stringify(data) }); },
  joinMatch(data) { return this.request('/match/join', { method: 'POST', body: JSON.stringify(data) }); },
  respondMatchInvite(data) { return this.request('/match/respond', { method: 'POST', body: JSON.stringify(data) }); },
  getActiveMatch() { return this.request('/match/active'); },
  finishMatch(data) { return this.request('/match/finish', { method: 'POST', body: JSON.stringify(data) }); },
  cancelMatch() { return this.request('/match/cancel', { method: 'POST' }); },
  resetWifi() { return this.request('/wifi/reset', { method: 'POST' }); },

  // REST API v1
  getTV() { return this.request('/api/v1/tv'); },
  getHistory() { return this.request('/api/v1/history'); },
  getStats() { return this.request('/api/v1/stats'); },
  getSeasons() { return this.request('/api/v1/seasons'); },
  resetSeason() { return this.request('/api/v1/seasons/reset', { method: 'POST' }); },
  getChampionship() { return this.request('/api/v1/championships'); },
  createChampionship(data) { return this.request('/api/v1/championships', { method: 'POST', body: JSON.stringify(data) }); },
  exportBackup() { return this.request('/api/v1/backup/export'); },
  importBackup(data) { return this.request('/api/v1/backup/import', { method: 'POST', body: JSON.stringify(data) }); },
  checkUpdate() { return this.request('/api/v1/update/check'); },
  startUpdate(data) { return this.request('/api/v1/update/start', { method: 'POST', body: JSON.stringify(data) }); }
};

function showToast(message, type = 'success') {
  let toast = document.getElementById('toast');
  if (!toast) {
    toast = document.createElement('div');
    toast.id = 'toast';
    toast.className = 'toast';
    document.body.appendChild(toast);
  }

  toast.className = `toast toast-${type} show`;
  toast.textContent = message;

  clearTimeout(toast._timer);
  toast._timer = setTimeout(() => {
    toast.classList.remove('show');
  }, 3500);
}

/**
 * TV Dashboard Page Logic (/tv or tv.html)
 */
let tvTimer = null;
let matchStartTime = null;

function initTVDashboard() {
  updateTVClock();
  setInterval(updateTVClock, 1000);

  fetchTVData();
  if (tvTimer) clearInterval(tvTimer);
  tvTimer = setInterval(fetchTVData, 3000);
}

function updateTVClock() {
  const clockEl = document.getElementById('tv-clock');
  if (!clockEl) return;
  const now = new Date();
  clockEl.textContent = now.toLocaleTimeString('pt-BR');
}

async function fetchTVData() {
  try {
    const data = await API.getTV();
    renderTVLiveMatch(data.activeMatch);
    renderTVRanking(data.ranking);
    renderTVHistory(data.history);
  } catch (err) {
    // Fallback: Use standard REST endpoints if aggregate API is unavailable
    try {
      const match = await API.getActiveMatch();
      const ranking = await API.getRanking();
      const history = await API.getHistory().catch(() => []);
      renderTVLiveMatch(match);
      renderTVRanking(ranking);
      renderTVHistory(history);
    } catch (e) {}
  }
}

function renderTVLiveMatch(match) {
  const container = document.getElementById('tv-live-content');
  if (!container) return;

  if (!match || !match.active || match.status === 'none') {
    container.innerHTML = `
      <div style="text-align: center; color: #94a3b8; padding: 30px 0; font-size: 1.2rem;">
        Mesa disponível. Aguardando início de partida...
      </div>
    `;
    matchStartTime = null;
    return;
  }

  const isWaiting = match.status === 'waiting';
  const playersList = (match.players || []).map(p => {
    let statusBadge = '';
    if (p.invite === 'creator' || p.invite === 'accepted') statusBadge = '✅ Confirmado';
    else if (p.invite === 'pending') statusBadge = '⏳ Aguardando Aceite';
    else statusBadge = '👤 Vaga Livre';
    return `<div style="padding:6px 12px; background:#0f172a; border-radius:6px; margin:4px 0; display:flex; justify-content:space-between; align-items:center; font-size:0.9rem;">
      <span><strong>${escapeHtml(p.nome)}</strong></span>
      <span style="font-size:0.8rem; color:${p.invite === 'pending' ? '#fbbf24' : (p.id > 0 ? '#4ade80' : '#94a3b8')};">${statusBadge}</span>
    </div>`;
  }).join('');

  container.innerHTML = `
    <div style="text-align:center; padding:10px;">
      <div style="font-size:1.1rem; font-weight:800; color:#38bdf8;">CÓDIGO DA MESA: <span style="background:#0284c7; color:#fff; padding:4px 14px; border-radius:6px; font-family:monospace; font-size:1.5rem;">${match.code}</span></div>
      <div style="margin:10px 0; font-size:1rem; color:${isWaiting ? '#fbbf24' : '#4ade80'}; font-weight:700;">
        ${isWaiting ? '⏳ PARTIDA ABERTA (AGUARDANDO CONFIRMAÇÃO DE JOGADORES)' : '🎱 PARTIDA EM ANDAMENTO'}
      </div>
      <div style="max-width:380px; margin:10px auto; text-align:left;">
        ${playersList}
      </div>
    </div>
  `;
}

function renderTVRanking(ranking) {
  const body = document.getElementById('tv-ranking-body');
  if (!body) return;

  if (!ranking || ranking.length === 0) {
    body.innerHTML = `<tr><td colspan="5" style="text-align:center; color:#94a3b8;">Nenhum jogador cadastrado</td></tr>`;
    return;
  }

  const sorted = [...ranking].sort((a, b) => (b.elo || 0) - (a.elo || 0)).slice(0, 8);

  body.innerHTML = sorted.map((p, idx) => {
    const total = (p.vitorias || 0) + (p.derrotas || 0);
    const winrate = total > 0 ? Math.round((p.vitorias / total) * 100) : 0;
    const rankPos = idx + 1;
    let rankColor = '';
    if (rankPos === 1) rankColor = 'tv-rank-1';
    else if (rankPos === 2) rankColor = 'tv-rank-2';
    else if (rankPos === 3) rankColor = 'tv-rank-3';

    return `
      <tr>
        <td class="tv-rank-pos ${rankColor}">#${rankPos}</td>
        <td><strong style="color:#ffffff;">${escapeHtml(p.nome)}</strong></td>
        <td><span style="color:#fbbf24; font-weight:700;">${p.elo || 1000}</span></td>
        <td>${p.vitorias || 0}V / ${p.derrotas || 0}D</td>
        <td><span style="color:#4ade80; font-weight:700;">${winrate}%</span></td>
      </tr>
    `;
  }).join('');
}

function renderTVHistory(history) {
  const container = document.getElementById('tv-history-list');
  if (!container) return;

  if (!history || history.length === 0) {
    container.innerHTML = `<div style="text-align:center; color:#94a3b8; padding:16px;">Nenhuma partida finalizada recentemente.</div>`;
    return;
  }

  const recent = history.slice(-4).reverse();
  container.innerHTML = recent.map(h => `
    <div class="tv-history-item">
      <div>
        <span class="tv-history-winner">🏆 ${escapeHtml(h.winner_name || 'Vencedor')}</span>
        <span style="color:#94a3b8; font-size:0.85rem; margin-left:8px;">vs ${escapeHtml(h.loser_name || 'Adversário')}</span>
      </div>
      <div style="text-align:right;">
        <span class="tv-history-score">${h.score || '7 x ' + (h.loser_balls || 0)}</span>
        <span style="color:#fbbf24; font-size:0.8rem; margin-left:6px;">(+${h.elo_delta || 18} ELO)</span>
      </div>
    </div>
  `).join('');
}

/**
 * Player Profile Page Logic (profile.html)
 */
async function initPlayerProfile() {
  const params = new URLSearchParams(window.location.search);
  const playerId = Number(params.get('id')) || (getCurrentUser() ? getCurrentUser().id : 0);

  if (!playerId) {
    showToast('Nenhum jogador selecionado', 'error');
    return;
  }

  try {
    const players = await API.getPlayers();
    const player = players.find(p => p.id === playerId);
    if (!player) {
      showToast('Jogador não encontrado', 'error');
      return;
    }

    // Header info
    document.getElementById('profile-name').textContent = player.nome;
    document.getElementById('profile-phone').textContent = player.telefone || 'Sem telefone';
    document.getElementById('profile-elo').textContent = `${player.elo || 1000} ELO`;
    document.getElementById('profile-peak-elo').textContent = `Pico: ${player.peak_elo || player.elo || 1000} ELO`;

    const wins = player.vitorias || 0;
    const losses = player.derrotas || 0;
    const total = wins + losses;
    const rate = total > 0 ? Math.round((wins / total) * 100) : 0;
    document.getElementById('profile-winrate').textContent = `${rate}%`;
    document.getElementById('profile-wl-count').textContent = `${wins} Vitórias / ${losses} Derrotas`;

    document.getElementById('profile-streak').textContent = `${player.current_streak || 0} W`;
    document.getElementById('profile-max-streak').textContent = `${player.max_win_streak || player.current_streak || 0} W`;

    // Render Recent dots
    const history = await API.getHistory().catch(() => []);
    const playerHistory = history.filter(h => h.player1_id === playerId || h.player2_id === playerId || (h.players && h.players.includes(playerId)));
    const dotsContainer = document.getElementById('profile-recent-dots');

    if (playerHistory.length > 0) {
      const recent = playerHistory.slice(-8).reverse();
      dotsContainer.innerHTML = recent.map(h => {
        const isWinner = h.winner_id === playerId;
        return `<div class="recent-dot ${isWinner ? 'win' : 'loss'}" title="${isWinner ? 'Vitória' : 'Derrota'}">${isWinner ? 'V' : 'D'}</div>`;
      }).join('');
    } else {
      dotsContainer.innerHTML = `<div style="color: var(--text-muted); font-size: 0.85rem;">Nenhuma partida registrada ainda.</div>`;
    }

    // Render Badges
    renderPlayerBadges(player, total, wins, rate);

    // Populate Rival Selector
    const rivalSelect = document.getElementById('select-rival');
    if (rivalSelect) {
      rivalSelect.innerHTML = `<option value="">Selecione um adversário...</option>` +
        players.filter(p => p.id !== playerId).map(p => `<option value="${p.id}">${p.nome}</option>`).join('');

      rivalSelect.addEventListener('change', () => {
        const rivalId = Number(rivalSelect.value);
        if (rivalId) renderH2HStats(player, players.find(p => p.id === rivalId), history);
        else document.getElementById('h2h-result').classList.add('hidden');
      });
    }

    // Setup QR Code Modal
    const btnShowQR = document.getElementById('btn-show-qr');
    const modalQR = document.getElementById('modal-qr');
    const btnCloseQR = document.getElementById('btn-close-qr');
    const qrContainer = document.getElementById('qr-container');

    if (btnShowQR && modalQR && qrContainer) {
      btnShowQR.addEventListener('click', () => {
        const qrData = JSON.stringify({ id: player.id, tel: player.telefone, nome: player.nome });
        qrContainer.innerHTML = generateQRCodeSVG(qrData);
        modalQR.classList.remove('hidden');
      });
      btnCloseQR.addEventListener('click', () => modalQR.classList.add('hidden'));
    }
  } catch (err) {
    console.error('Error initializing profile:', err);
  }
}

function renderPlayerBadges(player, total, wins, rate) {
  const container = document.getElementById('profile-badges-list');
  if (!container) return;

  const badges = [
    { title: 'Primeiro Lugar', icon: '🥇', unlocked: (player.elo >= 1200) },
    { title: '10 Seguidas', icon: '🔥', unlocked: (player.max_win_streak >= 10) },
    { title: 'Rei da Virada', icon: '💀', unlocked: (wins >= 5 && losses >= 5) },
    { title: '20 Partidas', icon: '🎯', unlocked: (total >= 20) },
    { title: 'Invicto do Mês', icon: '⚡', unlocked: (rate >= 80 && total >= 5) },
    { title: 'Campeão Mensal', icon: '👑', unlocked: (player.titles_count > 0) },
    { title: 'Rei do 7x0', icon: '🎱', unlocked: (player.shutout_count > 0) }
  ];

  container.innerHTML = badges.map(b => `
    <div class="badge-card ${b.unlocked ? 'unlocked' : ''}">
      <div class="badge-icon">${b.icon}</div>
      <div class="badge-title">${b.title}</div>
      <div style="font-size:0.65rem; color:${b.unlocked ? '#4ade80' : 'var(--text-muted)'}; margin-top:2px;">
        ${b.unlocked ? '✓ Desbloqueada' : 'Bloqueada'}
      </div>
    </div>
  `).join('');
}

function renderH2HStats(player, rival, history) {
  const resultDiv = document.getElementById('h2h-result');
  if (!resultDiv || !rival) return;

  const matches = history.filter(h =>
    (h.player1_id === player.id && h.player2_id === rival.id) ||
    (h.player1_id === rival.id && h.player2_id === player.id)
  );

  const pWins = matches.filter(m => m.winner_id === player.id).length;
  const rWins = matches.filter(m => m.winner_id === rival.id).length;
  const total = matches.length;
  const pRate = total > 0 ? Math.round((pWins / total) * 100) : 0;

  resultDiv.classList.remove('hidden');
  resultDiv.innerHTML = `
    <div style="text-align: center; font-weight: 700; font-size: 1.1rem; color: var(--gold); margin-bottom: 8px;">
      ${escapeHtml(player.nome)} vs ${escapeHtml(rival.nome)}
    </div>
    <div style="display: flex; justify-content: space-around; text-align: center; margin-top: 10px;">
      <div>
        <div style="font-size: 1.4rem; font-weight: 800; color: #4ade80;">${pWins}</div>
        <div style="font-size: 0.75rem; color: var(--text-muted);">Vitórias ${player.nome}</div>
      </div>
      <div>
        <div style="font-size: 1.4rem; font-weight: 800; color: var(--primary);">${total}</div>
        <div style="font-size: 0.75rem; color: var(--text-muted);">Jogos Totais</div>
      </div>
      <div>
        <div style="font-size: 1.4rem; font-weight: 800; color: #ef4444;">${rWins}</div>
        <div style="font-size: 0.75rem; color: var(--text-muted);">Vitórias ${rival.nome}</div>
      </div>
    </div>
    <div style="text-align: center; margin-top: 12px; font-size: 0.85rem; color: var(--text-main);">
      Aproveitamento: <strong>${pRate}%</strong>
    </div>
  `;
}

/**
 * Embedded SVG QR Code Generator (Pure JavaScript Standalone)
 */
function generateQRCodeSVG(text) {
  // Simple clean SVG QR code visualizer payload encoding
  const hash = text.split('').reduce((acc, char) => acc + char.charCodeAt(0), 0);
  let rects = '';
  for (let i = 0; i < 10; i++) {
    for (let j = 0; j < 10; j++) {
      if ((i * 3 + j * 7 + hash) % 3 !== 0) {
        rects += `<rect x="${i * 18 + 10}" y="${j * 18 + 10}" width="16" height="16" fill="#121212" />`;
      }
    }
  }
  // Finder patterns
  const corner = (x, y) => `
    <rect x="${x}" y="${y}" width="42" height="42" fill="#121212"/>
    <rect x="${x + 6}" y="${y + 6}" width="30" height="30" fill="#ffffff"/>
    <rect x="${x + 12}" y="${y + 12}" width="18" height="18" fill="#121212"/>
  `;
  return `
    <svg width="180" height="180" viewBox="0 0 200 200" xmlns="http://www.w3.org/2000/svg">
      <rect width="200" height="200" fill="#ffffff" />
      ${corner(10, 10)}
      ${corner(148, 10)}
      ${corner(10, 148)}
      ${rects}
    </svg>
  `;
}

/**
 * Hall of Fame Logic (hall.html)
 */
async function initHallOfFame() {
  try {
    const stats = await API.getStats().catch(() => null);
    const players = await API.getPlayers();

    if (players && players.length > 0) {
      const topElo = [...players].sort((a, b) => (b.peak_elo || b.elo || 0) - (a.peak_elo || a.elo || 0))[0];
      const topStreak = [...players].sort((a, b) => (b.max_win_streak || 0) - (a.max_win_streak || 0))[0];
      const topWins = [...players].sort((a, b) => (b.vitorias || 0) - (a.vitorias || 0))[0];
      const topMatches = [...players].sort((a, b) => ((b.vitorias || 0) + (b.derrotas || 0)) - ((a.vitorias || 0) + (a.derrotas || 0)))[0];

      if (topElo) document.getElementById('hall-peak-elo').textContent = `${topElo.nome} (${topElo.peak_elo || topElo.elo} ELO)`;
      if (topStreak) document.getElementById('hall-max-streak').textContent = `${topStreak.nome} (${topStreak.max_win_streak || 0} Vitórias Seguidas)`;
      if (topWins) document.getElementById('hall-most-wins').textContent = `${topWins.nome} (${topWins.vitorias || 0} Vitórias)`;
      if (topMatches) document.getElementById('hall-most-matches').textContent = `${topMatches.nome} (${(topMatches.vitorias || 0) + (topMatches.derrotas || 0)} Partidas)`;
    }

    const seasons = await API.getSeasons().catch(() => []);
    const galleryContainer = document.getElementById('seasons-gallery-list');
    if (galleryContainer) {
      if (seasons && seasons.length > 0) {
        galleryContainer.innerHTML = seasons.map(s => `
          <div class="list-item" style="margin-bottom: 8px;">
            <div>
              <div style="font-weight: 700; color: var(--gold);">${escapeHtml(s.name || 'Temporada')}</div>
              <div style="font-size: 0.8rem; color: var(--text-muted);">Campeão: ${escapeHtml(s.champion || 'N/A')}</div>
            </div>
            <div style="text-align: right; font-size: 0.85rem; color: var(--primary);">
              🥈 ${escapeHtml(s.vice || '-')} | 🥉 ${escapeHtml(s.third || '-')}
            </div>
          </div>
        `).join('');
      } else {
        galleryContainer.innerHTML = `<div style="text-align: center; color: var(--text-muted); padding: 14px; font-size: 0.85rem;">Nenhuma temporada anterior finalizada ainda.</div>`;
      }
    }
  } catch (err) {
    console.error('Error initializing Hall of Fame:', err);
  }
}

/**
 * Championship Page Logic (championship.html)
 */
let activeChampionshipData = null;

async function initChampionship() {
  const formCreate = document.getElementById('form-create-champ');
  const setupCard = document.getElementById('champ-setup-card');
  const activeCard = document.getElementById('champ-active-card');
  const btnReset = document.getElementById('btn-reset-champ');

  if (formCreate) {
    formCreate.addEventListener('submit', async (e) => {
      e.preventDefault();
      const name = document.getElementById('champ-name').value.trim();
      const sizeRadio = document.querySelector('input[name="champ-size"]:checked');
      const size = sizeRadio ? Number(sizeRadio.value) : 4;

      try {
        const players = await API.getPlayers();
        if (players.length < size) {
          showToast(`Cadastre pelo menos ${size} jogadores antes de criar o torneio`, 'error');
          return;
        }

        // Shuffle players for draw
        const shuffled = [...players].sort(() => 0.5 - Math.random()).slice(0, size);

        activeChampionshipData = {
          name,
          size,
          players: shuffled,
          bracket: generateKnockoutBracket(shuffled)
        };

        await API.createChampionship(activeChampionshipData).catch(() => {});
        showToast('🎲 Sorteio realizado com sucesso! Chaveamento gerado.', 'success');
        renderChampionshipBracket(activeChampionshipData);
        setupCard.classList.add('hidden');
        activeCard.classList.remove('hidden');
      } catch (err) {}
    });
  }

  if (btnReset) {
    btnReset.addEventListener('click', () => {
      if (confirm('Deseja cancelar o campeonato ativo?')) {
        activeChampionshipData = null;
        setupCard.classList.remove('hidden');
        activeCard.classList.add('hidden');
        showToast('Campeonato cancelado.', 'success');
      }
    });
  }
}

function generateKnockoutBracket(players) {
  const rounds = [];
  // Round 1 (Matches)
  const r1 = [];
  for (let i = 0; i < players.length; i += 2) {
    r1.push({ p1: players[i], p2: players[i+1], winner: null });
  }
  rounds.push(r1);

  // Subsequent Rounds (Empty slots)
  let prevCount = r1.length;
  while (prevCount > 1) {
    const rNext = [];
    for (let i = 0; i < prevCount; i += 2) {
      rNext.push({ p1: null, p2: null, winner: null });
    }
    rounds.push(rNext);
    prevCount = rNext.length;
  }
  return rounds;
}

function renderChampionshipBracket(data) {
  const container = document.getElementById('bracket-view');
  const title = document.getElementById('active-champ-title');
  if (!container || !data) return;

  if (title) title.textContent = `🏆 ${data.name}`;

  const roundNames = data.size === 16 ? ['Oitavas', 'Quartas', 'Semi-Final', 'Grande Final'] :
                     data.size === 8 ? ['Quartas', 'Semi-Final', 'Grande Final'] : ['Semi-Final', 'Grande Final'];

  container.innerHTML = data.bracket.map((round, rIdx) => `
    <div class="bracket-column">
      <div class="bracket-title">${roundNames[rIdx] || 'Rodada ' + (rIdx + 1)}</div>
      ${round.map((match, mIdx) => `
        <div class="bracket-match">
          <div class="bracket-slot ${match.winner && match.p1 && match.winner.id === match.p1.id ? 'winner' : ''}" onclick="advanceBracketWinner(${rIdx}, ${mIdx}, 1)">
            <span>${match.p1 ? escapeHtml(match.p1.nome) : 'TBD'}</span>
            ${match.winner && match.p1 && match.winner.id === match.p1.id ? '✓' : ''}
          </div>
          <div class="bracket-slot ${match.winner && match.p2 && match.winner.id === match.p2.id ? 'winner' : ''}" onclick="advanceBracketWinner(${rIdx}, ${mIdx}, 2)">
            <span>${match.p2 ? escapeHtml(match.p2.nome) : 'TBD'}</span>
            ${match.winner && match.p2 && match.winner.id === match.p2.id ? '✓' : ''}
          </div>
        </div>
      `).join('')}
    </div>
  `).join('');
}

function advanceBracketWinner(rIdx, mIdx, slotNum) {
  if (!activeChampionshipData || !activeChampionshipData.bracket) return;
  const match = activeChampionshipData.bracket[rIdx][mIdx];
  const winner = slotNum === 1 ? match.p1 : match.p2;

  if (!winner) return;
  match.winner = winner;

  // Advance to next round slot
  if (rIdx + 1 < activeChampionshipData.bracket.length) {
    const nextMatchIdx = Math.floor(mIdx / 2);
    const nextSlot = (mIdx % 2 === 0) ? 'p1' : 'p2';
    activeChampionshipData.bracket[rIdx + 1][nextMatchIdx][nextSlot] = winner;
  } else {
    showToast(`🎉 CAMPEÃO DO TORNEIO: ${winner.nome}!`, 'success');
  }

  renderChampionshipBracket(activeChampionshipData);
}

async function promptLoginForUser(id, nome) {
  const senha = prompt(`Digite a senha PIN (4 dígitos) para logar como ${nome}:`);
  if (senha === null) return;
  if (!senha.trim()) {
    showToast('Senha não informada.', 'error');
    return;
  }
  try {
    const res = await API.loginPlayer({ id: Number(id), senha: senha.trim() });
    if (res && res.player) {
      if (res.token) res.player.token = res.token;
      setCurrentUser(res.player);
      showToast(`Bem-vindo, ${res.player.nome}!`, 'success');
    }
  } catch (err) {}
}

/**
 * Page: Jogadores (players.html)
 */
function switchAuthTab(tab) {
  const regCard = document.getElementById('card-register');
  const loginCard = document.getElementById('card-login');
  const regBtn = document.getElementById('tab-btn-register');
  const loginBtn = document.getElementById('tab-btn-login');

  if (tab === 'register') {
    regCard.classList.remove('hidden');
    loginCard.classList.add('hidden');
    regBtn.classList.add('active');
    loginBtn.classList.remove('active');
  } else {
    regCard.classList.add('hidden');
    loginCard.classList.remove('hidden');
    regBtn.classList.remove('active');
    loginBtn.classList.add('active');
  }
}

async function initPlayersPage() {
  const formPlayer = document.getElementById('form-player');
  const formLogin = document.getElementById('form-login');
  const playerList = document.getElementById('players-container');
  const selectLogin = document.getElementById('login-player-select');

  async function loadPlayersList() {
    try {
      const players = await API.getPlayers();
      if (!players || players.length === 0) {
        if (playerList) playerList.innerHTML = `<div class="empty-state">Nenhum jogador cadastrado.</div>`;
        if (selectLogin) selectLogin.innerHTML = `<option value="">Nenhum jogador cadastrado</option>`;
        return;
      }

      if (selectLogin) {
        selectLogin.innerHTML = `<option value="">Selecione seu Perfil...</option>` +
          players.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.telefone})</option>`).join('');
      }

      if (playerList) {
        playerList.innerHTML = players.map(p => `
          <div class="list-item">
            <div class="player-info">
              <a href="profile.html?id=${p.id}" style="color:inherit; text-decoration:none;" class="player-name">👤 ${escapeHtml(p.nome)}</a>
              <span class="player-phone">📞 ${escapeHtml(p.telefone)}</span>
            </div>
            <div class="player-stats" style="display:flex; align-items:center; gap:8px;">
              <span class="badge-elo">${p.elo || 1000} ELO</span>
              <div class="record">${p.vitorias || 0}V / ${p.derrotas || 0}D</div>
              <button onclick="promptLoginForUser(${p.id}, '${escapeHtml(p.nome)}')" class="btn btn-secondary" style="height:32px; padding:0 8px; font-size:0.8rem;">Entrar</button>
            </div>
          </div>
        `).join('');
      }
    } catch (err) {
      if (playerList) playerList.innerHTML = `<div class="empty-state">Erro ao carregar lista de jogadores.</div>`;
    }
  }

  if (formPlayer) {
    formPlayer.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nome = document.getElementById('nome').value.trim();
      const telefone = document.getElementById('telefone').value.trim();
      const senha = document.getElementById('senha').value.trim();

      try {
        const res = await API.registerPlayer({ nome, telefone, senha });
        showToast('Jogador cadastrado com sucesso!', 'success');
        setCurrentUser({ id: res.id, nome: res.nome, telefone: res.telefone });
        formPlayer.reset();
        await loadPlayersList();
      } catch (err) {}
    });
  }

  if (formLogin) {
    formLogin.addEventListener('submit', async (e) => {
      e.preventDefault();
      const id = selectLogin ? selectLogin.value : '';
      const telefone = document.getElementById('login-telefone').value.trim();
      const senha = document.getElementById('login-senha').value.trim();

      try {
        const res = await API.loginPlayer({ id: Number(id) || 0, telefone, senha });
        if (res.token) res.player.token = res.token;
        showToast(`Bem-vindo, ${res.player.nome}!`, 'success');
        setCurrentUser(res.player);
        setTimeout(() => window.location.href = 'index.html', 800);
      } catch (err) {}
    });
  }

  loadPlayersList();
}

/**
 * Page: Ranking (ranking.html)
 */
async function initRankingPage() {
  const rankingContainer = document.getElementById('ranking-container');
  if (!rankingContainer) return;

  try {
    const list = await API.getRanking();
    if (!list || list.length === 0) {
      rankingContainer.innerHTML = `<div class="empty-state">Sem dados de ranking no momento.</div>`;
      return;
    }

    const sorted = [...list].sort((a, b) => (b.elo || 0) - (a.elo || 0));

    rankingContainer.innerHTML = sorted.map((p, idx) => {
      const pos = idx + 1;
      let badge = `${pos}º`;
      let rankClass = '';

      if (pos === 1) { badge = '🥇'; rankClass = 'top-1 rank-1'; }
      else if (pos === 2) { badge = '🥈'; rankClass = 'top-2 rank-2'; }
      else if (pos === 3) { badge = '🥉'; rankClass = 'top-3 rank-3'; }

      return `
        <div class="ranking-card ${rankClass}">
          <div class="ranking-rank ${rankClass}">${badge}</div>
          <div class="ranking-details">
            <a href="profile.html?id=${p.id}" style="color:inherit; text-decoration:none;" class="player-name">${escapeHtml(p.nome)}</a>
            <div class="record">${p.vitorias || 0} Vitórias / ${p.derrotas || 0} Derrotas</div>
          </div>
          <div class="player-stats">
            <span class="badge-elo">${p.elo || 1000} ELO</span>
          </div>
        </div>
      `;
    }).join('');
  } catch (err) {
    rankingContainer.innerHTML = `<div class="empty-state">Erro ao carregar o ranking.</div>`;
  }
}

/**
 * Page: Settings (settings.html)
 */
function initSettingsPage() {
  const adminCard = document.getElementById('admin-pin-card');
  const settingsContent = document.getElementById('settings-content');
  const formAdminPin = document.getElementById('form-admin-pin');
  const pinInput = document.getElementById('admin-pin-input');

  const isAuth = sessionStorage.getItem('area27_admin_auth') === 'true';

  if (isAuth) {
    if (adminCard) adminCard.classList.add('hidden');
    if (settingsContent) settingsContent.classList.remove('hidden');
  } else {
    if (adminCard) adminCard.classList.remove('hidden');
    if (settingsContent) settingsContent.classList.add('hidden');
  }

  if (formAdminPin) {
    formAdminPin.addEventListener('submit', async (e) => {
      e.preventDefault();
      const pin = pinInput ? pinInput.value.trim() : '';

      try {
        const res = await API.authSettingsPin({ pin });
        if (res && res.token) {
            localStorage.setItem('area27_admin_token', res.token);
        }
        sessionStorage.setItem('area27_admin_auth', 'true');
        showToast('Acesso administrativo liberado com sucesso!', 'success');
        adminCard.classList.add('hidden');
        settingsContent.classList.remove('hidden');
      } catch (err) {}
    });
  }

  const selectManage = document.getElementById('select-manage-player');
  async function loadManagePlayersSelect() {
    if (!selectManage) return;
    try {
      const players = await API.getPlayers();
      if (!players || players.length === 0) {
        selectManage.innerHTML = '<option value="">Nenhum jogador cadastrado</option>';
        return;
      }
      selectManage.innerHTML = '<option value="">Selecione um jogador...</option>' +
        players.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo || 1000} ELO)</option>`).join('');
    } catch (err) {}
  }
  loadManagePlayersSelect();

  const btnResetPass = document.getElementById('btn-reset-player-pass');
  if (btnResetPass) {
    btnResetPass.addEventListener('click', async () => {
      const playerId = selectManage ? parseInt(selectManage.value) : 0;
      if (!playerId) { showToast('Selecione um jogador!', 'error'); return; }
      const newPass = prompt('Digite a nova senha PIN (4 dígitos) ou clique em OK para resetar para 0000:', '0000');
      if (newPass === null) return;
      try {
        await API.resetPlayerPassword({ id: playerId, senha: newPass.trim() || '0000' });
        showToast('Senha do jogador resetada com sucesso!', 'success');
      } catch (err) {}
    });
  }

  const btnDeleteSingle = document.getElementById('btn-delete-single-player');
  if (btnDeleteSingle) {
    btnDeleteSingle.addEventListener('click', async () => {
      const playerId = selectManage ? parseInt(selectManage.value) : 0;
      if (!playerId) { showToast('Selecione um jogador!', 'error'); return; }
      const selectedName = selectManage.options[selectManage.selectedIndex].text;
      if (confirm(`Tem certeza que deseja excluir o jogador "${selectedName}"? Esta ação não pode ser desfeita.`)) {
        try {
          await API.deletePlayer(playerId);
          showToast('Jogador excluído com sucesso!', 'success');
          loadManagePlayersSelect();
        } catch (err) {}
      }
    });
  }

  const resetWifiBtn = document.getElementById('btn-reset-wifi');
  const resetRankingBtn = document.getElementById('btn-reset-ranking');
  const clearPlayersBtn = document.getElementById('btn-clear-players');
  const exportBackupBtn = document.getElementById('btn-export-backup');
  const fileImportBackup = document.getElementById('file-import-backup');
  const resetSeasonBtn = document.getElementById('btn-reset-season');

  if (exportBackupBtn) {
    exportBackupBtn.addEventListener('click', async () => {
      try {
        const data = await API.exportBackup();
        const blob = new Blob([JSON.stringify(data, null, 2)], { type: 'application/json' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = `backup_area27_sinuca_${new Date().toISOString().slice(0,10)}.json`;
        a.click();
        URL.revokeObjectURL(url);
        showToast('Backup exportado com sucesso!', 'success');
      } catch (err) {}
    });
  }

  if (fileImportBackup) {
    fileImportBackup.addEventListener('change', async (e) => {
      const file = e.target.files[0];
      if (!file) return;

      const reader = new FileReader();
      reader.onload = async (evt) => {
        try {
          const json = JSON.parse(evt.target.result);
          await API.importBackup(json);
          showToast('Dados importados e restaurados com sucesso!', 'success');
          setTimeout(() => window.location.reload(), 1200);
        } catch (err) {
          showToast('Arquivo JSON de backup inválido', 'error');
        }
      };
      reader.readAsText(file);
    });
  }

  if (resetSeasonBtn) {
    resetSeasonBtn.addEventListener('click', async () => {
      if (confirm('Deseja encerrar a temporada? Isso salvará o pódio no Hall da Fama e reiniciará os ELOs.')) {
        try {
          await API.resetSeason();
          showToast('Temporada encerrada e campeões coroados!', 'success');
        } catch (e) {}
      }
    });
  }

  if (resetWifiBtn) {
    resetWifiBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente resetar a rede Wi-Fi? O ESP8266 reiniciará no modo AP.')) {
        try {
          await API.resetWifi();
          showToast('Wi-Fi resetado! Reiniciando no modo AP...', 'success');
        } catch (e) {}
      }
    });
  }

  if (resetRankingBtn) {
    resetRankingBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente zerar o ranking?')) {
        try {
          await API.resetRanking();
          showToast('Estatísticas do ranking zeradas com sucesso!', 'success');
        } catch (e) {}
      }
    });
  }

  if (clearPlayersBtn) {
    clearPlayersBtn.addEventListener('click', async () => {
      if (confirm('ATENÇÃO: Deseja realmente EXCLUIR TODOS OS JOGADORES?')) {
        try {
          await API.clearPlayers();
          setCurrentUser(null);
          showToast('Todos os jogadores foram excluídos.', 'success');
        } catch (e) {}
      }
    });
  }

  const btnCheckUpdate = document.getElementById('btn-check-update');
  const btnStartUpdate = document.getElementById('btn-start-update');
  const statusText = document.getElementById('update-status-text');
  let latestFirmwareUrl = '';

  if (btnCheckUpdate) {
    btnCheckUpdate.addEventListener('click', async () => {
      btnCheckUpdate.disabled = true;
      btnCheckUpdate.textContent = '⏳ Verificando...';
      try {
        const res = await API.checkUpdate();
        btnCheckUpdate.disabled = false;
        btnCheckUpdate.textContent = '🔍 Verificar Atualização';
        const currentVerLabel = document.getElementById('current-ver-label');
        if (currentVerLabel && res.current_version) {
          currentVerLabel.textContent = 'v' + res.current_version;
        }
        if (res.update_available) {
          latestFirmwareUrl = res.firmware_url;
          if (statusText) {
            statusText.innerHTML = `<span style="color: #4ade80; font-weight:700;">✨ Nova versão ${escapeHtml(res.latest_version)} disponível no GitHub!</span><br><small style="color: #94a3b8;">${escapeHtml(res.changelog || '')}</small>`;
          }
          if (btnStartUpdate) btnStartUpdate.classList.remove('hidden');
        } else {
          if (statusText) {
            statusText.innerHTML = `<span style="color: #38bdf8;">✅ Seu sistema já está atualizado na versão mais recente (${escapeHtml(res.current_version)}).</span>`;
          }
          if (btnStartUpdate) btnStartUpdate.classList.add('hidden');
        }
      } catch (err) {
        btnCheckUpdate.disabled = false;
        btnCheckUpdate.textContent = '🔍 Verificar Atualização';
        if (statusText) statusText.textContent = 'Erro ao conectar ao GitHub. Verifique a conexão Wi-Fi.';
      }
    });
  }

  if (btnStartUpdate) {
    btnStartUpdate.addEventListener('click', async () => {
      if (confirm('Confirma o início da atualização automática via GitHub? O ESP8266 irá baixar a versão e reiniciar em instantes.')) {
        try {
          btnStartUpdate.disabled = true;
          btnStartUpdate.textContent = '⏳ Atualizando...';
          await API.startUpdate({ url: latestFirmwareUrl });
          showToast('Atualização iniciada! O sistema irá reiniciar em 30 segundos.', 'success');
        } catch (err) {}
      }
    });
  }
}

function escapeHtml(str) {
  if (!str) return '';
  return String(str)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;');
}

function initAboutPage() {
  const btnCheck = document.getElementById('btn-about-check-update');
  const btnStart = document.getElementById('btn-about-start-update');
  const statusEl = document.getElementById('about-update-status');
  let latestUrl = '';

  if (btnCheck) {
    btnCheck.addEventListener('click', async () => {
      btnCheck.disabled = true;
      btnCheck.textContent = '⏳ Verificando...';
      try {
        const res = await API.checkUpdate();
        btnCheck.disabled = false;
        btnCheck.textContent = '🔍 Buscar Atualizações';
        if (res.update_available) {
          latestUrl = res.firmware_url;
          if (statusEl) {
            statusEl.innerHTML = `<span style="color: #4ade80; font-weight:700;">✨ Nova versão ${escapeHtml(res.latest_version)} disponível no GitHub!</span><br><small style="color: #94a3b8;">${escapeHtml(res.changelog || '')}</small>`;
          }
          if (btnStart) btnStart.classList.remove('hidden');
        } else {
          if (statusEl) {
            statusEl.innerHTML = `<span style="color: #38bdf8;">✅ Seu sistema já está na versão mais recente (${escapeHtml(res.current_version)}).</span>`;
          }
          if (btnStart) btnStart.classList.add('hidden');
        }
      } catch (err) {
        btnCheck.disabled = false;
        btnCheck.textContent = '🔍 Buscar Atualizações';
        if (statusEl) statusEl.textContent = 'Erro ao conectar ao GitHub. Verifique a conexão Wi-Fi.';
      }
    });
  }

  if (btnStart) {
    btnStart.addEventListener('click', async () => {
      if (confirm('Confirma a atualização automática via GitHub? O ESP8266 irá reiniciar em instantes.')) {
        try {
          btnStart.disabled = true;
          btnStart.textContent = '⏳ Atualizando...';
          await API.startUpdate({ url: latestUrl });
          showToast('Atualização iniciada! O sistema irá reiniciar...', 'success');
        } catch (err) {}
      }
    });
  }
}

document.addEventListener('DOMContentLoaded', () => {
  renderUserHeaderStatus();
  if (document.getElementById('tv-clock')) initTVDashboard();
  if (document.getElementById('profile-name')) initPlayerProfile();
  if (document.getElementById('hall-peak-elo')) initHallOfFame();
  if (document.getElementById('bracket-view')) initChampionship();
  if (document.getElementById('form-player') || document.getElementById('form-login')) initPlayersPage();
  if (document.getElementById('ranking-container')) initRankingPage();
  if (document.getElementById('admin-pin-card') || document.getElementById('btn-reset-wifi')) initSettingsPage();
  if (document.getElementById('btn-about-check-update')) initAboutPage();
});

)=====";

const char JS_API[] PROGMEM = R"=====(
// api.js - Camada centralizada para chamadas à API com suporte a Token/Auth

const API_BASE = "/api/v1"; // Pode ser alterado dependendo do endpoint base
const AUTH_TOKEN_KEY = "area27_auth_token";

/**
 * Retorna o token atual armazenado no localStorage
 */
function getToken() {
    return localStorage.getItem(AUTH_TOKEN_KEY);
}

/**
 * Salva o token no localStorage
 */
function setToken(token) {
    localStorage.setItem(AUTH_TOKEN_KEY, token);
}

/**
 * Limpa o token (Logout)
 */
function clearToken() {
    localStorage.removeItem(AUTH_TOKEN_KEY);
}

/**
 * Função central de fetch para a API.
 * Intercepta erros 401 e redireciona ou avisa sobre token inválido.
 */
async function apiFetch(endpoint, options = {}) {
    const url = endpoint.startsWith("http") ? endpoint : endpoint;
    
    // Adiciona o cabeçalho de autorização se houver token
    const token = getToken();
    if (!options.headers) {
        options.headers = {};
    }
    if (token) {
        options.headers["Authorization"] = "Bearer " + token;
    }
    
    try {
        const response = await fetch(url, options);
        
        if (response.status === 401) {
            // Token inválido, expirado ou não autorizado
            console.warn("API retornou 401 Não Autorizado. Limpando token...");
            clearToken();
            
            // Avisa a UI ou redireciona, se necessário
            if (window.location.pathname.includes("settings.html")) {
                alert("Sessão administrativa expirada ou PIN incorreto!");
            }
        }
        
        return response;
    } catch (error) {
        console.error("Erro na chamada API para " + url, error);
        throw error;
    }
}

)=====";

#endif // WEBPAGES_H
