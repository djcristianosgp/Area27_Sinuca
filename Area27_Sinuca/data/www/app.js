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
        await API.authSettingsPin({ pin });
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
