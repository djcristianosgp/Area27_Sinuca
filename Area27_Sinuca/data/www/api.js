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
