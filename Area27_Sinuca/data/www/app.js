/**
 * Área27 Sinuca - Application Core Logic (ESP8266 Optimized)
 * Vanilla JS REST Client & UI Renderer
 */

const API = {
  async request(endpoint, options = {}) {
    try {
      const response = await fetch(endpoint, {
        headers: { 'Content-Type': 'application/json', ...(options.headers || {}) },
        ...options
      });
      if (!response.ok) {
        throw new Error(`Erro na requisição: ${response.status}`);
      }
      return await response.json();
    } catch (err) {
      console.error(`API Error [${endpoint}]:`, err);
      showToast(err.message || 'Falha ao conectar com o servidor', 'error');
      throw err;
    }
  },

  getPlayers() {
    return this.request('/players');
  },

  addPlayer(data) {
    return this.request('/players', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  },

  getRanking() {
    return this.request('/ranking');
  },

  registerMatch(data) {
    return this.request('/match', {
      method: 'POST',
      body: JSON.stringify(data)
    });
  }
};

/**
 * Toast Notification Manager
 */
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
          <div class="player-stats">
            <span class="badge-elo">${p.elo || 1000} ELO</span>
            <div class="record">${p.vitorias || 0}V / ${p.derrotas || 0}D</div>
          </div>
        </div>
      `).join('');
    } catch (err) {
      playerList.innerHTML = `<div class="empty-state">Erro ao carregar lista de jogadores.</div>`;
    }
  }

  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nomeInput = document.getElementById('nome');
      const telInput = document.getElementById('telefone');

      const nome = nomeInput.value.trim();
      const telefone = telInput.value.trim();

      if (!nome) {
        showToast('Informe o nome do jogador', 'error');
        return;
      }

      const submitBtn = form.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.addPlayer({ nome, telefone });
        showToast('Jogador cadastrado com sucesso!', 'success');
        nomeInput.value = '';
        telInput.value = '';
        await loadPlayers();
      } catch (err) {
        // Handled in API.request
      } finally {
        submitBtn.disabled = false;
      }
    });
  }

  if (playerList) {
    loadPlayers();
  }
}

/**
 * Page: Nova Partida (match.html)
 */
async function initMatchPage() {
  const form = document.getElementById('form-match');
  const selectA = document.getElementById('playerA');
  const selectB = document.getElementById('playerB');
  const selectWinner = document.getElementById('winner');

  let playersCache = [];

  function updateWinnerOptions() {
    const valA = selectA.value;
    const valB = selectB.value;

    selectWinner.innerHTML = '<option value="">Selecione o Vencedor</option>';

    if (!valA || !valB) {
      selectWinner.disabled = true;
      return;
    }

    if (valA === valB) {
      showToast('Escolha dois jogadores diferentes!', 'error');
      selectWinner.disabled = true;
      return;
    }

    selectWinner.disabled = false;
    const playerObjA = playersCache.find(p => String(p.id) === String(valA));
    const playerObjB = playersCache.find(p => String(p.id) === String(valB));

    if (playerObjA) {
      const optA = document.createElement('option');
      optA.value = playerObjA.id;
      optA.textContent = playerObjA.nome;
      selectWinner.appendChild(optA);
    }

    if (playerObjB) {
      const optB = document.createElement('option');
      optB.value = playerObjB.id;
      optB.textContent = playerObjB.nome;
      selectWinner.appendChild(optB);
    }
  }

  async function loadPlayersDropdown() {
    try {
      playersCache = await API.getPlayers();

      selectA.innerHTML = '<option value="">Selecione o Jogador A</option>';
      selectB.innerHTML = '<option value="">Selecione o Jogador B</option>';

      playersCache.forEach(p => {
        const opt1 = document.createElement('option');
        opt1.value = p.id;
        opt1.textContent = p.nome;
        selectA.appendChild(opt1);

        const opt2 = document.createElement('option');
        opt2.value = p.id;
        opt2.textContent = p.nome;
        selectB.appendChild(opt2);
      });
    } catch (err) {
      showToast('Erro ao carregar lista de jogadores', 'error');
    }
  }

  if (selectA && selectB) {
    selectA.addEventListener('change', updateWinnerOptions);
    selectB.addEventListener('change', updateWinnerOptions);
  }

  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();

      const playerA = Number(selectA.value);
      const playerB = Number(selectB.value);
      const winner = Number(selectWinner.value);

      if (!playerA || !playerB) {
        showToast('Selecione ambos os jogadores', 'error');
        return;
      }

      if (playerA === playerB) {
        showToast('Os jogadores A e B devem ser diferentes', 'error');
        return;
      }

      if (!winner) {
        showToast('Selecione o vencedor da partida', 'error');
        return;
      }

      const submitBtn = form.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.registerMatch({ playerA, playerB, winner });
        showToast('Partida registrada com sucesso.', 'success');
        form.reset();
        selectWinner.disabled = true;
      } catch (err) {
        // Handled in API
      } finally {
        submitBtn.disabled = false;
      }
    });

    loadPlayersDropdown();
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

    // Sort descending by ELO
    const sorted = [...list].sort((a, b) => (b.elo || 0) - (a.elo || 0));

    rankingContainer.innerHTML = sorted.map((p, idx) => {
      const pos = idx + 1;
      let badge = `${pos}º`;
      let rankClass = '';

      if (pos === 1) {
        badge = '🥇';
        rankClass = 'top-1 rank-1';
      } else if (pos === 2) {
        badge = '🥈';
        rankClass = 'top-2 rank-2';
      } else if (pos === 3) {
        badge = '🥉';
        rankClass = 'top-3 rank-3';
      }

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
 * Helper: XSS Prevention
 */
function escapeHtml(str) {
  if (!str) return '';
  return String(str)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;');
}

// Global page initialization based on DOM elements
document.addEventListener('DOMContentLoaded', () => {
  if (document.getElementById('form-player')) initPlayersPage();
  if (document.getElementById('form-match')) initMatchPage();
  if (document.getElementById('ranking-container')) initRankingPage();
});
