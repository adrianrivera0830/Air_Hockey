//
// Created by Cuent on 2/9/2025.
//

#include "../Headers/Pusher.h"


Pusher::Pusher(SDL_Renderer *m_renderer, int diameter, int velocityMultiplier) :  velMult(velocityMultiplier){
    const char *path = "../images/handle.png";
    pusher_texture = new TextureRenderer(m_renderer, path);
    pusher_texture->SetSize(diameter, diameter);
}

void Pusher::LerpVector(float x1, float y1, float x2, float y2, float alpha, int &outX, int &outY) {
    outX = (1.0f - alpha) * x1 + alpha * x2;
    outY = (1.0f - alpha) * y1 + alpha * y2;
}

void Pusher::SetPusherPosition(float deltaTime,int x, int y) {
    previousPos.x = x;
    previousPos.y = y;

    LerpVector(previousPos.x, previousPos.y, x, y, .15f, currentPos.x, currentPos.y);

    if (deltaTime != 0) {
        velocity.x = ((currentPos.x - previousPos.x) / deltaTime) * velMult;
        velocity.y = ((currentPos.y - previousPos.y) / deltaTime) * velMult;
    }

    //y = std::max(SCREEN_HEIGHT / 2, y);
    pusher_texture->SetPosition(currentPos.x,currentPos.y);
}

void Pusher::RenderPusher() {
    pusher_texture->RenderTexture();
}

TextureRenderer * Pusher::GetTexture() {
    return pusher_texture;
}

Velocity Pusher::GetVelocity() {
    return velocity;
}


SDL_Rect Pusher::GetRect() {
    return pusher_texture->GetRect();
}

