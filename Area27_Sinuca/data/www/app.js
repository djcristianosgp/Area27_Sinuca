/**
 * Área27 Sinuca - Application Core Logic
 * Session Management, Match Control, Room Code Linking & ELO Ranking
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

  getPlayers() {
    return this.request('/players');
  },

  registerPlayer(data) {
    return this.request('/players', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  loginPlayer(data) {
    return this.request('/players/login', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  deletePlayer(id) {
    return this.request('/players/delete', {
      method: 'POST',
      body: JSON.stringify({ id })
    });
  },

  clearPlayers() {
    return this.request('/players/clear', { method: 'POST' });
  },

  resetRanking() {
    return this.request('/ranking/reset', { method: 'POST' });
  },

  getRanking() {
    return this.request('/ranking');
  },

  authSettingsPin(data) {
    return this.request('/settings/auth', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  createMatch(data) {
    return this.request('/match/create', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  joinMatch(data) {
    return this.request('/match/join', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  respondMatchInvite(data) {
    return this.request('/match/respond', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  getActiveMatch() {
    return this.request('/match/active');
  },

  finishMatch(data) {
    return this.request('/match/finish', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  cancelMatch() {
    return this.request('/match/cancel', { method: 'POST' });
  },

  resetWifi() {
    return this.request('/wifi/reset', { method: 'POST' });
  }
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

/**
 * Page: Modo Partida (match.html)
 */
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
    // Team 1 vs Team 2
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
    // Individual (2P or 3P)
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
      // Check if logged in user has a pending invite
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

      // Render Roster List
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

      if (pin !== '0000') {
        showToast('PIN de Administrador incorreto (PIN: 0000)', 'error');
        return;
      }

      try {
        await API.authSettingsPin({ pin });
        sessionStorage.setItem('area27_admin_auth', 'true');
        showToast('Acesso administrativo liberado com sucesso!', 'success');
        adminCard.classList.add('hidden');
        settingsContent.classList.remove('hidden');
      } catch (err) {
        // Handled in API
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
