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

  deletePlayer(id) {
    return this.request('/players/delete', {
      method: 'POST',
      body: JSON.stringify({ id })
    });
  },

  clearPlayers() {
    return this.request('/players/clear', {
      method: 'POST'
    });
  },

  resetRanking() {
    return this.request('/ranking/reset', {
      method: 'POST'
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
  },

  resetWifi() {
    return this.request('/wifi/reset', {
      method: 'POST'
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
      playerList.innerHTML = `<div class="empty-state">Erro ao carregar lista de jogadores.</div>`;
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
      const valA = selectA ? selectA.value : '';
      const valB = selectB ? selectB.value : '';

      playersCache = await API.getPlayers();

      if (selectA && selectB) {
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

        if (valA) selectA.value = valA;
        if (valB) selectB.value = valB;

        updateWinnerOptions();
      }
    } catch (err) {
      showToast('Erro ao carregar lista de jogadores', 'error');
    }
  }

  if (formQuickPlayer) {
    formQuickPlayer.addEventListener('submit', async (e) => {
      e.preventDefault();
      const nomeInput = document.getElementById('quick-nome');
      const telInput = document.getElementById('quick-telefone');

      const nome = nomeInput.value.trim();
      const telefone = telInput.value.trim();

      if (!nome) {
        showToast('Informe o nome do jogador', 'error');
        return;
      }

      const submitBtn = formQuickPlayer.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        const res = await API.addPlayer({ nome, telefone });
        showToast(`Jogador '${nome}' cadastrado com sucesso!`, 'success');
        nomeInput.value = '';
        telInput.value = '';

        await loadPlayersDropdown();

        if (res && res.id) {
          if (!selectA.value) {
            selectA.value = res.id;
          } else if (!selectB.value && selectA.value != res.id) {
            selectB.value = res.id;
          }
          updateWinnerOptions();
        }
      } catch (err) {
        // Handled in API
      } finally {
        submitBtn.disabled = false;
      }
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

      const submitBtn = formMatch.querySelector('button[type="submit"]');
      submitBtn.disabled = true;

      try {
        await API.registerMatch({ playerA, playerB, winner });
        showToast('Partida registrada com sucesso.', 'success');
        formMatch.reset();
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
 * Page: Settings (settings.html)
 */
function initSettingsPage() {
  const resetWifiBtn = document.getElementById('btn-reset-wifi');
  const resetRankingBtn = document.getElementById('btn-reset-ranking');
  const clearPlayersBtn = document.getElementById('btn-clear-players');

  if (resetWifiBtn) {
    resetWifiBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente resetar a rede Wi-Fi? O ESP8266 reiniciará no modo Ponto de Acesso (Area27-Sinuca-Config).')) {
        try {
          await API.resetWifi();
          showToast('Wi-Fi resetado! Reiniciando no modo AP...', 'success');
        } catch (e) {}
      }
    });
  }

  if (resetRankingBtn) {
    resetRankingBtn.addEventListener('click', async () => {
      if (confirm('Deseja realmente zerar todas as estatísticas do ranking? (Os jogadores cadastrados serão mantidos)')) {
        try {
          await API.resetRanking();
          showToast('Estatísticas do ranking zeradas!', 'success');
        } catch (e) {}
      }
    });
  }

  if (clearPlayersBtn) {
    clearPlayersBtn.addEventListener('click', async () => {
      if (confirm('ATENÇÃO: Deseja realmente EXCLUIR TODOS OS JOGADORES? Esta ação não pode ser desfeita.')) {
        try {
          await API.clearPlayers();
          showToast('Todos os jogadores foram excluídos com sucesso!', 'success');
        } catch (e) {}
      }
    });
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

document.addEventListener('DOMContentLoaded', () => {
  if (document.getElementById('form-player')) initPlayersPage();
  if (document.getElementById('form-match') || document.getElementById('form-quick-player')) initMatchPage();
  if (document.getElementById('ranking-container')) initRankingPage();
  if (document.getElementById('btn-reset-wifi') || document.getElementById('btn-clear-players')) initSettingsPage();
});
