//
// Created by Cuent on 2/9/2025.
//

#include "../Headers/Pusher.h"

Pusher::Pusher(SDL_Renderer *m_renderer) {
    pusher_texture = new TextureRenderer(m_renderer, "../images/handle.png");
    pusher_texture->SetPosition(400, 600);
    pusher_texture->SetSize(PUSHER_DIAMETER, PUSHER_DIAMETER);
}

void Pusher::LerpVector(float x1, float y1, float x2, float y2, float alpha, int &outX, int &outY) {
    outX = (1.0f - alpha) * x1 + alpha * x2;
    outY = (1.0f - alpha) * y1 + alpha * y2;
}

void Pusher::UpdatePusherPosition(float deltaTime,int newX, int newY) {
    previusX = x;
    previusY = y;



    LerpVector(previusX, previusY, newX, newY, .15f, x, y);


    velX = ((x - previusX) / deltaTime) * VELOCITY_MULTIPLIER;
    velY = ((y - previusY) / deltaTime) * VELOCITY_MULTIPLIER;


    //y = std::max(SCREEN_HEIGHT / 2, y);
    pusher_texture->SetPosition(x, y);
    RenderPusher();
}

void Pusher::RenderPusher() {
    pusher_texture->RenderTexture();
}

TextureRenderer * Pusher::GetTexture() {
    return pusher_texture;
}

float Pusher::GetVelX() { return velX; }

float Pusher::GetVelY() { return velY; }

int Pusher::GetDiameter() { return PUSHER_DIAMETER; }

int Pusher::GetX() {
    return  x;
}

int Pusher::GetY() {
    return  y;
}
