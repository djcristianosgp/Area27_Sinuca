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

.app-container {
  max-width: 480px;
  margin: 0 auto;
  padding: 16px;
  min-height: 100vh;
  display: flex;
  flex-direction: column;
}

.header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding-bottom: 16px;
  margin-bottom: 20px;
  border-bottom: 1px solid var(--border-color);
}

.header-title { display: flex; align-items: center; gap: 10px; }
.header h1 { font-size: 1.4rem; font-weight: 700; color: var(--text-main); letter-spacing: -0.5px; }

.logo-badge {
  background: linear-gradient(135deg, var(--primary), var(--secondary));
  width: 38px; height: 38px;
  border-radius: 50%;
  display: flex; align-items: center; justify-content: center;
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
  display: inline-flex; align-items: center; gap: 6px;
  transition: var(--transition);
}

.back-btn:active { transform: scale(0.96); background: var(--border-color); }

.card-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 14px; }
.card-link { text-decoration: none; color: inherit; display: block; }

.card {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius);
  padding: 20px 16px;
  transition: var(--transition);
  box-shadow: 0 4px 12px rgba(0,0,0,0.2);
}

.card-interactive {
  display: flex; flex-direction: column; align-items: center; justify-content: center;
  text-align: center; height: 100%; min-height: 120px; cursor: pointer;
}

.card-interactive:active { transform: scale(0.97); background: var(--card-hover); border-color: var(--primary); }
.card-icon { font-size: 2.2rem; margin-bottom: 8px; }
.card-title { font-size: 1.05rem; font-weight: 600; color: var(--text-main); }

.form-group { margin-bottom: 16px; }
.form-label { display: block; font-size: 0.9rem; color: var(--text-muted); margin-bottom: 6px; font-weight: 500; }

.form-input, .form-select {
  width: 100%; height: 48px;
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

.btn {
  width: 100%; height: 50px; border: none; border-radius: var(--radius-sm);
  font-size: 1rem; font-weight: 600; font-family: inherit; cursor: pointer;
  display: inline-flex; align-items: center; justify-content: center; gap: 8px;
  transition: var(--transition);
}

.btn-primary { background: var(--primary); color: var(--text-main); box-shadow: 0 4px 12px rgba(59, 147, 193, 0.3); }
.btn-primary:active { background: var(--primary-hover); transform: scale(0.98); }

.btn-secondary { background: var(--secondary); color: var(--text-main); }
.btn-secondary:active { background: var(--secondary-hover); transform: scale(0.98); }

.btn-danger { background: #c62828; color: var(--text-main); }
.btn-danger:active { background: #b71c1c; transform: scale(0.98); }

.section-header { display: flex; justify-content: space-between; align-items: center; margin: 20px 0 12px 0; }
.section-title { font-size: 1.1rem; font-weight: 600; color: var(--text-main); }
.item-list { display: flex; flex-direction: column; gap: 10px; }

.list-item {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 14px 16px;
  display: flex; align-items: center; justify-content: space-between;
}

.player-info { display: flex; flex-direction: column; }
.player-name { font-weight: 600; font-size: 1rem; }
.player-phone { font-size: 0.85rem; color: var(--text-muted); }
.player-stats { text-align: right; }

.badge-elo {
  background: rgba(59, 147, 193, 0.15);
  color: var(--primary);
  font-weight: 700; font-size: 0.85rem;
  padding: 4px 8px; border-radius: 6px;
  border: 1px solid rgba(59, 147, 193, 0.3);
  display: inline-block; margin-bottom: 4px;
}

.record { font-size: 0.8rem; color: var(--text-muted); }
.ranking-list { display: flex; flex-direction: column; gap: 10px; }

.ranking-card {
  background: var(--card-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--radius-sm);
  padding: 14px;
  display: flex; align-items: center; gap: 12px;
}

.ranking-rank {
  font-size: 1.2rem; font-weight: 800;
  width: 36px; height: 36px; border-radius: 50%;
  display: flex; align-items: center; justify-content: center;
  background: #252525; color: var(--text-muted); flex-shrink: 0;
}

.rank-1 { background: rgba(255, 215, 0, 0.15); color: var(--gold); border: 1px solid rgba(255, 215, 0, 0.4); }
.rank-2 { background: rgba(192, 192, 192, 0.15); color: var(--silver); border: 1px solid rgba(192, 192, 192, 0.4); }
.rank-3 { background: rgba(205, 127, 50, 0.15); color: var(--bronze); border: 1px solid rgba(205, 127, 50, 0.4); }

.ranking-card.top-1 { border-color: rgba(255, 215, 0, 0.5); background: linear-gradient(135deg, #1E1E1E 70%, rgba(255, 215, 0, 0.08)); }
.ranking-card.top-2 { border-color: rgba(192, 192, 192, 0.4); }
.ranking-card.top-3 { border-color: rgba(205, 127, 50, 0.4); }

.ranking-details { flex: 1; }

.toast {
  position: fixed; bottom: 24px; left: 50%;
  transform: translateX(-50%) translateY(100px);
  max-width: 440px; width: 90%;
  padding: 14px 18px; border-radius: var(--radius-sm);
  color: #FFF; font-weight: 600; font-size: 0.95rem;
  box-shadow: 0 6px 20px rgba(0,0,0,0.5);
  transition: transform 0.3s cubic-bezier(0.175, 0.885, 0.32, 1.275);
  z-index: 1000; display: flex; align-items: center; gap: 10px;
}

.toast.show { transform: translateX(-50%) translateY(0); }
.toast-success { background: var(--success-color); }
.toast-error { background: var(--error-color); }

.empty-state {
  text-align: center; padding: 30px 16px; color: var(--text-muted);
  background: var(--card-bg); border: 1px dashed var(--border-color); border-radius: var(--radius-sm);
}

.footer { margin-top: auto; padding-top: 24px; text-align: center; font-size: 0.8rem; color: var(--text-muted); }
)rawliteral";

// ==========================================
// app.js
// ==========================================
const char JS_APP[] PROGMEM = R"rawliteral(
const API = {
  async request(endpoint, options = {}) {
    try {
      const response = await fetch(endpoint, {
        headers: { 'Content-Type': 'application/json', ...(options.headers || {}) },
        ...options
      });
      if (!response.ok) throw new Error(`Erro: ${response.status}`);
      return await response.json();
    } catch (err) {
      console.error(`API Error [${endpoint}]:`, err);
      showToast(err.message || 'Falha na requisição', 'error');
      throw err;
    }
  },
  getPlayers() { return this.request('/players'); },
  addPlayer(data) { return this.request('/players', { method: 'POST', body: JSON.stringify(data) }); },
  deletePlayer(id) { return this.request('/players/delete', { method: 'POST', body: JSON.stringify({ id }) }); },
  clearPlayers() { return this.request('/players/clear', { method: 'POST' }); },
  resetRanking() { return this.request('/ranking/reset', { method: 'POST' }); },
  getRanking() { return this.request('/ranking'); },
  registerMatch(data) { return this.request('/match', { method: 'POST', body: JSON.stringify(data) }); },
  resetWifi() { return this.request('/wifi/reset', { method: 'POST' }); }
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
  toast._timer = setTimeout(() => { toast.classList.remove('show'); }, 3500);
}

async function initPlayersPage() {
  const form = document.getElementById('form-player');
  const playerList = document.getElementById('players-container');

  async function loadPlayers() {
    try {
      const players = await API.getPlayers();
      if (!players || players.length === 0) {
        playerList.innerHTML = `<div class="empty-state">Nenhum jogador cadastrado ainda.</div>`;
        return;
      }
      playerList.innerHTML = players.map(p => `
        <div class="list-item">
          <div class="player-info">
            <span class="player-name">${escapeHtml(p.nome)}</span>
            <span class="player-phone">${escapeHtml(p.telefone || '-')}</span>
          </div>
          <div style="display: flex; align-items: center; gap: 10px;">
            <div class="player-stats">
              <span class="badge-elo">${p.elo || 1000} ELO</span>
              <div class="record">${p.vitorias || 0}V / ${p.derrotas || 0}D</div>
            </div>
            <button onclick="handleDeleteSinglePlayer(${p.id}, '${escapeHtml(p.nome)}')" style="background: none; border: none; font-size: 1.2rem; cursor: pointer;" title="Excluir Jogador">🗑️</button>
          </div>
        </div>
      `).join('');
    } catch (err) {
      playerList.innerHTML = `<div class="empty-state">Erro ao carregar jogadores.</div>`;
    }
  }

  window.handleDeleteSinglePlayer = async (id, nome) => {
    if (confirm(`Deseja realmente excluir o jogador "${nome}"?`)) {
      try {
        await API.deletePlayer(id);
        showToast(`Jogador "${nome}" excluído com sucesso!`, 'success');
        await loadPlayers();
      } catch (e) {}
    }
  };

  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nomeInput = document.getElementById('nome');
      const telInput = document.getElementById('telefone');
      const nome = nomeInput.value.trim();
      const telefone = telInput.value.trim();

      if (!nome) return showToast('Informe o nome', 'error');

      const submitBtn = form.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.addPlayer({ nome, telefone });
        showToast('Jogador cadastrado com sucesso!', 'success');
        nomeInput.value = '';
        telInput.value = '';
        await loadPlayers();
      } catch (err) {}
      finally { submitBtn.disabled = false; }
    });
  }

  if (playerList) loadPlayers();
}

async function initMatchPage() {
  const formMatch = document.getElementById('form-match');
  const formQuickPlayer = document.getElementById('form-quick-player');
  const selectA = document.getElementById('playerA');
  const selectB = document.getElementById('playerB');
  const selectWinner = document.getElementById('winner');
  let playersCache = [];

  function updateWinnerOptions() {
    const valA = selectA.value;
    const valB = selectB.value;
    selectWinner.innerHTML = '<option value="">Selecione o Vencedor</option>';

    if (!valA || !valB) { selectWinner.disabled = true; return; }
    if (valA === valB) { showToast('Escolha dois jogadores diferentes', 'error'); selectWinner.disabled = true; return; }

    selectWinner.disabled = false;
    const playerObjA = playersCache.find(p => String(p.id) === String(valA));
    const playerObjB = playersCache.find(p => String(p.id) === String(valB));

    if (playerObjA) {
      const optA = document.createElement('option');
      optA.value = playerObjA.id; optA.textContent = playerObjA.nome;
      selectWinner.appendChild(optA);
    }
    if (playerObjB) {
      const optB = document.createElement('option');
      optB.value = playerObjB.id; optB.textContent = playerObjB.nome;
      selectWinner.appendChild(optB);
    }
  }

  async function loadPlayersDropdown() {
    try {
      const valA = selectA ? selectA.value : '';
      const valB = selectB ? selectB.value : '';

      playersCache = await API.getPlayers();
      if (selectA && selectB) {
        selectA.innerHTML = '<option value="">Selecione o Jogador A</option>';
        selectB.innerHTML = '<option value="">Selecione o Jogador B</option>';

        playersCache.forEach(p => {
          const opt1 = document.createElement('option');
          opt1.value = p.id; opt1.textContent = p.nome;
          selectA.appendChild(opt1);

          const opt2 = document.createElement('option');
          opt2.value = p.id; opt2.textContent = p.nome;
          selectB.appendChild(opt2);
        });

        if (valA) selectA.value = valA;
        if (valB) selectB.value = valB;
        updateWinnerOptions();
      }
    } catch (err) {
      showToast('Erro ao carregar jogadores', 'error');
    }
  }

  if (formQuickPlayer) {
    formQuickPlayer.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nomeInput = document.getElementById('quick-nome');
      const telInput = document.getElementById('quick-telefone');
      const nome = nomeInput.value.trim();
      const telefone = telInput.value.trim();

      if (!nome) return showToast('Informe o nome do jogador', 'error');

      const submitBtn = formQuickPlayer.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        const res = await API.addPlayer({ nome, telefone });
        showToast(`Jogador '${nome}' cadastrado!`, 'success');
        nomeInput.value = '';
        telInput.value = '';

        await loadPlayersDropdown();

        if (res && res.id) {
          if (!selectA.value) selectA.value = res.id;
          else if (!selectB.value && selectA.value != res.id) selectB.value = res.id;
          updateWinnerOptions();
        }
      } catch (err) {}
      finally { submitBtn.disabled = false; }
    });
  }

  if (selectA && selectB) {
    selectA.addEventListener('change', updateWinnerOptions);
    selectB.addEventListener('change', updateWinnerOptions);
  }

  if (formMatch) {
    formMatch.addEventListener('submit', async (e) => {
      e.preventDefault();
      const playerA = Number(selectA.value);
      const playerB = Number(selectB.value);
      const winner = Number(selectWinner.value);

      if (!playerA || !playerB) return showToast('Selecione os dois jogadores', 'error');
      if (playerA === playerB) return showToast('Jogadores devem ser diferentes', 'error');
      if (!winner) return showToast('Selecione o vencedor', 'error');

      const submitBtn = formMatch.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.registerMatch({ playerA, playerB, winner });
        showToast('Partida registrada com sucesso.', 'success');
        formMatch.reset();
        selectWinner.disabled = true;
      } catch (err) {}
      finally { submitBtn.disabled = false; }
    });

    loadPlayersDropdown();
  }
}

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
            <div class="player-name">${escapeHtml(p.nome)}</div>
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

function initSettingsPage() {
  const resetWifiBtn = document.getElementById('btn-reset-wifi');
  const resetRankingBtn = document.getElementById('btn-reset-ranking');
  const clearPlayersBtn = document.getElementById('btn-clear-players');

  if (resetWifiBtn) {
    resetWifiBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente resetar a rede Wi-Fi? O ESP8266 reiniciará no modo Ponto de Acesso (Area27-Sinuca-Config).')) {
        try {
          await API.resetWifi();
          showToast('Wi-Fi resetado! Reiniciando...', 'success');
        } catch (e) {}
      }
    });
  }

  if (resetRankingBtn) {
    resetRankingBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente zerar o ranking? Todas as vitórias, derrotas e ELO voltarão a 1000.')) {
        try {
          await API.resetRanking();
          showToast('Estatísticas do ranking zeradas com sucesso!', 'success');
        } catch (e) {}
      }
    });
  }

  if (clearPlayersBtn) {
    clearPlayersBtn.addEventListener('click', async () => {
      if (confirm('ATENÇÃO: Deseja EXCLUIR TODOS OS JOGADORES? Esta ação é irreversível!')) {
        try {
          await API.clearPlayers();
          showToast('Todos os jogadores foram excluídos!', 'success');
        } catch (e) {}
      }
    });
  }
}

function escapeHtml(str) {
  if (!str) return '';
  return String(str)
    .replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;').replace(/'/g, '&#039;');
}

document.addEventListener('DOMContentLoaded', () => {
  if (document.getElementById('form-player')) initPlayersPage();
  if (document.getElementById('form-match') || document.getElementById('form-quick-player')) initMatchPage();
  if (document.getElementById('ranking-container')) initRankingPage();
  if (document.getElementById('btn-reset-wifi') || document.getElementById('btn-clear-players')) initSettingsPage();
});
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
    </header>
    <main class="card-grid">
      <a href="match.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">🎱</div>
          <div class="card-title">Nova Partida</div>
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
      <a href="settings.html" class="card-link">
        <div class="card card-interactive">
          <div class="card-icon">⚙️</div>
          <div class="card-title">Configurações</div>
        </div>
      </a>
      <a href="about.html" class="card-link" style="grid-column: span 2;">
        <div class="card card-interactive" style="min-height: 80px; flex-direction: row; gap: 12px;">
          <div class="card-icon" style="margin-bottom: 0; font-size: 1.6rem;">ℹ️</div>
          <div class="card-title">Sobre o Sistema</div>
        </div>
      </a>
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
      <div class="header-title">
        <div class="logo-badge">👥</div>
        <h1>Jogadores</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="margin-bottom: 20px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 14px;">Novo Jogador</h2>
        <form id="form-player">
          <div class="form-group">
            <label class="form-label" for="nome">Nome</label>
            <input type="text" id="nome" class="form-input" placeholder="Ex: João" required>
          </div>
          <div class="form-group">
            <label class="form-label" for="telefone">Telefone</label>
            <input type="tel" id="telefone" class="form-input" placeholder="Ex: 27999999999">
          </div>
          <button type="submit" class="btn btn-primary">Salvar Jogador</button>
        </form>
      </div>
      <div class="section-header">
        <h2 class="section-title">Lista de Jogadores</h2>
      </div>
      <div id="players-container" class="item-list">
        <div class="empty-state">Carregando jogadores...</div>
      </div>
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
  <title>Nova Partida - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">🎱</div>
        <h1>Nova Partida</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="margin-bottom: 20px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 14px;">👤 Cadastrar Jogador Rápido</h2>
        <form id="form-quick-player">
          <div class="form-group">
            <label class="form-label" for="quick-nome">Nome do Jogador</label>
            <input type="text" id="quick-nome" class="form-input" placeholder="Ex: Cristiano" required>
          </div>
          <div class="form-group">
            <label class="form-label" for="quick-telefone">Telefone (opcional)</label>
            <input type="tel" id="quick-telefone" class="form-input" placeholder="Ex: 27999999999">
          </div>
          <button type="submit" class="btn btn-secondary">➕ Cadastrar Jogador</button>
        </form>
      </div>

      <div class="card">
        <h2 style="font-size: 1.1rem; margin-bottom: 14px;">🏆 Seleção da Partida</h2>
        <form id="form-match">
          <div class="form-group">
            <label class="form-label" for="playerA">Jogador A</label>
            <select id="playerA" class="form-select" required>
              <option value="">Carregando jogadores...</option>
            </select>
          </div>
          <div class="form-group">
            <label class="form-label" for="playerB">Jogador B</label>
            <select id="playerB" class="form-select" required>
              <option value="">Carregando jogadores...</option>
            </select>
          </div>
          <div class="form-group">
            <label class="form-label" for="winner">Vencedor</label>
            <select id="winner" class="form-select" disabled required>
              <option value="">Selecione Jogador A e B primeiro</option>
            </select>
          </div>
          <button type="submit" class="btn btn-primary">Registrar Partida</button>
        </form>
      </div>
    </main>
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
      <div class="header-title">
        <div class="logo-badge">⚙️</div>
        <h1>Configurações</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px;">📶 Rede Wi-Fi</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
          Reinicia o ESP8266 no modo Ponto de Acesso (Area27-Sinuca-Config) para conectar a outro roteador.
        </p>
        <button id="btn-reset-wifi" class="btn btn-secondary">Trocar de Rede Wi-Fi</button>
      </div>

      <div class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🏆 Zerar Ranking</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
          Reseta todas as estatísticas (vitórias, derrotas e ELO para 1000), mantendo o cadastro dos jogadores.
        </p>
        <button id="btn-reset-ranking" class="btn btn-secondary" style="background: #e65100;">Zerar Estatísticas do Ranking</button>
      </div>

      <div class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🗑️ Gerenciar Jogadores</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;">
          Apaga permanentemente todos os jogadores cadastrados do sistema.
        </p>
        <button id="btn-clear-players" class="btn btn-danger">Excluir Todos os Jogadores</button>
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
      <div class="header-title">
        <div class="logo-badge">ℹ️</div>
        <h1>Sobre</h1>
      </div>
      <a href="index.html" class="back-btn">← Voltar</a>
    </header>
    <main>
      <div class="card" style="text-align: center; padding: 30px 20px;">
        <div style="font-size: 3rem; margin-bottom: 12px;">🎱</div>
        <h2 style="font-size: 1.4rem; font-weight: 700; margin-bottom: 6px;">Área27 Sinuca</h2>
        <p style="color: var(--primary); font-weight: 600; margin-bottom: 24px;">Versão MVP</p>
        <div style="background: #161616; border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 16px; margin-bottom: 20px; text-align: left; display: flex; flex-direction: column; gap: 10px; font-size: 0.95rem;">
          <div><strong style="color: var(--text-muted);">Plataforma:</strong> Rodando em ESP8266 (ESP-01)</div>
          <div><strong style="color: var(--text-muted);">Desenvolvido por:</strong> Área27</div>
          <div><strong style="color: var(--text-muted);">Tecnologia:</strong> HTML5, CSS3, JS Vanilla (Sem Frameworks)</div>
        </div>
        <a href="index.html" class="btn btn-primary" style="text-decoration: none;">Ir para a Página Inicial</a>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

// ==========================================
// wifi.html (Captive Portal Configuration Page)
// ==========================================
const char HTML_WIFI_CONFIG[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Configuração Wi-Fi - Área27 Sinuca</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="app-container">
    <header class="header">
      <div class="header-title">
        <div class="logo-badge">📶</div>
        <h1>Configurar Wi-Fi</h1>
      </div>
    </header>

    <main>
      <div class="card">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px;">Conectar à sua Rede Wi-Fi</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">
          Selecione a sua rede Wi-Fi abaixo e digite a senha para conectar o ESP8266.
        </p>

        <form id="form-wifi">
          <div class="form-group">
            <label class="form-label" for="wifi-ssid">Redes Disponíveis</label>
            <select id="wifi-ssid" class="form-select" required>
              <option value="">Procurando redes Wi-Fi...</option>
            </select>
          </div>

          <div class="form-group">
            <label class="form-label" for="wifi-pass">Senha do Wi-Fi</label>
            <input type="password" id="wifi-pass" class="form-input" placeholder="Digite a senha do Wi-Fi">
          </div>

          <button type="submit" class="btn btn-primary" id="btn-save-wifi">Salvar e Conectar</button>
        </form>
      </div>
    </main>

    <footer class="footer">Área27 Sinuca &bull; Captive Portal Edition</footer>
  </div>

  <script>
    async function scanWifi() {
      const select = document.getElementById('wifi-ssid');
      try {
        const res = await fetch('/wifi/scan');
        const networks = await res.json();
        select.innerHTML = '<option value="">Selecione uma rede...</option>';
        networks.forEach(net => {
          const opt = document.createElement('option');
          opt.value = net.ssid;
          opt.textContent = `${net.ssid} (${net.rssi} dBm)`;
          select.appendChild(opt);
        });
      } catch (e) {
        select.innerHTML = '<option value="">Erro ao buscar redes. Recarregue a página.</option>';
      }
    }

    document.getElementById('form-wifi').addEventListener('submit', async (e) => {
      e.preventDefault();
      const ssid = document.getElementById('wifi-ssid').value;
      const pass = document.getElementById('wifi-pass').value;
      const btn = document.getElementById('btn-save-wifi');

      if (!ssid) { alert('Selecione uma rede Wi-Fi'); return; }

      btn.disabled = true;
      btn.textContent = 'Salvando e Reiniciando...';

      try {
        await fetch('/wifi/save', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ ssid, password: pass })
        });
        alert('Configuração salva! O ESP8266 está reiniciando para conectar à rede: ' + ssid);
      } catch (e) {
        alert('Configuração enviada! O ESP8266 irá reiniciar.');
      }
    });

    scanWifi();
  </script>
</body>
</html>
)rawliteral";

#endif
