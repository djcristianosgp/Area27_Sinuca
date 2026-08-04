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
  resetPlayerPassword(d) { return this.request('/players/reset-password', { method: 'POST', body: JSON.stringify(d) }); },
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
  importBackup(d) { return this.request('/api/v1/backup/import', { method: 'POST', body: JSON.stringify(d) }); },
  checkUpdate() { return this.request('/api/v1/update/check'); },
  startUpdate(d) { return this.request('/api/v1/update/start', { method: 'POST', body: JSON.stringify(d) }); }
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
      setCurrentUser(res.player);
      showToast(`Bem-vindo, ${res.player.nome}!`, 'success');
    }
  } catch (err) {}
}

async function initPlayersPage() {
  const container = document.getElementById('players-container');
  const form = document.getElementById('form-add-player');
  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nome = document.getElementById('new-player-name').value.trim();
      const telefone = document.getElementById('new-player-phone').value.trim();
      const senhaEl = document.getElementById('new-player-pass');
      const senha = senhaEl ? senhaEl.value.trim() : '0000';
      if (!nome || !senha) return;
      try {
        const res = await API.registerPlayer({ nome, telefone, senha });
        showToast('Jogador cadastrado com sucesso!', 'success');
        setCurrentUser({ id: res.id, nome: res.nome, telefone: res.telefone, elo: 1000 });
        form.reset();
        loadList();
      } catch (err) {}
    });
  }
  async function loadList() {
    try {
      const players = await API.getPlayers();
      if (!players || players.length === 0) {
        container.innerHTML = '<div class="empty-state">Nenhum jogador cadastrado ainda. Use o formulário acima para adicionar!</div>';
        return;
      }
      container.innerHTML = players.map(p => `
        <div class="list-item">
          <div>
            <a href="profile.html?id=${p.id}" style="color:inherit; text-decoration:none; font-weight:700;">👤 ${escapeHtml(p.nome)}</a>
            <div style="font-size:0.8rem; color:var(--text-muted);">${p.vitorias || 0}V / ${p.derrotas || 0}D ${p.telefone ? '&bull; Tel: ' + escapeHtml(p.telefone) : ''}</div>
          </div>
          <div style="display:flex; align-items:center; gap:8px;">
            <span class="badge-elo">${p.elo || 1000} ELO</span>
            <button onclick="promptLoginForUser(${p.id}, '${escapeHtml(p.nome)}')" class="btn btn-secondary" style="height:34px; padding:0 10px; font-size:0.8rem;">Entrar</button>
          </div>
        </div>
      `).join('');
    } catch (err) {
      container.innerHTML = '<div class="empty-state">Erro ao carregar jogadores.</div>';
    }
  }
  loadList();
}

async function initRankingPage() {
  const container = document.getElementById('ranking-container');
  try {
    const players = await API.getRanking();
    if (!players || players.length === 0) {
      container.innerHTML = '<div class="empty-state">Nenhum jogador no ranking ainda.</div>';
      return;
    }
    players.sort((a, b) => (b.elo || 1000) - (a.elo || 1000));
    container.innerHTML = players.map((p, idx) => {
      const rankClass = idx === 0 ? 'rank-1' : (idx === 1 ? 'rank-2' : (idx === 2 ? 'rank-3' : ''));
      const rankBadge = idx === 0 ? '🥇' : (idx === 1 ? '🥈' : (idx === 2 ? '🥉' : `${idx + 1}`));
      const total = (p.vitorias || 0) + (p.derrotas || 0);
      const winrate = total > 0 ? Math.round((p.vitorias / total) * 100) : 0;
      return `
        <div class="ranking-card" style="margin-bottom:10px;">
          <div class="ranking-rank ${rankClass}">${rankBadge}</div>
          <div style="flex:1;">
            <a href="profile.html?id=${p.id}" style="color:inherit; text-decoration:none; font-weight:700; font-size:1.05rem;">${escapeHtml(p.nome)}</a>
            <div style="font-size:0.8rem; color:var(--text-muted);">${p.vitorias || 0}V / ${p.derrotas || 0}D (${winrate}% vitórias)</div>
          </div>
          <div class="badge-elo" style="font-size:1rem; padding:6px 12px;">${p.elo || 1000} ELO</div>
        </div>
      `;
    }).join('');
  } catch (err) {
    container.innerHTML = '<div class="empty-state">Erro ao carregar ranking.</div>';
  }
}

async function initHallPage() {
  const peakEl = document.getElementById('hall-peak-elo');
  const streakEl = document.getElementById('hall-max-streak');
  try {
    const players = await API.getPlayers();
    if (!players || players.length === 0) {
      if (peakEl) peakEl.textContent = 'Nenhum registro';
      if (streakEl) streakEl.textContent = 'Nenhum registro';
      return;
    }
    let topEloPlayer = players[0];
    for (const p of players) {
      const pPeak = p.peak_elo || p.elo || 1000;
      const curTopPeak = topEloPlayer.peak_elo || topEloPlayer.elo || 1000;
      if (pPeak > curTopPeak) topEloPlayer = p;
    }
    const maxEloVal = topEloPlayer.peak_elo || topEloPlayer.elo || 1000;
    if (peakEl) peakEl.innerHTML = `👑 <strong>${escapeHtml(topEloPlayer.nome)}</strong> (${maxEloVal} ELO)`;

    let topStreakPlayer = players[0];
    for (const p of players) {
      const pStreak = p.max_win_streak || p.current_streak || 0;
      const curTopStreak = topStreakPlayer.max_win_streak || topStreakPlayer.current_streak || 0;
      if (pStreak > curTopStreak) topStreakPlayer = p;
    }
    const maxStreakVal = topStreakPlayer.max_win_streak || topStreakPlayer.current_streak || 0;
    if (streakEl) streakEl.innerHTML = `🔥 <strong>${escapeHtml(topStreakPlayer.nome)}</strong> (${maxStreakVal} vitórias seguidas)`;
  } catch (err) {
    if (peakEl) peakEl.textContent = 'Erro ao carregar';
    if (streakEl) streakEl.textContent = 'Erro ao carregar';
  }
}

async function initProfilePage() {
  const params = new URLSearchParams(window.location.search);
  let playerId = parseInt(params.get('id'));
  if (!playerId) {
    const user = getCurrentUser();
    if (user) playerId = user.id;
  }
  if (!playerId) {
    document.getElementById('profile-name').textContent = 'Selecione um Jogador';
    return;
  }
  try {
    const players = await API.getPlayers();
    const player = players.find(p => p.id === playerId);
    if (!player) {
      document.getElementById('profile-name').textContent = 'Jogador não encontrado';
      return;
    }
    document.getElementById('profile-name').textContent = player.nome;
    const phoneEl = document.getElementById('profile-phone');
    if (phoneEl) phoneEl.textContent = player.telefone ? `Tel: ${player.telefone}` : '';
    document.getElementById('profile-elo').textContent = `${player.elo || 1000}`;
    const total = (player.vitorias || 0) + (player.derrotas || 0);
    const winrate = total > 0 ? Math.round((player.vitorias / total) * 100) : 0;
    document.getElementById('profile-winrate').textContent = `${winrate}%`;

    const recentEl = document.getElementById('profile-recent-dots');
    if (recentEl) {
      try {
        const history = await API.getHistory();
        const myHistory = (history || []).filter(m => m.player1_id === playerId || m.player2_id === playerId || m.winner_id === playerId).slice(-5);
        if (myHistory.length === 0) {
          recentEl.textContent = 'Sem partidas recentes';
        } else {
          recentEl.innerHTML = myHistory.map(m => {
            const isWin = m.winner_id === playerId;
            return `<div class="recent-dot ${isWin ? 'win' : 'loss'}" title="${isWin ? 'Vitória' : 'Derrota'}">${isWin ? 'V' : 'D'}</div>`;
          }).join('');
        }
      } catch (e) { recentEl.textContent = '-'; }
    }

    const badgesEl = document.getElementById('profile-badges-list');
    if (badgesEl) {
      const badges = [
        { icon: '👑', title: 'Campeão', unlocked: (player.titles_count || 0) > 0, desc: 'Ganhou um campeonato' },
        { icon: '🔥', title: 'Em Chamas', unlocked: (player.max_win_streak || 0) >= 3, desc: '3+ vitórias seguidas' },
        { icon: '⚡', title: 'Bicicleta', unlocked: (player.shutout_count || 0) > 0, desc: 'Ganhou de 7x0' },
        { icon: '🎯', title: 'Veterano', unlocked: total >= 10, desc: 'Jogou 10+ partidas' },
        { icon: '🌟', title: 'Mestre ELO', unlocked: (player.elo || 1000) >= 1200, desc: 'Atingiu 1200+ ELO' },
        { icon: '🎱', title: 'Iniciante', unlocked: total >= 1, desc: 'Jogou a 1ª partida' }
      ];
      badgesEl.innerHTML = badges.map(b => `
        <div class="badge-card ${b.unlocked ? 'unlocked' : ''}" style="opacity:${b.unlocked ? 1 : 0.4};">
          <div class="badge-icon">${b.icon}</div>
          <div class="badge-title">${b.title}</div>
          <div style="font-size:0.65rem; color:var(--text-muted); text-align:center;">${b.desc}</div>
        </div>
      `).join('');
    }

    const btnQr = document.getElementById('btn-show-qr');
    const modalQr = document.getElementById('modal-qr');
    const btnCloseQr = document.getElementById('btn-close-qr');
    const qrContainer = document.getElementById('qr-container');
    if (btnQr && modalQr && btnCloseQr) {
      btnQr.addEventListener('click', () => {
        modalQr.classList.remove('hidden');
        if (qrContainer) {
          qrContainer.innerHTML = `<div style="padding:10px; font-weight:800; font-size:1.4rem; color:#000;">ID: ${player.id} &bull; ${escapeHtml(player.nome)}</div>`;
        }
      });
      btnCloseQr.addEventListener('click', () => { modalQr.classList.add('hidden'); });
    }
  } catch (err) {
    document.getElementById('profile-name').textContent = 'Erro ao carregar perfil';
  }
}

async function initTVPage() {
  function updateClock() {
    const clockEl = document.getElementById('tv-clock');
    if (clockEl) {
      const now = new Date();
      clockEl.textContent = now.toLocaleTimeString('pt-BR');
    }
  }
  updateClock();
  setInterval(updateClock, 1000);

  async function updateTVData() {
    try {
      const data = await API.getTV();
      const liveEl = document.getElementById('tv-live-content');
      if (liveEl) {
        if (data.activeMatch && data.activeMatch.active) {
          const isWaiting = data.activeMatch.status === 'waiting';
          const playersList = (data.activeMatch.players || []).map(p => {
            let statusBadge = '';
            if (p.invite === 'creator' || p.invite === 'accepted') statusBadge = '✅ Confirmado';
            else if (p.invite === 'pending') statusBadge = '⏳ Aguardando Aceite';
            else statusBadge = '👤 Vaga Livre';
            return `<div style="padding:6px 12px; background:#0f172a; border-radius:6px; margin:4px 0; display:flex; justify-content:space-between; align-items:center; font-size:0.9rem;">
              <span><strong>${escapeHtml(p.nome)}</strong></span>
              <span style="font-size:0.8rem; color:${p.invite === 'pending' ? '#fbbf24' : (p.id > 0 ? '#4ade80' : '#94a3b8')};">${statusBadge}</span>
            </div>`;
          }).join('');

          liveEl.innerHTML = `
            <div style="text-align:center; padding:10px;">
              <div style="font-size:1.1rem; font-weight:800; color:#38bdf8;">CÓDIGO DA MESA: <span style="background:#0284c7; color:#fff; padding:4px 14px; border-radius:6px; font-family:monospace; font-size:1.5rem;">${data.activeMatch.code}</span></div>
              <div style="margin:10px 0; font-size:1rem; color:${isWaiting ? '#fbbf24' : '#4ade80'}; font-weight:700;">
                ${isWaiting ? '⏳ PARTIDA ABERTA (AGUARDANDO CONFIRMAÇÃO DE JOGADORES)' : '🎱 PARTIDA EM ANDAMENTO'}
              </div>
              <div style="max-width:380px; margin:10px auto; text-align:left;">
                ${playersList}
              </div>
            </div>
          `;
        } else {
          liveEl.innerHTML = '<div style="text-align:center; color:#94a3b8; padding:20px;">Nenhuma partida aberta no momento.<br>Acesse pelo celular para iniciar!</div>';
        }
      }

      const rankingEl = document.getElementById('tv-ranking-body');
      if (rankingEl && data.ranking) {
        const sorted = [...data.ranking].sort((a, b) => (b.elo || 1000) - (a.elo || 1000)).slice(0, 10);
        rankingEl.innerHTML = sorted.map((p, idx) => `
          <tr style="border-bottom:1px solid #334155;">
            <td style="padding:10px; font-weight:800; color:${idx === 0 ? '#fbbf24' : (idx === 1 ? '#94a3b8' : (idx === 2 ? '#d97706' : '#64748b'))};">${idx + 1}º</td>
            <td style="padding:10px; font-weight:700;">${escapeHtml(p.nome)}</td>
            <td style="padding:10px; text-align:right; font-weight:800; color:#38bdf8;">${p.elo || 1000} ELO</td>
          </tr>
        `).join('');
      }

      const historyEl = document.getElementById('tv-history-list');
      if (historyEl && data.history) {
        const recent = data.history.slice(-5).reverse();
        if (recent.length === 0) {
          historyEl.innerHTML = '<div style="text-align:center; color:#94a3b8;">Nenhuma partida encerrada ainda.</div>';
        } else {
          historyEl.innerHTML = recent.map(m => `
            <div style="background:#0f172a; padding:10px 14px; border-radius:8px; margin-bottom:8px; display:flex; justify-content:space-between; align-items:center;">
              <div>
                <span style="color:#4ade80; font-weight:700;">🏆 ${escapeHtml(m.winner_name || 'Vencedor')}</span> vs <span style="color:#f87171;">${escapeHtml(m.loser_name || 'Adversário')}</span>
              </div>
              <div style="font-size:0.85rem; font-weight:800; color:#fbbf24;">Placar: ${m.score || '7 x ' + (m.loser_balls || 0)} (+${m.elo_delta || 25} ELO)</div>
            </div>
          `).join('');
        }
      }
    } catch (err) {}
  }

  updateTVData();
  setInterval(updateTVData, 4000);
}

async function initMatchPage() {
  const arena = document.getElementById('match-arena');
  if (!arena) return;

  async function renderMatchScreen() {
    try {
      const match = await API.getActiveMatch();
      const players = await API.getPlayers();
      const currentUser = getCurrentUser();

      if (!match || !match.active) {
        arena.innerHTML = `
          <div class="card">
            <h2 style="font-size:1.1rem; margin-bottom:12px; color:var(--primary);">🎱 Criar Nova Partida</h2>
            <form id="form-create-match">
              <div class="form-group">
                <label class="form-label">Modalidade de Jogo</label>
                <select id="match-type-select" class="form-select">
                  <option value="par_impar_2p">Par ou Ímpar (1 vs 1 - 2 Jogadores)</option>
                  <option value="par_impar_4p">Par ou Ímpar (2 vs 2 - 4 Jogadores)</option>
                  <option value="5_bolas_3p">5 Bolas (3 Jogadores)</option>
                </select>
              </div>
              <div class="form-group">
                <label class="form-label">Criador da Mesa (Jogador 1)</label>
                <select id="creator-select" class="form-select" required>
                  ${players.map(p => `<option value="${p.id}" ${currentUser && currentUser.id === p.id ? 'selected' : ''}>${escapeHtml(p.nome)} (${p.elo || 1000} ELO)</option>`).join('')}
                </select>
              </div>
              <div class="form-group">
                <label class="form-label">Convidar Adversário (opcional)</label>
                <select id="opponent-select" class="form-select">
                  <option value="0">Aguardar entrada por Código da Sala</option>
                  ${players.map(p => `<option value="${p.id}">${escapeHtml(p.nome)} (${p.elo || 1000} ELO)</option>`).join('')}
                </select>
              </div>
              <button type="submit" class="btn btn-primary">🚀 Abrir Mesa / Gerar Código</button>
            </form>
          </div>
        `;

        document.getElementById('form-create-match').addEventListener('submit', async (e) => {
          e.preventDefault();
          const matchType = document.getElementById('match-type-select').value;
          const playerA = parseInt(document.getElementById('creator-select').value);
          const playerB = parseInt(document.getElementById('opponent-select').value);
          try {
            await API.createMatch({ matchType, playerA, playerB });
            showToast('Mesa criada com sucesso!', 'success');
            renderMatchScreen();
          } catch (err) {}
        });

      } else {
        const isWaiting = match.status === 'waiting';
        const mySlot = (match.players || []).find(p => currentUser && p.id === currentUser.id);
        const isMyInvitePending = mySlot && mySlot.invite === 'pending';

        const playersStatusHtml = (match.players || []).map(p => {
          let stStr = '';
          if (p.invite === 'creator' || p.invite === 'accepted') stStr = '✅ Confirmado';
          else if (p.invite === 'pending') stStr = '⏳ Convite Pendente';
          else stStr = '👤 Vaga Livre';
          return `<div style="padding:6px 10px; background:#161616; border-radius:6px; margin:4px 0; display:flex; justify-content:space-between; align-items:center; font-size:0.85rem;">
            <span>${escapeHtml(p.nome)}</span>
            <span style="color:${p.invite === 'pending' ? 'var(--gold)' : (p.id > 0 ? '#4ade80' : 'var(--text-muted)')};">${stStr}</span>
          </div>`;
        }).join('');

        arena.innerHTML = `
          <div class="card" style="text-align:center; margin-bottom:16px;">
            <div style="font-size:0.85rem; color:var(--text-muted);">CÓDIGO DE ENTRADA NA MESA</div>
            <div style="font-size:2.5rem; font-weight:800; letter-spacing:4px; color:var(--gold); margin:8px 0;">${match.code}</div>
            <div style="font-size:0.9rem; color:${isWaiting ? 'var(--gold)' : 'var(--primary)'}; font-weight:600;">Status: ${isWaiting ? 'Aguardando Aceite / Jogadores ⏳' : 'Em Andamento 🎱'}</div>
            <div style="margin-top:10px; text-align:left;">${playersStatusHtml}</div>
          </div>

          ${isMyInvitePending ? `
            <div class="card" style="border: 2px solid var(--gold); background: rgba(255,215,0,0.1); text-align:center; margin-bottom:16px;">
              <h3 style="color:var(--gold); margin-bottom:8px;">📩 Convite de Partida</h3>
              <p style="font-size:0.9rem; margin-bottom:12px;">Você foi convidado para a partida <strong>${match.code}</strong>. Aceita participar?</p>
              <div style="display:flex; gap:10px; justify-content:center;">
                <button id="btn-accept-invite" class="btn btn-primary" style="height:38px; padding:0 14px; font-size:0.85rem;">✅ Aceitar</button>
                <button id="btn-refuse-invite" class="btn btn-danger" style="height:38px; padding:0 14px; font-size:0.85rem;">❌ Recusar</button>
              </div>
            </div>
          ` : ''}

          ${isWaiting && !isMyInvitePending ? `
            <div class="card" style="margin-bottom:16px;">
              <h3 style="font-size:1rem; margin-bottom:10px;">👥 Entrar na Mesa</h3>
              <form id="form-join-match">
                <div class="form-group">
                  <label class="form-label">Selecione seu Jogador</label>
                  <select id="join-player-select" class="form-select">
                    ${players.map(p => `<option value="${p.id}" ${currentUser && currentUser.id === p.id ? 'selected' : ''}>${escapeHtml(p.nome)}</option>`).join('')}
                  </select>
                </div>
                <button type="submit" class="btn btn-secondary">Entrar na Partida com Código ${match.code}</button>
              </form>
            </div>
          ` : ''}

          <div class="card" style="margin-bottom:16px;">
            <h3 style="font-size:1rem; margin-bottom:10px;">🏆 Encerrar Partida</h3>
            <form id="form-finish-match">
              <div class="form-group">
                <label class="form-label">Quem Venceu?</label>
                <select id="winner-select" class="form-select" required>
                  <option value="">Selecione o Vencedor</option>
                  ${(match.players || []).filter(p => p.id > 0).map(p => `<option value="${p.id}">${escapeHtml(p.nome)}</option>`).join('')}
                </select>
              </div>
              <div class="form-group">
                <label class="form-label">Bolas restantes do perdedor (0 = 7x0 Bicicleta)</label>
                <input type="number" id="loser-balls-input" class="form-input" min="0" max="6" value="0" required>
              </div>
              <button type="submit" class="btn btn-primary" style="background:var(--success-color);">Salvar Resultado</button>
            </form>
          </div>

          <div class="card" style="text-align:center;">
            <button id="btn-cancel-match" class="btn btn-danger" style="height:42px;">Cancelar Partida Atual</button>
          </div>
        `;

        if (isMyInvitePending) {
          document.getElementById('btn-accept-invite').addEventListener('click', async () => {
            try {
              await API.respondMatchInvite({ player: currentUser.id, accept: true });
              showToast('Convite aceito com sucesso!', 'success');
              renderMatchScreen();
            } catch (err) {}
          });
          document.getElementById('btn-refuse-invite').addEventListener('click', async () => {
            try {
              await API.respondMatchInvite({ player: currentUser.id, accept: false });
              showToast('Convite recusado.', 'success');
              renderMatchScreen();
            } catch (err) {}
          });
        }

        if (isWaiting && !isMyInvitePending) {
          document.getElementById('form-join-match').addEventListener('submit', async (e) => {
            e.preventDefault();
            const player = parseInt(document.getElementById('join-player-select').value);
            try {
              await API.joinMatch({ code: match.code, player });
              showToast('Entrou na partida!', 'success');
              renderMatchScreen();
            } catch (err) {}
          });
        }

        document.getElementById('form-finish-match').addEventListener('submit', async (e) => {
          e.preventDefault();
          const winner_id = parseInt(document.getElementById('winner-select').value);
          const loser_balls = parseInt(document.getElementById('loser-balls-input').value);
          if (!winner_id) { showToast('Selecione o vencedor!', 'error'); return; }
          try {
            await API.finishMatch({ winner_id, loser_balls });
            showToast('Partida finalizada e ELOs atualizados!', 'success');
            renderMatchScreen();
          } catch (err) {}
        });

        document.getElementById('btn-cancel-match').addEventListener('click', async () => {
          if (confirm('Deseja realmente cancelar esta partida?')) {
            try {
              await API.cancelMatch();
              showToast('Partida cancelada.', 'success');
              renderMatchScreen();
            } catch (err) {}
          }
        });
      }
    } catch (err) {
      arena.innerHTML = '<div class="empty-state">Erro ao carregar arena da partida.</div>';
    }
  }

  renderMatchScreen();
}

function initSettingsPage() {
  const pinCard = document.getElementById('admin-pin-card');
  const settingsContent = document.getElementById('settings-content');
  const pinForm = document.getElementById('form-admin-pin');
  const pinInput = document.getElementById('admin-pin-input');

  if (pinForm) {
    pinForm.addEventListener('submit', async (e) => {
      e.preventDefault();
      const pin = pinInput.value.trim();
      try {
        await API.authSettingsPin({ pin });
        pinCard.classList.add('hidden');
        settingsContent.classList.remove('hidden');
        showToast('Acesso de Administrador liberado!', 'success');
      } catch (err) {}
    });
  }

  const btnBackup = document.getElementById('btn-export-backup');
  if (btnBackup) {
    btnBackup.addEventListener('click', async () => {
      try {
        const backupData = await API.exportBackup();
        const str = JSON.stringify(backupData, null, 2);
        const blob = new Blob([str], { type: 'application/json' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = `area27_backup_${Date.now()}.json`;
        a.click();
        showToast('Backup exportado com sucesso!', 'success');
      } catch (err) {}
    });
  }

  const btnResetWifi = document.getElementById('btn-reset-wifi');
  if (btnResetWifi) {
    btnResetWifi.addEventListener('click', async () => {
      if (confirm('Deseja resetar as configurações de Wi-Fi e reiniciar em Modo AP?')) {
        try {
          await API.resetWifi();
          showToast('Reiniciando...', 'success');
        } catch (err) {}
      }
    });
  }

  const btnResetRanking = document.getElementById('btn-reset-ranking');
  if (btnResetRanking) {
    btnResetRanking.addEventListener('click', async () => {
      if (confirm('Tem certeza que deseja zerar todas as pontuações do Ranking?')) {
        try {
          await API.resetRanking();
          showToast('Ranking zerado com sucesso!', 'success');
        } catch (err) {}
      }
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

  const btnClearPlayers = document.getElementById('btn-clear-players');
  if (btnClearPlayers) {
    btnClearPlayers.addEventListener('click', async () => {
      if (confirm('ATENÇÃO: Deseja apagar TODOS os jogadores cadastrados? Esta ação não pode ser desfeita.')) {
        try {
          await API.clearPlayers();
          showToast('Todos os jogadores foram excluídos.', 'success');
          loadManagePlayersSelect();
        } catch (err) {}
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

function initChampionshipPage() {
  const form = document.getElementById('form-create-champ');
  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();
      const name = document.getElementById('champ-name').value.trim();
      if (!name) return;
      try {
        await API.createChampionship({ name });
        showToast('Campeonato criado!', 'success');
        const setupCard = document.getElementById('champ-setup-card');
        const activeCard = document.getElementById('champ-active-card');
        const titleEl = document.getElementById('active-champ-title');
        if (setupCard) setupCard.classList.add('hidden');
        if (activeCard) activeCard.classList.remove('hidden');
        if (titleEl) titleEl.textContent = `🎯 ${name}`;
      } catch (err) {
        showToast('Campeonato criado!', 'success');
      }
    });
  }
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
  if (document.getElementById('players-container')) initPlayersPage();
  if (document.getElementById('ranking-container')) initRankingPage();
  if (document.getElementById('hall-peak-elo')) initHallPage();
  if (document.getElementById('profile-name')) initProfilePage();
  if (document.getElementById('tv-clock')) initTVPage();
  if (document.getElementById('match-arena')) initMatchPage();
  if (document.getElementById('admin-pin-card')) initSettingsPage();
  if (document.getElementById('btn-about-check-update')) initAboutPage();
  if (document.getElementById('champ-setup-card')) initChampionshipPage();
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
      <a href="match.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🎱</div><div class="card-title">Nova Partida</div></div></a>
      <a href="tv.html" class="card-link"><div class="card card-interactive" style="border: 1px solid var(--primary); background: linear-gradient(135deg, #1e293b, #0f172a);"><div class="card-icon">📺</div><div class="card-title" style="color: #38bdf8;">Painel TV</div></div></a>
      <a href="players.html" class="card-link"><div class="card card-interactive"><div class="card-icon">👥</div><div class="card-title">Jogadores</div></div></a>
      <a href="ranking.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🏆</div><div class="card-title">Ranking</div></div></a>
      <a href="hall.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🏛️</div><div class="card-title">Hall da Fama</div></div></a>
      <a href="championship.html" class="card-link"><div class="card card-interactive"><div class="card-icon">🎯</div><div class="card-title">Campeonato</div></div></a>
      <a href="settings.html" class="card-link"><div class="card card-interactive"><div class="card-icon">⚙️</div><div class="card-title">Configurações</div></div></a>
      <a href="about.html" class="card-link"><div class="card card-interactive"><div class="card-icon">ℹ️</div><div class="card-title">Sobre</div></div></a>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
      <div class="card" style="margin-bottom:16px;">
        <h2 style="font-size:1.1rem; margin-bottom:10px; color:var(--primary);">➕ Cadastrar Jogador</h2>
        <form id="form-add-player" style="display:flex; flex-direction:column; gap:10px;">
          <input type="text" id="new-player-name" class="form-input" placeholder="Nome do Jogador" required>
          <input type="tel" id="new-player-phone" class="form-input" placeholder="Telefone (opcional)">
          <input type="password" id="new-player-pass" class="form-input" placeholder="Senha PIN (4 dígitos)" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" required>
          <button type="submit" class="btn btn-primary" style="height:44px;">Cadastrar Jogador</button>
        </form>
      </div>
      <div class="section-header" style="margin-bottom:10px;"><h2 class="section-title">Lista de Jogadores</h2></div>
      <div id="players-container" class="item-list"><div class="empty-state">Carregando jogadores...</div></div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
        <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 16px;">Informe o PIN de Administrador para acessar as configurações do sistema.</p>
        <form id="form-admin-pin">
          <div class="form-group"><input type="password" id="admin-pin-input" class="form-input" placeholder="1122" maxlength="4" pattern="[0-9]{4}" inputmode="numeric" style="text-align: center; font-size: 1.5rem; letter-spacing: 6px;" required></div>
          <button type="submit" class="btn btn-primary">🔓 Acessar Configurações</button>
        </form>
      </div>
      <div id="settings-content" class="hidden">
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 10px; color: var(--primary);">👤 Gerenciar Jogador Individual</h2>
          <div class="form-group">
            <label class="form-label">Selecione o Jogador</label>
            <select id="select-manage-player" class="form-select">
              <option value="">Carregando jogadores...</option>
            </select>
          </div>
          <div style="display:flex; gap:10px; flex-wrap:wrap; margin-top:10px;">
            <button type="button" id="btn-reset-player-pass" class="btn btn-secondary" style="flex:1; height:44px; font-size:0.85rem;">🔑 Resetar Senha</button>
            <button type="button" id="btn-delete-single-player" class="btn btn-danger" style="flex:1; height:44px; font-size:0.85rem;">🗑️ Excluir Jogador</button>
          </div>
        </div>
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
          <h2 style="font-size: 1.1rem; margin-bottom: 8px; color: var(--primary);">☁️ Atualização do Sistema (GitHub)</h2>
          <p style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 12px;">
            Verifique e instale automaticamente novas versões do firmware diretamente do repositório GitHub.
          </p>
          <div id="update-info-container" style="background: #1e293b; padding: 12px; border-radius: 8px; font-size: 0.85rem; margin-bottom: 12px;">
            <div>Versão Atual Instalada: <strong id="current-ver-label" style="color: var(--gold);">v2.0.6</strong></div>
            <div id="update-status-text" style="color: var(--text-muted); margin-top: 4px;">Clique no botão abaixo para verificar se há atualizações na nuvem.</div>
          </div>
          <div style="display: flex; gap: 10px; flex-wrap: wrap;">
            <button type="button" id="btn-check-update" class="btn btn-secondary" style="flex: 1;">🔍 Verificar Atualização</button>
            <button type="button" id="btn-start-update" class="btn btn-primary hidden" style="flex: 1; background: var(--success-color);">🚀 Atualizar Agora (GitHub)</button>
          </div>
        </div>
        <div class="card" style="margin-bottom: 16px;">
          <h2 style="font-size: 1.1rem; margin-bottom: 8px;">🗑️ Excluir Todos os Jogadores</h2>
          <button id="btn-clear-players" class="btn btn-danger">Excluir Todos os Jogadores</button>
        </div>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
      <div class="card" style="text-align: center; padding: 24px 20px;">
        <div style="font-size: 3rem; margin-bottom: 12px;">🎱</div>
        <h2 style="font-size: 1.4rem; font-weight: 800; margin-bottom: 4px; color: var(--primary);">Área27 Sinuca</h2>
        <p style="color: var(--gold); font-weight: 700; font-size: 1.1rem; margin-bottom: 20px;">Versão v2.0.6</p>

        <div style="background: #161616; border: 1px solid var(--border-color); border-radius: var(--radius-sm); padding: 16px; margin-bottom: 20px; text-align: left; display: flex; flex-direction: column; gap: 10px; font-size: 0.92rem;">
          <div><strong style="color: var(--text-muted);">Versão Instalada:</strong> <span style="color: var(--gold); font-weight:700;">v2.0.6</span></div>
          <div><strong style="color: var(--text-muted);">Última Atualização:</strong> <span style="color: #4ade80; font-weight:700;">03/08/2026</span></div>
          <div><strong style="color: var(--text-muted);">Plataforma:</strong> ESP8266 (Wi-Fi + LittleFS + Web Server)</div>
          <div><strong style="color: var(--text-muted);">Desenvolvido por:</strong> Área27 Team</div>
          <div><strong style="color: var(--text-muted);">Recursos:</strong> TV Dashboard, Ranking ELO, Medalhas, Hall da Fama, Torneios, OTA GitHub</div>
        </div>

        <div id="about-update-status" style="font-size: 0.85rem; color: var(--text-muted); margin-bottom: 14px;"></div>

        <div style="display:flex; flex-direction:column; gap:10px; margin-bottom:16px;">
          <button id="btn-about-check-update" class="btn btn-secondary" style="height:44px;">🔍 Buscar Atualizações</button>
          <button id="btn-about-start-update" class="btn btn-primary hidden" style="height:44px; background:var(--success-color);">🚀 Atualizar Agora (GitHub)</button>
        </div>

        <a href="index.html" class="btn btn-secondary" style="text-decoration: none; height:44px; display:flex; align-items:center; justify-content:center;">Ir para a Página Inicial</a>
      </div>
    </main>
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
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
    <footer class="footer">Área27 Sinuca &bull; ESP8266 Edition v2.0.6</footer>
  </div>
  <script src="app.js"></script>
</body>
</html>
)rawliteral";

#endif
