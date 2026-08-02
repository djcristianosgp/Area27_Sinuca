#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <Arduino.h>

// ==========================================
// style.css
// ==========================================
const char CSS_STYLE[] PROGMEM = R"rawliteral(
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

.btn-outline {
  background: transparent;
  border: 1px solid var(--border-color);
  color: var(--text-main);
}

.btn-outline:active {
  background: var(--border-color);
}

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
)rawliteral";

// ==========================================
// app.js
// ==========================================
const char JS_APP[] PROGMEM = R"rawliteral(
function getCurrentUser() {
  try {
    const data = localStorage.getItem('area27_user');
    return data ? JSON.parse(data) : null;
  } catch (e) { return null; }
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
  setTimeout(() => { window.location.reload(); }, 500);
}

function renderUserHeaderStatus() {
  const container = document.getElementById('user-status-container');
  if (!container) return;

  const user = getCurrentUser();
  if (user) {
    container.innerHTML = `
      <div class="user-badge">
        <span>👤 ${escapeHtml(user.nome)}</span>
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
      const response = await fetch(endpoint, {
        headers: { 'Content-Type': 'application/json', ...(options.headers || {}) },
        ...options
      });
      const data = await response.json();
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
  const loginSelect = document.getElementById('login-player-select');

  async function loadPlayers() {
    try {
      const players = await API.getPlayers();

      if (loginSelect) {
        loginSelect.innerHTML = '<option value="">Selecione seu perfil...</option>';
        players.forEach(p => {
          const opt = document.createElement('option');
          opt.value = p.id;
          opt.textContent = `${p.nome} (${p.telefone})`;
          loginSelect.appendChild(opt);
        });
      }

      if (!players || players.length === 0) {
        playerList.innerHTML = `<div class="empty-state">Nenhum jogador cadastrado ainda.</div>`;
        return;
      }

      playerList.innerHTML = players.map(p => `
        <div class="list-item">
          <div class="player-info">
            <span class="player-name">${escapeHtml(p.nome)}</span>
            <span class="player-phone">📞 ${escapeHtml(p.telefone)}</span>
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
      if (playerList) playerList.innerHTML = `<div class="empty-state">Erro ao carregar lista de jogadores.</div>`;
    }
  }

  window.handleDeleteSinglePlayer = async (id, nome) => {
    if (confirm(`Deseja realmente excluir o jogador "${nome}"?`)) {
      try {
        await API.deletePlayer(id);
        showToast(`Jogador "${nome}" excluído com sucesso!`, 'success');
        const curr = getCurrentUser();
        if (curr && curr.id === id) setCurrentUser(null);
        await loadPlayers();
      } catch (e) {}
    }
  };

  if (formPlayer) {
    formPlayer.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nome = document.getElementById('nome').value.trim();
      const telefone = document.getElementById('telefone').value.trim();
      const senha = document.getElementById('senha').value.trim();

      if (!nome || !telefone || !senha) {
        showToast('Preencha todos os campos obrigatórios', 'error');
        return;
      }

      if (senha.length !== 4 || !/^\d{4}$/.test(senha)) {
        showToast('A senha deve conter exatamente 4 dígitos numéricos', 'error');
        return;
      }

      const submitBtn = formPlayer.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        const res = await API.registerPlayer({ nome, telefone, senha });
        showToast(`Jogador ${nome} cadastrado com sucesso!`, 'success');
        setCurrentUser({ id: res.id, nome: res.nome, telefone: res.telefone });
        formPlayer.reset();
        await loadPlayers();
      } catch (err) {
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  if (formLogin) {
    formLogin.addEventListener('submit', async (e) => {
      e.preventDefault();
      const id = loginSelect ? loginSelect.value : '';
      const telefone = document.getElementById('login-telefone').value.trim();
      const senha = document.getElementById('login-senha').value.trim();

      if (!id && !telefone) {
        showToast('Selecione seu perfil ou digite seu telefone', 'error');
        return;
      }

      if (senha.length !== 4 || !/^\d{4}$/.test(senha)) {
        showToast('Informe a senha PIN de 4 dígitos numéricos', 'error');
        return;
      }

      const submitBtn = formLogin.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        const res = await API.loginPlayer({ id: Number(id) || 0, telefone, senha });
        showToast(`Bem-vindo de volta, ${res.player.nome}!`, 'success');
        setCurrentUser(res.player);
        formLogin.reset();
      } catch (err) {
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  loadPlayers();
}

let matchPollTimer = null;
let currentActiveMatchData = null;
let cachedPlayersList = [];

function switchGuardTab(tab) {
  const regForm = document.getElementById('guard-form-register');
  const loginForm = document.getElementById('guard-form-login');
  const regBtn = document.getElementById('guard-tab-register');
  const loginBtn = document.getElementById('guard-tab-login');

  if (tab === 'register') {
    regForm.classList.remove('hidden');
    loginForm.classList.add('hidden');
    regBtn.classList.add('active');
    loginBtn.classList.remove('active');
  } else {
    regForm.classList.add('hidden');
    loginForm.classList.remove('hidden');
    regBtn.classList.remove('active');
    loginBtn.classList.add('active');
  }
}

function switchMatchTab(tab) {
  const createCard = document.getElementById('card-create-match');
  const joinCard = document.getElementById('card-join-match');
  const createBtn = document.getElementById('tab-btn-create-match');
  const joinBtn = document.getElementById('tab-btn-join-match');

  if (tab === 'create') {
    createCard.classList.remove('hidden');
    joinCard.classList.add('hidden');
    createBtn.classList.add('active');
    joinBtn.classList.remove('active');
  } else {
    createCard.classList.add('hidden');
    joinCard.classList.remove('hidden');
    createBtn.classList.remove('active');
    joinBtn.classList.add('active');
  }
}

function handleMatchTypeChange() {
  const select = document.getElementById('match-type-select');
  const container = document.getElementById('dynamic-invites-container');
  if (!select || !container) return;

  const type = select.value;
  const user = getCurrentUser();
  const available = cachedPlayersList.filter(p => !user || p.id !== user.id);

  let html = '';

  if (type === 'par_impar_2p') {
    html = `
      <div class="form-group">
        <label class="form-label" for="select-playerB">Selecionar Oponente (Jogador 2)</label>
        <select id="select-playerB" class="form-select">
          <option value="">Aguardar vínculo via Código de 4 Caracteres</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
    `;
  } else if (type === 'par_impar_4p') {
    html = `
      <div class="form-group">
        <label class="form-label" for="select-playerB">Dupla A - Seu Parceiro (Jogador 2)</label>
        <select id="select-playerB" class="form-select">
          <option value="">Aguardar vínculo via Código</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
      <div class="form-group">
        <label class="form-label" for="select-playerC">Dupla B - Oponente 1 (Jogador 3)</label>
        <select id="select-playerC" class="form-select">
          <option value="">Aguardar vínculo via Código</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
      <div class="form-group">
        <label class="form-label" for="select-playerD">Dupla B - Oponente 2 (Jogador 4)</label>
        <select id="select-playerD" class="form-select">
          <option value="">Aguardar vínculo via Código</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
    `;
  } else if (type === '5_bolas_3p') {
    html = `
      <div class="form-group">
        <label class="form-label" for="select-playerB">Oponente 1 (Jogador 2)</label>
        <select id="select-playerB" class="form-select">
          <option value="">Aguardar vínculo via Código</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
      <div class="form-group">
        <label class="form-label" for="select-playerC">Oponente 2 (Jogador 3)</label>
        <select id="select-playerC" class="form-select">
          <option value="">Aguardar vínculo via Código</option>
          ${available.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo} ELO)</option>`).join('')}
        </select>
      </div>
    `;
  }

  container.innerHTML = html;
}

function selectBalls(count) {
  const input = document.getElementById('loser-balls-input');
  if (input) input.value = count;

  const opts = document.querySelectorAll('.ball-opt');
  opts.forEach((opt, idx) => {
    if (idx === count) opt.classList.add('selected');
    else opt.classList.remove('selected');
  });
}

async function respondInvite(accept) {
  const user = getCurrentUser();
  if (!user) return;

  try {
    const res = await API.respondMatchInvite({ player: user.id, accept });
    showToast(res.message || (accept ? 'Convite aceito!' : 'Convite recusado.'), 'success');
    await checkActiveMatchState();
  } catch (e) {}
}

function openFinishModal() {
  if (!currentActiveMatchData || !currentActiveMatchData.active) {
    showToast('Nenhuma partida ativa para finalizar', 'error');
    return;
  }

  const modal = document.getElementById('modal-finish-match');
  const winnerSelect = document.getElementById('finish-winner-select');

  winnerSelect.innerHTML = '<option value="">Selecione o Vencedor</option>';
  
  const type = currentActiveMatchData.matchType;
  const players = currentActiveMatchData.players || [];

  if (type === 'par_impar_4p') {
    const p0 = players[0] ? players[0].nome : 'P1';
    const p1 = players[1] ? players[1].nome : 'P2';
    const p2 = players[2] ? players[2].nome : 'P3';
    const p3 = players[3] ? players[3].nome : 'P4';

    const opt1 = document.createElement('option');
    opt1.value = 1;
    opt1.textContent = `🥇 Dupla A (${p0} & ${p1})`;
    winnerSelect.appendChild(opt1);

    const opt2 = document.createElement('option');
    opt2.value = 2;
    opt2.textContent = `🥇 Dupla B (${p2} & ${p3})`;
    winnerSelect.appendChild(opt2);
  } else {
    players.forEach(p => {
      if (p.id > 0) {
        const opt = document.createElement('option');
        opt.value = p.id;
        opt.textContent = `🥇 ${p.nome}`;
        winnerSelect.appendChild(opt);
      }
    });
  }

  selectBalls(0);
  modal.classList.remove('hidden');
  modal.scrollIntoView({ behavior: 'smooth' });
}

function closeFinishModal() {
  const modal = document.getElementById('modal-finish-match');
  if (modal) modal.classList.add('hidden');
}

async function cancelCurrentMatch() {
  if (confirm('Deseja realmente cancelar a partida atual?')) {
    try {
      await API.cancelMatch();
      showToast('Partida cancelada com sucesso.', 'success');
      closeFinishModal();
      await checkActiveMatchState();
    } catch (e) {}
  }
}

async function checkActiveMatchState() {
  try {
    const data = await API.getActiveMatch();
    currentActiveMatchData = data;

    const user = getCurrentUser();
    const activePanel = document.getElementById('active-match-panel');
    const lobbyPanel = document.getElementById('match-lobby');
    const inviteBanner = document.getElementById('invite-pending-card');
    const inviteText = document.getElementById('invite-banner-text');
    const codeDisplay = document.getElementById('active-room-code');
    const rosterContainer = document.getElementById('active-roster-container');
    const statusMsg = document.getElementById('match-status-msg');
    const finishBtn = document.getElementById('btn-open-finish-modal');
    const typeBadge = document.getElementById('active-match-type-badge');

    if (data && data.active && data.status !== 'finished') {
      let mySlot = null;
      if (user && data.players) {
        mySlot = data.players.find(p => p.id === user.id);
      }

      if (mySlot && mySlot.invite === 'pending') {
        if (inviteBanner) inviteBanner.classList.remove('hidden');
        if (inviteText) inviteText.textContent = `Você foi convidado para uma partida de ${getMatchTypeName(data.matchType)}! Clique abaixo para aceitar ou recusar:`;
      } else {
        if (inviteBanner) inviteBanner.classList.add('hidden');
      }

      if (activePanel) activePanel.classList.remove('hidden');
      if (lobbyPanel) lobbyPanel.classList.add('hidden');

      if (typeBadge) typeBadge.textContent = getMatchTypeName(data.matchType).toUpperCase();
      if (codeDisplay) codeDisplay.textContent = data.code || '----';

      if (rosterContainer && data.players) {
        rosterContainer.innerHTML = data.players.map((p, idx) => {
          let badgeText = 'Vaga Livre';
          let badgeStyle = 'background: #252525; color: #888;';

          if (p.invite === 'creator') {
            badgeText = '👑 Criador';
            badgeStyle = 'background: rgba(255,215,0,0.15); color: var(--gold); border: 1px solid rgba(255,215,0,0.4);';
          } else if (p.invite === 'pending') {
            badgeText = '⏳ Convite Pendente';
            badgeStyle = 'background: rgba(230,81,0,0.2); color: #ff9800; border: 1px solid #ff9800;';
          } else if (p.invite === 'accepted') {
            badgeText = '🟢 Confirmado';
            badgeStyle = 'background: rgba(46,125,50,0.2); color: #4caf50; border: 1px solid #4caf50;';
          }

          let slotLabel = `Jogador ${idx + 1}`;
          if (data.matchType === 'par_impar_4p') {
            slotLabel = (idx < 2) ? `Dupla A (Slot ${idx + 1})` : `Dupla B (Slot ${idx + 1})`;
          }

          return `
            <div class="list-item">
              <div class="player-info">
                <span class="player-name">${escapeHtml(p.nome)}</span>
                <span class="player-phone">${slotLabel} &bull; ${p.elo || 1000} ELO</span>
              </div>
              <span class="badge-elo" style="${badgeStyle}">${badgeText}</span>
            </div>
          `;
        }).join('');
      }

      if (data.status === 'in_progress') {
        if (statusMsg) statusMsg.textContent = '🟢 Partida em Andamento! Quando terminar, clique abaixo:';
        if (finishBtn) finishBtn.disabled = false;
      } else {
        if (statusMsg) statusMsg.textContent = '⏳ Aguardando jogadores aceitarem os convites...';
        if (finishBtn) finishBtn.disabled = true;
      }
    } else {
      if (inviteBanner) inviteBanner.classList.add('hidden');
      if (activePanel) activePanel.classList.add('hidden');
      if (lobbyPanel) lobbyPanel.classList.remove('hidden');
      closeFinishModal();
    }
  } catch (e) {}
}

function getMatchTypeName(type) {
  if (type === 'par_impar_4p') return 'Par ou Ímpar (Dupla 4P)';
  if (type === '5_bolas_3p') return '5 Bolas (3P)';
  return 'Par ou Ímpar (Individual 2P)';
}

async function initMatchPage() {
  const authGuard = document.getElementById('match-auth-guard');
  const matchArena = document.getElementById('match-arena');

  const user = getCurrentUser();
  if (!user) {
    if (authGuard) authGuard.classList.remove('hidden');
    if (matchArena) matchArena.classList.add('hidden');
    initMatchAuthGuard();
    return;
  }

  if (authGuard) authGuard.classList.add('hidden');
  if (matchArena) matchArena.classList.remove('hidden');

  const playerNameDisp = document.getElementById('current-player-name-display');
  if (playerNameDisp) playerNameDisp.textContent = `👤 ${user.nome} (Criador)`;

  try {
    cachedPlayersList = await API.getPlayers();
    handleMatchTypeChange();
  } catch (e) {}

  const formCreate = document.getElementById('form-create-match');
  if (formCreate) {
    formCreate.addEventListener('submit', async (e) => {
      e.preventDefault();
      const matchTypeSelect = document.getElementById('match-type-select');
      const matchType = matchTypeSelect ? matchTypeSelect.value : 'par_impar_2p';

      const pB = document.getElementById('select-playerB');
      const pC = document.getElementById('select-playerC');
      const pD = document.getElementById('select-playerD');

      const playerB = pB ? Number(pB.value) || 0 : 0;
      const playerC = pC ? Number(pC.value) || 0 : 0;
      const playerD = pD ? Number(pD.value) || 0 : 0;

      const submitBtn = formCreate.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        const res = await API.createMatch({
          matchType,
          playerA: user.id,
          playerB,
          playerC,
          playerD
        });
        showToast(`Partida criada com sucesso! Código: ${res.code}`, 'success');
        await checkActiveMatchState();
      } catch (err) {
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  const formJoin = document.getElementById('form-join-match');
  if (formJoin) {
    formJoin.addEventListener('submit', async (e) => {
      e.preventDefault();
      const codeInput = document.getElementById('input-join-code');
      const code = codeInput ? codeInput.value.trim().toUpperCase() : '';

      if (!code || code.length !== 4) {
        showToast('Informe o código de 4 caracteres da sala', 'error');
        return;
      }

      const submitBtn = formJoin.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.joinMatch({ code, player: user.id });
        showToast('Vínculo com a partida realizado! Aguardando aceite.', 'success');
        if (codeInput) codeInput.value = '';
        await checkActiveMatchState();
      } catch (err) {
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  const formFinish = document.getElementById('form-finish-match');
  if (formFinish) {
    formFinish.addEventListener('submit', async (e) => {
      e.preventDefault();
      const winner = Number(document.getElementById('finish-winner-select').value);
      const loserBallsInput = document.getElementById('loser-balls-input').value;

      if (!winner) {
        showToast('Selecione o vencedor da partida', 'error');
        return;
      }

      if (loserBallsInput === '' || isNaN(loserBallsInput)) {
        showToast('Informe com quantas bolas o perdedor ficou', 'error');
        return;
      }

      const loserBalls = Number(loserBallsInput);
      const submitBtn = formFinish.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.finishMatch({ winner, loserBalls });
        showToast('🏆 Partida registrada e finalizada com sucesso!', 'success');
        closeFinishModal();
        await checkActiveMatchState();
      } catch (err) {
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  checkActiveMatchState();
  if (matchPollTimer) clearInterval(matchPollTimer);
  matchPollTimer = setInterval(checkActiveMatchState, 2500);
}

function initMatchAuthGuard() {
  const guardSelect = document.getElementById('guard-login-select');
  if (guardSelect) {
    API.getPlayers().then(players => {
      guardSelect.innerHTML = '<option value="">Selecione seu perfil...</option>';
      players.forEach(p => {
        const opt = document.createElement('option');
        opt.value = p.id;
        opt.textContent = `${p.nome} (${p.telefone})`;
        guardSelect.appendChild(opt);
      });
    }).catch(() => {});
  }

  const regForm = document.getElementById('guard-form-register');
  if (regForm) {
    regForm.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nome = document.getElementById('guard-nome').value.trim();
      const telefone = document.getElementById('guard-telefone').value.trim();
      const senha = document.getElementById('guard-senha').value.trim();

      if (senha.length !== 4 || !/^\d{4}$/.test(senha)) {
        showToast('A senha PIN deve ter exatamente 4 dígitos numéricos', 'error');
        return;
      }

      try {
        const res = await API.registerPlayer({ nome, telefone, senha });
        showToast(`Cadastro realizado com sucesso!`, 'success');
        setCurrentUser({ id: res.id, nome: res.nome, telefone: res.telefone });
        window.location.reload();
      } catch (err) {}
    });
  }

  const loginForm = document.getElementById('guard-form-login');
  if (loginForm) {
    loginForm.addEventListener('submit', async (e) => {
      e.preventDefault();
      const id = guardSelect ? guardSelect.value : '';
      const telefone = document.getElementById('guard-login-telefone').value.trim();
      const senha = document.getElementById('guard-login-senha').value.trim();

      if (senha.length !== 4 || !/^\d{4}$/.test(senha)) {
        showToast('Informe a senha PIN de 4 dígitos numéricos', 'error');
        return;
      }

      try {
        const res = await API.loginPlayer({ id: Number(id) || 0, telefone, senha });
        showToast(`Bem-vindo, ${res.player.nome}!`, 'success');
        setCurrentUser(res.player);
        window.location.reload();
      } catch (err) {}
    });
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

      if (pin !== '0000') {
        showToast('PIN de Administrador incorreto (PIN: 0000)', 'error');
        return;
      }

      try {
        await API.authSettingsPin({ pin });
        sessionStorage.setItem('area27_admin_auth', 'true');
        showToast('Acesso administrativo liberado com sucesso!', 'success');
        if (adminCard) adminCard.classList.add('hidden');
        if (settingsContent) settingsContent.classList.remove('hidden');
      } catch (err) {
      }
    });
  }

  const resetWifiBtn = document.getElementById('btn-reset-wifi');
  const resetRankingBtn = document.getElementById('btn-reset-ranking');
  const clearPlayersBtn = document.getElementById('btn-clear-players');

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

document.addEventListener('DOMContentLoaded', () => {
  renderUserHeaderStatus();
  if (document.getElementById('form-player') || document.getElementById('form-login')) initPlayersPage();
  if (document.getElementById('match-arena') || document.getElementById('match-auth-guard')) initMatchPage();
  if (document.getElementById('ranking-container')) initRankingPage();
  if (document.getElementById('admin-pin-card') || document.getElementById('btn-reset-wifi')) initSettingsPage();
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
      <div id="user-status-container"></div>
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

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition
    </footer>
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
      <div style="display: flex; align-items: center; gap: 8px;">
        <div id="user-status-container"></div>
        <a href="index.html" class="back-btn">← Voltar</a>
      </div>
    </header>

    <main>
      <div class="tabs-nav">
        <button id="tab-btn-register" class="tab-btn active" onclick="switchAuthTab('register')">Cadastrar</button>
        <button id="tab-btn-login" class="tab-btn" onclick="switchAuthTab('login')">Entrar (Login)</button>
      </div>

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
            <input type="password" id="senha" class="form-input" placeholder="Ex: 1234" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" required>
          </div>

          <button type="submit" class="btn btn-primary">Cadastrar e Entrar</button>
        </form>
      </div>

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
            <input type="password" id="login-senha" class="form-input" placeholder="****" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" required>
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
      Área27 Sinuca &bull; ESP8266 Edition
    </footer>
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
            <input type="password" id="guard-senha" class="form-input" placeholder="Ex: 1234" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" required>
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
            <input type="password" id="guard-login-senha" class="form-input" placeholder="****" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" required>
          </div>
          <button type="submit" class="btn btn-secondary">Entrar na Conta</button>
        </form>
      </div>

      <div id="match-arena" class="hidden">

        <div id="invite-pending-card" class="card hidden" style="margin-bottom: 20px; border-color: var(--gold); background: linear-gradient(135deg, #2A2410, #1E1E1E);">
          <h3 style="color: var(--gold); font-size: 1.1rem; margin-bottom: 8px;">📩 Convite de Partida Recebido!</h3>
          <p id="invite-banner-text" style="font-size: 0.9rem; color: var(--text-main); margin-bottom: 16px;">
            Você foi convidado para entrar em uma partida!
          </p>
          <div style="display: flex; gap: 10px;">
            <button class="btn btn-primary" onclick="respondInvite(true)">✅ Aceitar Convite</button>
            <button class="btn btn-outline" style="border-color: var(--error-color); color: var(--error-color);" onclick="respondInvite(false)">❌ Recusar Convite</button>
          </div>
        </div>
        
        <div id="active-match-panel" class="card hidden" style="margin-bottom: 20px;">
          <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 12px;">
            <span id="active-match-type-badge" class="badge-elo" style="font-size: 0.85rem;">PAR OU ÍMPAR (2P)</span>
            <button onclick="cancelCurrentMatch()" style="background: none; border: none; color: var(--error-color); cursor: pointer; font-size: 0.85rem; font-weight: 600;">✖ Cancelar</button>
          </div>

          <div class="code-box">
            <div class="code-title">Código da Partida (4 Caracteres)</div>
            <div id="active-room-code" class="code-display">----</div>
            <div style="font-size: 0.8rem; color: var(--text-muted); margin-top: 6px;">
              Outro jogador pode digitar este código para entrar na sala!
            </div>
          </div>

          <div id="active-roster-container" class="item-list" style="margin: 16px 0;">
          </div>

          <div id="match-status-msg" style="text-align: center; font-size: 0.9rem; color: var(--gold); margin-bottom: 14px;">
            ⏳ Aguardando jogadores aceitarem os convites...
          </div>

          <div style="display: flex; flex-direction: column; gap: 10px;">
            <button id="btn-open-finish-modal" class="btn btn-primary" onclick="openFinishModal()" disabled>
              🏆 Finalizar Partida
            </button>
            <button id="btn-cancel-match" class="btn btn-outline" style="border-color: var(--error-color); color: var(--error-color);" onclick="cancelCurrentMatch()">
              🚫 Cancelar Partida
            </button>
          </div>
        </div>

        <div id="match-lobby">
          <div class="tabs-nav">
            <button id="tab-btn-create-match" class="tab-btn active" onclick="switchMatchTab('create')">Criar Partida</button>
            <button id="tab-btn-join-match" class="tab-btn" onclick="switchMatchTab('join')">Entrar por Código</button>
          </div>

          <div id="card-create-match" class="card">
            <h2 style="font-size: 1.1rem; margin-bottom: 14px;">➕ Criar Nova Partida</h2>
            <form id="form-create-match">
              
              <div class="form-group">
                <label class="form-label" for="match-type-select">Tipo de Partida *</label>
                <select id="match-type-select" class="form-select" onchange="handleMatchTypeChange()" required>
                  <option value="par_impar_2p">🎱 Par ou Ímpar (Individual - 2 Jogadores)</option>
                  <option value="par_impar_4p">👥 Par ou Ímpar (Em Dupla - 4 Jogadores)</option>
                  <option value="5_bolas_3p">🖐️ 5 Bolas (3 Jogadores)</option>
                </select>
              </div>

              <div class="form-group">
                <label class="form-label">Criador (Você)</label>
                <div id="current-player-name-display" class="form-input" style="display: flex; align-items: center; color: var(--gold); font-weight: 700;">
                  Carregando perfil...
                </div>
              </div>

              <div id="dynamic-invites-container">
              </div>

              <button type="submit" class="btn btn-primary" style="margin-top: 10px;">⚡ Iniciar Partida</button>
            </form>
          </div>

          <div id="card-join-match" class="card hidden">
            <h2 style="font-size: 1.1rem; margin-bottom: 14px;">🔗 Vincular-se a uma Partida</h2>
            <form id="form-join-match">
              <div class="form-group">
                <label class="form-label" for="input-join-code">Código da Partida (4 Caracteres) *</label>
                <input type="text" id="input-join-code" class="form-input" placeholder="Ex: A7K9" maxlength="4" style="text-transform: uppercase; font-size: 1.4rem; letter-spacing: 4px; font-weight: 700; text-align: center;" required>
              </div>

              <button type="submit" class="btn btn-secondary">🤝 Entrar na Partida</button>
            </form>
          </div>
        </div>

      </div>

      <div id="modal-finish-match" class="card hidden" style="margin-top: 20px; border-color: var(--primary);">
        <h2 style="font-size: 1.2rem; margin-bottom: 14px; text-align: center; color: var(--gold);">🏁 Finalizar Partida</h2>

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
      Área27 Sinuca &bull; ESP8266 Edition
    </footer>
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

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition
    </footer>
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
      <div id="admin-pin-card" class="card" style="margin-bottom: 16px;">
        <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--gold);">🔒 Acesso Restrito</h2>
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">
          Informe o PIN de Administrador (0000) para acessar as configurações do sistema.
        </p>

        <form id="form-admin-pin">
          <div class="form-group">
            <label class="form-label" for="admin-pin-input">PIN de Administrador (4 dígitos)</label>
            <input type="password" id="admin-pin-input" class="form-input" placeholder="0000" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" style="text-align: center; font-size: 1.5rem; letter-spacing: 6px;" required>
          </div>

          <button type="submit" class="btn btn-primary">🔓 Acessar Configurações</button>
        </form>
      </div>

      <div id="settings-content" class="hidden">
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
            Apaga permanentemente todos os jogadores cadastrados e reinicia o banco de dados.
          </p>
          <button id="btn-clear-players" class="btn btn-danger">Excluir Todos os Jogadores</button>
        </div>
      </div>
    </main>

    <footer class="footer">
      Área27 Sinuca &bull; ESP8266 Edition
    </footer>
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

        <form action="/wifi/save" method="POST">
          <div class="form-group">
            <label class="form-label" for="wifi-ssid">Redes Disponíveis</label>
            <select id="wifi-ssid" name="ssid" class="form-select" required>
              <option value="">Procurando redes Wi-Fi...</option>
            </select>
          </div>

          <div class="form-group">
            <label class="form-label" for="wifi-pass">Senha do Wi-Fi</label>
            <input type="password" id="wifi-pass" name="password" class="form-input" placeholder="Digite a senha do Wi-Fi">
          </div>

          <button type="submit" class="btn btn-primary">Salvar e Conectar</button>
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
        select.innerHTML = '<option value="">Erro ao buscar redes. Digite manualmente ou recarregue.</option>';
      }
    }
    scanWifi();
  </script>
</body>
</html>
)rawliteral";

#endif
