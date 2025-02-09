//
// Created by Cuent on 2/9/2025.
//

#ifndef PUSHER_H
#define PUSHER_H
#include "TextureRenderer.h"



class Pusher {
public:
    Pusher(SDL_Renderer *m_renderer);

    void LerpVector(float x1, float y1, float x2, float y2, float alpha, int &outX, int &outY);

#define VELOCITY_MULTIPLIER 0.05;

    void UpdatePusherPosition(float deltaTime);

    void RenderPusher();

    TextureRenderer *GetTexture();

    float GetVelX();

    float GetVelY();

    int GetDiameter();

private:
    TextureRenderer *pusher_texture;
    const int PUSHER_DIAMETER = 66;
    int x;
    int y;
    float previusX = 0;
    float previusY = 0;
    float velX = 0;
    float velY = 0;
};



#endif //PUSHER_H
