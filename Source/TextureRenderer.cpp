//
// Created by Cuent on 2/9/2025.
//

#include "../Headers/TextureRenderer.h"

TextureRenderer::TextureRenderer(SDL_Renderer *renderer, std::string path): m_renderer(renderer) {
    LoadTexture(path.c_str());
}

void TextureRenderer::LoadTexture(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Error cargando la imagen: " << path << " - " << IMG_GetError() << "\n";
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!m_texture) {
        std::cerr << "La textura de " << path << "no se pudo crear\n";
    }

    SDL_FreeSurface(surface);

    assert(m_texture);
}

void TextureRenderer::SetPosition(int x, int y) {
    m_rect.x = x;
    m_rect.y = y;
}

void TextureRenderer::SetSize(int width, int height) {
    m_rect.w = width;
    m_rect.h = height;
}

void TextureRenderer::RenderTexture() {
    SDL_RenderCopy(m_renderer, m_texture,NULL, &m_rect);
}

TextureRenderer::~TextureRenderer() {
    UnloadTexture();
}

void TextureRenderer::UnloadTexture() {
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}
