//
// Created by Cuent on 2/9/2025.
//

#ifndef PUSHER_H
#define PUSHER_H
#include "TextureRenderer.h"
#include "Structs.h"


class Pusher {
public:
    Pusher(SDL_Renderer *m_renderer, int diameter, int velocityMultiplier);

    void LerpVector(float x1, float y1, float x2, float y2, float alpha, int &outX, int &outY);

    void SetPusherPosition(float deltaTime, int x, int y);

    void RenderPusher();

    TextureRenderer *GetTexture();

    Velocity GetVelocity();


    SDL_Rect GetRect();

private:
    TextureRenderer *pusher_texture;

    Position previousPos;
    Position currentPos;

    Velocity velocity;
    int velMult;
};



#endif //PUSHER_H
