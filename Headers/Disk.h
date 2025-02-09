//
// Created by Cuent on 2/9/2025.
//

#ifndef DISK_H
#define DISK_H
#include <cmath>
#include "TextureRenderer.h"

class Disk {
public:
    Disk(SDL_Renderer *m_renderer);

    void HitDisk(float radians);

    void UpdateVelocity();

    void UpdatePosition(float deltaTime);

    void RenderDisk();

    void ApplyImpulse(float pusherVelX, float pusherVelY);

    void OnDiskEdgeCollission();

#define RADIUS_OFFSET -30

    void OnDiskMalletCollision(float radians, int radius);


    TextureRenderer *GetTexture() {
        return diskTexture;
    }

private:
    TextureRenderer *diskTexture;

    float friction = 0.003f;
    const int DISK_DIAMETER = 36;
    float x = 400;
    float y = 400;
    float velX = 0;
    float velY = 0;
};



#endif //DISK_H
