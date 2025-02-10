//
// Created by adrian on 2/10/25.
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Headers/Disk.h"
#include "../Headers/Pusher.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000
#define EDGE_MARGIN 30;
#define GOALPOAST_START 320
#define GOALPOAST_LENGTH 160

const int FPS = 1000;
const int FRAME_DELAY = 1000 / FPS;

const int HANDLE_RADIUS = 56;
const int BALL_RADIUS = 36;


class Game {
public:
    void GameLoop();
    bool Initialize();


    void CleanUp();
    //SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetWindowGrab(window, SDL_TRUE);


    ~Game();

    Disk *disk = nullptr;
    Pusher *pusher = nullptr;
private:
};



#endif //GAME_H
