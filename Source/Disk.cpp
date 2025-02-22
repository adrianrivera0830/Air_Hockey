//
// Created by Cuent on 2/9/2025.
//

#include "../Headers/Disk.h"

Disk::Disk(SDL_Renderer *m_renderer) {
    const char* path = "../images/ball.png";
    diskTexture = new TextureRenderer(m_renderer, path);
    diskTexture->SetPosition(400, 400);
    diskTexture->SetSize(DISK_DIAMETER, DISK_DIAMETER);
}

void Disk::HitDisk(float radians) {
    float speed = sqrt(velX * velX + velY * velY);

    velX = speed * cos(radians);
    velY = speed * sin(radians);
}

void Disk::UpdateVelocity() {
    velX *= (1 - friction);
    velY *= (1 - friction);
}

void Disk::UpdatePosition(float deltaTime) {
    x += (velX * deltaTime);
    y += (velY * deltaTime);
    OnDiskEdgeCollision();
    diskTexture->SetPosition(x, y);
}

void Disk::RenderDisk() {
    diskTexture->RenderTexture();
}

void Disk::ApplyImpulse(float pusherVelX, float pusherVelY) {
    velX += pusherVelX;
    velY += pusherVelY;
}

void Disk::OnDiskEdgeCollision() {
    // int margin = EDGE_MARGIN;
    // int fullX = x + DISK_DIAMETER;
    // int fullY = y + DISK_DIAMETER;
    //
    // if (x < margin) {
    //     x = margin;
    //     velX = -velX;
    // }
    //
    // //Permitir colision en el lado izquierda de la porteria superior
    // else if (x < GOALPOAST_START && fullX > GOALPOAST_START && y < margin) {
    //     //std::cout << "(" << x << "," << y << ")" << std::endl;
    //     x = GOALPOAST_START;
    //     velX = -velX;
    // }
    // else if (x < GOALPOAST_START + GOALPOAST_LENGTH && fullX > GOALPOAST_START + GOALPOAST_LENGTH && y < margin) {
    //     x = GOALPOAST_START + GOALPOAST_LENGTH -DISK_DIAMETER;
    //     velX = -velX;
    // }
    // else if (fullX > SCREEN_WIDTH - margin) {
    //     x = SCREEN_WIDTH - DISK_DIAMETER - margin;
    //     velX = -velX;
    // }
    //
    //
    // //Permitir colision en el lado izquierda de la porteria inferior
    //
    // else if (x < GOALPOAST_START && fullX > GOALPOAST_START && fullY > SCREEN_HEIGHT - margin) {
    //     x = GOALPOAST_START;
    //     velX = -velX;
    // }
    //
    // if (y < margin && fullX < GOALPOAST_START) {
    //     y = margin;
    //     velY = -velY;
    // }
    // else if (y < margin && x > GOALPOAST_START + GOALPOAST_LENGTH) {
    //     y = margin;
    //     velY = -velY;
    // }
    //
    // else if (fullY > SCREEN_HEIGHT - margin) {
    //     y = SCREEN_HEIGHT - DISK_DIAMETER - margin;
    //
    //     velY = -velY;
    // }
    // else if (y < margin && x > GOALPOAST_START + GOALPOAST_LENGTH) {
    //     y = margin;
    //     velY = -velY;
    // }
    // else if (x > GOALPOAST_START && y > SCREEN_HEIGHT - margin) {
    //     x = GOALPOAST_START;
    //     velX = -velX;
    // }

    // if (fullX > SCREEN_WIDTH - margin) {
    //     x = SCREEN_WIDTH - DISK_DIAMETER - margin;
    //     velX = -velX;
    // }
    // else if (x < 0 + margin) {
    //     x = margin;
    //     velX = -velX;
    //
    // }
    //
    // bool inGoalPost = (x > GOALPOAST_START && fullX < GOALPOAST_START + GOALPOAST_LENGTH);
    //
    //  if ((fullY > SCREEN_HEIGHT - margin) && !inGoalPost ) {
    //      y = SCREEN_HEIGHT - DISK_DIAMETER - margin;
    //      velY = -velY;
    //     //y = SCREEN_HEIGHT - (BALL_DIAMETER);
    // } else if (y  < margin && !inGoalPost) {
    //     y = margin;
    //     velY = -velY;
    //
    // }
}

void Disk::OnDiskMalletCollision(float radians, int radius) {
    float degrees = radians * (180.0 / 3.1416);


    float dirX = (float) cos(radians) * (radius + RADIUS_OFFSET);
    float dirY = (float) sin(radians) * (radius + RADIUS_OFFSET);
    x += dirX;
    y += dirY;
}
