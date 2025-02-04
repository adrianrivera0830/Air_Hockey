#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm> // Para std::min y std::max

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000

const int FPS = 144;
const int FRAME_DELAY = 1000/FPS;

const int BALL_RADIUS = 56;
SDL_Window* window;
SDL_Renderer* renderer;

bool Initialize() {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // Inicializar SDL_image para manejar imágenes PNG
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Error al inicializar SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Inicializar SDL_ttf para manejo de fuentes
    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Crear una ventana
    window = SDL_CreateWindow("Ventana SDL2",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT ,
                              SDL_WINDOW_SHOWN);
    if (!window) {

        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Crear el renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void LerpVector(float x1, float y1, float x2, float y2, float alpha, float& outX, float& outY) {
    outX = (1.0f - alpha) * x1 + alpha * x2;
    outY = (1.0f - alpha) * y1 + alpha * y2;
}


void Lerp(float x, float target, float alpha, float& out) {
    out = (1 - alpha) * x + alpha * target;
}

void CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    if (!Initialize()) {
        return 1;
    }

    //SDL_ShowCursor(SDL_DISABLE);


    SDL_Surface* ballSurface = IMG_Load("../images/ball.png");
    SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer,ballSurface);
    if (!ballTexture) {
        CleanUp();
    }

    SDL_Surface* handleSurface = IMG_Load("../images/handle.png");
    SDL_Texture* handleTexure = SDL_CreateTextureFromSurface(renderer,handleSurface);

    SDL_FreeSurface(ballSurface);


    // Definir el rectángulo destino centrado en la ventana
    SDL_Rect dstRect = {
        (400 ) / 2,
        (400) / 2,
        BALL_RADIUS,
        BALL_RADIUS
    };


    int handlePosX,handlePosY;
    bool running = true;

    SDL_Event event;
    while (running) {

        Uint32 frameStart = SDL_GetTicks(); // Tiempo inicial del frame


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            SDL_GetMouseState(&handlePosX, &handlePosY);

            handlePosY = std::max(SCREEN_HEIGHT/2,handlePosY);
            float newX = dstRect.x;
            float newY = dstRect.y;
            LerpVector(newX, newY, static_cast<float>(handlePosX), static_cast<float>(handlePosY), 0.15f, newX, newY);
            dstRect.x = static_cast<int>(newX);
            dstRect.y = static_cast<int>(newY);


        }
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, handleTexure, NULL, &dstRect); // Renderizar la textura
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Esperar el tiempo restante
        }
    }

    CleanUp();

    return 0;
}
