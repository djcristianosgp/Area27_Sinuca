#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <Arduino.h>

// ==========================================
// style.css
// ==========================================
const char CSS_STYLE[] PROGMEM = R"rawliteral(
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
* { box-sizing: border-box; margin: 0; padding: 0; }
html, body { background-color: var(--bg-color); color: var(--text-main); font-family: var(--font-family); font-size: 16px; line-height: 1.5; min-height: 100vh; overflow-x: hidden; }
.app-container { max-width: 480px; margin: 0 auto; padding: 16px; min-height: 100vh; display: flex; flex-direction: column; }
.header { display: flex; align-items: center; justify-content: space-between; padding-bottom: 16px; margin-bottom: 20px; border-bottom: 1px solid var(--border-color); }
.header-title { display: flex; align-items: center; gap: 10px; }
.header h1 { font-size: 1.4rem; font-weight: 700; color: var(--text-main); letter-spacing: -0.5px; }
.logo-badge { background: linear-gradient(135deg, var(--primary), var(--secondary)); width: 38px; height: 38px; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 1.2rem; box-shadow: 0 4px 10px rgba(59, 147, 193, 0.3); }
.back-btn { background: var(--card-bg); color: var(--text-main); border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 8px 14px; text-decoration: none; font-size: 0.9rem; font-weight: 600; display: inline-flex; align-items: center; gap: 6px; transition: var(--transition); }
.card-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 14px; }
.card-link { text-decoration: none; color: inherit; display: block; }
.card { background: var(--card-bg); border: 1px solid var(--border-color); border-radius: var(--radius); padding: 20px 16px; transition: var(--transition); box-shadow: 0 4px 12px rgba(0,0,0,0.2); }
.card-interactive { display: flex; flex-direction: column; align-items: center; justify-content: center; text-align: center; height: 100%; min-height: 120px; cursor: pointer; }
.card-icon { font-size: 2.2rem; margin-bottom: 8px; }
.card-title { font-size: 1.05rem; font-weight: 600; color: var(--text-main); }
.form-group { margin-bottom: 16px; }
.form-label { display: block; font-size: 0.9rem; color: var(--text-muted); margin-bottom: 6px; font-weight: 500; }
.form-input, .form-select { width: 100%; height: 48px; background: #161616; border: 1px solid var(--border-color); border-radius: var(--radius-sm); color: var(--text-main); padding: 0 14px; font-size: 1rem; font-family: inherit; outline: none; transition: var(--transition); }
.btn { width: 100%; height: 50px; border: none; border-radius: var(--radius-sm); font-size: 1rem; font-weight: 600; font-family: inherit; cursor: pointer; display: inline-flex; align-items: center; justify-content: center; gap: 8px; transition: var(--transition); }
.btn-primary { background: var(--primary); color: var(--text-main); box-shadow: 0 4px 12px rgba(59, 147, 193, 0.3); }
.btn-secondary { background: var(--secondary); color: var(--text-main); }
.btn-danger { background: var(--error-color); color: var(--text-main); }
.item-list { display: flex; flex-direction: column; gap: 10px; }
.list-item { background: var(--card-bg); border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 14px 16px; display: flex; align-items: center; justify-content: space-between; }
.badge-elo { background: rgba(59, 147, 193, 0.15); color: var(--primary); font-weight: 700; font-size: 0.85rem; padding: 4px 8px; border-radius: 6px; border: 1px solid rgba(59, 147, 193, 0.3); display: inline-block; }
.ranking-card { background: var(--card-bg); border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 14px; display: flex; align-items: center; gap: 12px; }
.ranking-rank { font-size: 1.2rem; font-weight: 800; width: 36px; height: 36px; border-radius: 50%; display: flex; align-items: center; justify-content: center; background: #252525; color: var(--text-muted); }
.rank-1 { background: rgba(255, 215, 0, 0.15); color: var(--gold); border: 1px solid rgba(255, 215, 0, 0.4); }
.rank-2 { background: rgba(192, 192, 192, 0.15); color: var(--silver); border: 1px solid rgba(192, 192, 192, 0.4); }
.rank-3 { background: rgba(205, 127, 50, 0.15); color: var(--bronze); border: 1px solid rgba(205, 127, 50, 0.4); }
.toast { position: fixed; bottom: 24px; left: 50%; transform: translateX(-50%) translateY(100px); max-width: 440px; width: 90%; padding: 14px 18px; border-radius: var(--radius-sm); color: #FFF; font-weight: 600; z-index: 1000; }
.toast.show { transform: translateX(-50%) translateY(0); }
.toast-success { background: var(--success-color); }
.toast-error { background: var(--error-color); }
.empty-state { text-align: center; padding: 30px 16px; color: var(--text-muted); background: var(--card-bg); border: 1px dashed var(--border-color); border-radius: var(--radius-sm); }
.footer { margin-top: auto; padding-top: 24px; text-align: center; font-size: 0.8rem; color: var(--text-muted); }
.hidden { display: none !important; }
.user-badge { display: inline-flex; align-items: center; gap: 8px; background: rgba(59, 147, 193, 0.15); border: 1px solid rgba(59, 147, 193, 0.3); color: var(--primary); padding: 6px 12px; border-radius: 20px; font-size: 0.85rem; font-weight: 600; }
.modal-overlay { position: fixed; top: 0; left: 0; right: 0; bottom: 0; background: rgba(0,0,0,0.75); display: flex; align-items: center; justify-content: center; z-index: 999; padding: 16px; }
.modal-card { background: var(--card-bg); border: 1px solid var(--border-color); border-radius: var(--radius); padding: 24px; max-width: 400px; width: 100%; box-shadow: 0 8px 30px rgba(0,0,0,0.5); }
.badge-card { background: rgba(22, 22, 22, 0.8); border: 1px solid var(--border-color); border-radius: 8px; padding: 10px; text-align: center; display: flex; flex-direction: column; align-items: center; }
.badge-card.unlocked { border-color: var(--gold); background: linear-gradient(135deg, #1e1e1e, rgba(255,215,0,0.1)); }
.badge-card .badge-icon { font-size: 1.8rem; margin-bottom: 4px; }
.badge-card .badge-title { font-size: 0.75rem; font-weight: 700; color: var(--text-main); }
.recent-dot { width: 28px; height: 28px; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 0.75rem; font-weight: 800; }
.recent-dot.win { background: #2e7d32; color: #fff; }
.recent-dot.loss { background: #c62828; color: #fff; }
)rawliteral";

// ==========================================
// app.js
// ==========================================
const char JS_APP[] PROGMEM = R"rawliteral(
function getCurrentUser() { try { const d = localStorage.getItem('area27_user'); return d ? JSON.parse(d) : null; } catch (e) { return null; } }
function setCurrentUser(u) { if (u) localStorage.setItem('area27_user', JSON.stringify(u)); else localStorage.removeItem('area27_user'); renderUserHeaderStatus(); }
function logoutUser() { localStorage.removeItem('area27_user'); showToast('Sessão encerrada.', 'success'); setTimeout(() => window.location.reload(), 500); }
function renderUserHeaderStatus() {
  const container = document.getElementById('user-status-container');
  if (!container) return;
  const user = getCurrentUser();
  if (user) {
    container.innerHTML = `<div class="user-badge"><a href="profile.html?id=${user.id}" style="color:inherit;text-decoration:none;">👤 ${escapeHtml(user.nome)}</a><button onclick="logoutUser()">✕</button></div>`;
  } else {
    container.innerHTML = `<a href="players.html" class="user-badge" style="text-decoration:none;">🔑 Entrar</a>`;
  }
}
const API = {
  async request(ep, opts = {}) {
    try {
      const res = await fetch(ep, { headers: { 'Content-Type': 'application/json', ...(opts.headers || {}) }, ...opts });
      const data = await res.json();
      if (!res.ok) throw new Error(data.error || `Erro: ${res.status}`);
      return data;
    } catch (err) {
      showToast(err.message || 'Falha de conexão', 'error');
      throw err;
    }
  },
  getPlayers() { return this.request('/players'); },
  registerPlayer(d) { return this.request('/players', { method: 'POST', body: JSON.stringify(d) }); },
  loginPlayer(d) { return this.request('/players/login', { method: 'POST', body: JSON.stringify(d) }); },
  deletePlayer(id) { return this.request('/players/delete', { method: 'POST', body: JSON.stringify({ id }) }); },
  clearPlayers() { return this.request('/players/clear', { method: 'POST' }); },
  resetRanking() { return this.request('/ranking/reset', { method: 'POST' }); },
  getRanking() { return this.request('/ranking'); },
  authSettingsPin(d) { return this.request('/settings/auth', { method: 'POST', body: JSON.stringify(d) }); },
  createMatch(d) { return this.request('/match/create', { method: 'POST', body: JSON.stringify(d) }); },
  joinMatch(d) { return this.request('/match/join', { method: 'POST', body: JSON.stringify(d) }); },
  respondMatchInvite(d) { return this.request('/match/respond', { method: 'POST', body: JSON.stringify(d) }); },
  getActiveMatch() { return this.request('/match/active'); },
  finishMatch(d) { return this.request('/match/finish', { method: 'POST', body: JSON.stringify(d) }); },
  cancelMatch() { return this.request('/match/cancel', { method: 'POST' }); },
  resetWifi() { return this.request('/wifi/reset', { method: 'POST' }); },
  getTV() { return this.request('/api/v1/tv'); },
  getHistory() { return this.request('/api/v1/history'); },
  getStats() { return this.request('/api/v1/stats'); },
  getSeasons() { return this.request('/api/v1/seasons'); },
  resetSeason() { return this.request('/api/v1/seasons/reset', { method: 'POST' }); },
  getChampionship() { return this.request('/api/v1/championships'); },
  createChampionship(d) { return this.request('/api/v1/championships', { method: 'POST', body: JSON.stringify(d) }); },
  exportBackup() { return this.request('/api/v1/backup/export'); },
  importBackup(d) { return this.request('/api/v1/backup/import', { method: 'POST', body: JSON.stringify(d) }); }
};

function showToast(msg, type = 'success') {
  let toast = document.getElementById('toast');
  if (!toast) {
    toast = document.createElement('div');
    toast.id = 'toast';
    toast.className = 'toast';
    document.body.appendChild(toast);
  }
  toast.className = `toast toast-${type} show`;
  toast.textContent = msg;
  clearTimeout(toast._timer);
  toast._timer = setTimeout(() => toast.classList.remove('show'), 3500);
}
function escapeHtml(str) {
  if (!str) return '';
  return String(str).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}
document.addEventListener('DOMContentLoaded', () => { renderUserHeaderStatus(); });
)rawliteral";

// ==========================================
// index.html
// ==========================================
const char HTML_INDEX[] PROGMEM = R"rawliteral(
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
      <a href="match.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🎱</div><div class="card-title">Nova Partida</div></div></a>
      <a href="tv.html" class="card-link"><div class="card card-interactive" style="border: 1px solid var(--primary); background: linear-gradient(135deg, #1e293b, #0f172a);"><div class="card-icon">📺</div><div class="card-title" style="color: #38bdf8;">Painel TV</div></div></a>
      <a href="players.html" class="card-link"><div class="card card-interactive"><div class="card-icon">👥</div><div class="card-title">Jogadores</div></div></a>
      <a href="ranking.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🏆</div><div class="card-title">Ranking</div></div></a>
      <a href="hall.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🏛️</div><div class="card-title">Hall da Fama</div></div></a>
      <a href="championship.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🎯</div><div class="card-title">Campeonato</div></div></a>
      <a href="settings.html" class="card-link"><div class="card card-interactive"><div class="card-icon">⚙️</div><div class="card-title">Configurações</div></div></a>
      <a href="about.html" class="card-link"><div class="card card-interactive"><div class="card-icon">ℹ️</div><div class="card-title">Sobre</div></div></a>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// players.html
// ==========================================
const char HTML_PLAYERS[] PROGMEM = R"rawliteral(
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
      <div class="header-title"><div class="logo-badge">👥</div><h1>Jogadores</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="section-header"><h2 class="section-title">Lista de Jogadores</h2></div>
      <div id="players-container" class="item-list"><div class="empty-state">Carregando jogadores...</div></div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// match.html
// ==========================================
const char HTML_MATCH[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Partida - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title"><div class="logo-badge">🎱</div><h1>Partida</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main><div id="match-arena"><div class="empty-state">Carregando dados da partida...</div></div></main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// ranking.html
// ==========================================
const char HTML_RANKING[] PROGMEM = R"rawliteral(
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
      <div class="header-title"><div class="logo-badge">🏆</div><h1>Ranking</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main><div id="ranking-container" class="ranking-list"><div class="empty-state">Carregando classificação...</div></div></main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// settings.html
// ==========================================
const char HTML_SETTINGS[] PROGMEM = R"rawliteral(
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
      <div class="header-title"><div class="logo-badge">⚙️</div><h1>Configurações</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div id="admin-pin-card" class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--gold);">🔒 Acesso Restrito</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">Informe o PIN de Administrador (0000) para acessar as configurações do sistema.</p>
        <form id="form-admin-pin">
          <div class="form-group"><input type="password" id="admin-pin-input" class="form-input" placeholder="0000" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" style="text-align: center; font-size: 1.5rem; letter-spacing: 6px;" required></div>
          <button type="submit" class="btn btn-primary">🔓 Acessar Configurações</button>
        </form>
      </div>
      <div id="settings-content" class="hidden">
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--primary);">💾 Backup do Sistema</h2>
          <button id="btn-export-backup" class="btn btn-primary">📥 Exportar Dados (backup.json)</button>
        </div>
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">📶 Rede Wi-Fi</h2>
          <button id="btn-reset-wifi" class="btn btn-secondary">Trocar de Rede Wi-Fi</button>
        </div>
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🏆 Zerar Ranking</h2>
          <button id="btn-reset-ranking" class="btn btn-secondary" style="background: #e65100;">Zerar Estatísticas do Ranking</button>
        </div>
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🗑️ Gerenciar Jogadores</h2>
          <button id="btn-clear-players" class="btn btn-danger">Excluir Todos os Jogadores</button>
        </div>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// about.html
// ==========================================
const char HTML_ABOUT[] PROGMEM = R"rawliteral(
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
      <div class="header-title"><div class="logo-badge">ℹ️</div><h1>Sobre o Sistema</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card">
        <h2 style="font-size: 1.2rem; color: var(--primary); margin-bottom: 10px;">🎱 Área27 Sinuca v2.0</h2>
        <p style="font-size: 0.9rem; color: var(--text-muted); margin-bottom: 14px;">Sistema completo de gerenciamento de salão de sinuca rodando no microcontrolador ESP8266 com TV Dashboard, Perfil, Ranking ELO, Medalhas e Torneios.</p>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// wifi.html (Captive Portal)
// ==========================================
const char HTML_WIFI_CONFIG[] PROGMEM = R"rawliteral(
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
)rawliteral";

// ==========================================
// tv.html (TV Dashboard)
// ==========================================
const char HTML_TV[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>TV Dashboard - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body style="background:#0b0f19; color:#fff; padding:20px;">
  <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:20px; background:#1e293b; padding:16px 24px; border-radius:14px;">
    <div style="display:flex; align-items:center; gap:14px;"><div style="font-size:2rem;">🎱</div><h1>ÁREA27 SINUCA - TV DASHBOARD</h1></div>
    <div id="tv-clock" style="font-size:1.8rem; font-family:monospace; color:#38bdf8;">00:00:00</div>
  </div>
  <div style="display:grid; grid-template-columns:1.2fr 1fr; gap:20px;">
    <div>
      <div class="card" style="margin-bottom:20px; background:#1e1b4b; border:2px solid #6366f1;">
        <h2 style="color:#fbbf24; margin-bottom:10px;">🎱 PARTIDA ATUAL NA MESA</h2>
        <div id="tv-live-content"><div style="text-align:center; color:#94a3b8; padding:20px;">Aguardando partida...</div></div>
      </div>
      <div class="card">
        <h2 style="color:#fbbf24; margin-bottom:10px;">📜 ÚLTIMAS PARTIDAS</h2>
        <div id="tv-history-list"><div style="text-align:center; color:#94a3b8;">Carregando histórico...</div></div>
      </div>
    </div>
    <div>
      <div class="card">
        <h2 style="color:#fbbf24; margin-bottom:10px;">🏆 CLASSIFICAÇÃO GERAL</h2>
        <table style="width:100%; border-collapse:collapse;">
          <tbody id="tv-ranking-body"><tr><td style="text-align:center; color:#94a3b8;">Carregando ranking...</td></tr></tbody>
        </table>
      </div>
    </div>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// profile.html (Perfil do Jogador)
// ==========================================
const char HTML_PROFILE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Perfil - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title"><div class="logo-badge">👤</div><h1>Perfil do Jogador</h1></div>
      <a href="players.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="text-align:center; margin-bottom:16px;">
        <h2 id="profile-name">Carregando...</h2>
        <p id="profile-phone" style="color:var(--text-muted);"></p>
        <button id="btn-show-qr" class="btn btn-secondary" style="width:auto; margin:10px auto;">📱 Exibir QR Code</button>
      </div>
      <div class="card-grid" style="grid-template-columns:1fr 1fr; margin-bottom:16px;">
        <div class="card" style="text-align:center;"><div style="font-size:0.8rem; color:var(--text-muted);">ELO</div><div id="profile-elo" style="font-size:1.8rem; font-weight:800; color:var(--gold);">-</div></div>
        <div class="card" style="text-align:center;"><div style="font-size:0.8rem; color:var(--text-muted);">Aproveitamento</div><div id="profile-winrate" style="font-size:1.8rem; font-weight:800; color:#4ade80;">-</div></div>
      </div>
      <div class="card" style="margin-bottom:16px;">
        <h3>Últimos Jogos</h3>
        <div id="profile-recent-dots" style="display:flex; gap:6px; margin-top:8px;">-</div>
      </div>
      <div class="card">
        <h3>🏅 Medalhas</h3>
        <div id="profile-badges-list" style="display:grid; grid-template-columns:repeat(2, 1fr); gap:8px; margin-top:8px;"></div>
      </div>
    </main>
    <div id="modal-qr" class="modal-overlay hidden">
      <div class="modal-card" style="text-align:center;">
        <h3>📱 QR Code de Acesso</h3>
        <div id="qr-container" style="display:flex; justify-content:center; padding:12px; background:#fff; border-radius:10px; margin:12px 0;"></div>
        <button id="btn-close-qr" class="btn btn-secondary">Fechar</button>
      </div>
    </div>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// hall.html (Hall da Fama)
// ==========================================
const char HTML_HALL[] PROGMEM = R"rawliteral(
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
      <div class="header-title"><div class="logo-badge">🏛️</div><h1>Hall da Fama</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="margin-bottom:14px; border-left:4px solid var(--gold);">
        <div style="font-size:0.8rem; color:var(--text-muted);">Maior ELO</div>
        <div id="hall-peak-elo" style="font-size:1.1rem; font-weight:700;">Carregando...</div>
      </div>
      <div class="card" style="margin-bottom:14px; border-left:4px solid #ef4444;">
        <div style="font-size:0.8rem; color:var(--text-muted);">Maior Sequência</div>
        <div id="hall-max-streak" style="font-size:1.1rem; font-weight:700;">Carregando...</div>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// championship.html (Campeonato)
// ==========================================
const char HTML_CHAMPIONSHIP[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Campeonato - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title"><div class="logo-badge">🎯</div><h1>Modo Campeonato</h1></div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div id="champ-setup-card" class="card">
        <h2>Criar Campeonato (16/8/4 Jogadores)</h2>
        <form id="form-create-champ">
          <div class="form-group"><label class="form-label">Nome do Campeonato</label><input type="text" id="champ-name" class="form-input" required></div>
          <button type="submit" class="btn btn-primary">🎲 Sorteio e Gerar Chaveamento</button>
        </form>
      </div>
      <div id="champ-active-card" class="card hidden">
        <h2 id="active-champ-title">Torneio</h2>
        <div id="bracket-view" style="display:flex; gap:10px; overflow-x:auto; margin-top:10px;"></div>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

#endif
