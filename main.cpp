#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm> // Para std::min y std::max

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000

const int FPS = 144;
const int FRAME_DELAY = 1000/FPS;

const int HANDLE_RADIUS = 56;
const int BALL_RADIUS = 36;

float deltaTime = 0.0f;


SDL_Window* window;
SDL_Renderer* renderer;

class Ball {
public:
    void HitBall() {
        velY = 500;
    }
    void UpdateVelocity() {
        velX *= (1-friction);
        velY *= (1-friction);

    }
    void UpdatePosition(float deltaTime) {
        x += (velX * deltaTime);
        y += (velY * deltaTime);
    }

    float friction = 0.008f;
    float x = SCREEN_WIDTH/2;
    float y = SCREEN_HEIGHT/2;
    float velX = 0;
    float velY = 0;
private:

};

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


void GameLoop() {

    SDL_Surface* ballSurface = IMG_Load("../images/ball.png");
    SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer,ballSurface);
    if (!ballTexture) {
        CleanUp();
    }

    SDL_Surface* handleSurface = IMG_Load("../images/handle.png");
    SDL_Texture* handleTexure = SDL_CreateTextureFromSurface(renderer,handleSurface);

    SDL_FreeSurface(ballSurface);

    SDL_Rect handleRect = {
        (400 ) / 2,
        (400) / 2,
        HANDLE_RADIUS,
        HANDLE_RADIUS
    };

    Ball* ball = new Ball();

    SDL_Rect ballRect = {
        static_cast<int>(ball->x),  // Usa `->` porque ball es un puntero
        static_cast<int>(ball->y),
        BALL_RADIUS,
        BALL_RADIUS
    };


    int handlePosX,handlePosY;

    Uint32 lastTime = SDL_GetTicks(); // Tiempo del último frame

    bool running = true;

    SDL_Event event;
    while (running) {

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convertir a segundos
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) { // Si se presiona la tecla "A"
                    ball->HitBall(); // Llamar a HitBall()
                }
            }

            SDL_GetMouseState(&handlePosX, &handlePosY);

            handlePosY = std::max(SCREEN_HEIGHT/2,handlePosY);
            float newX = handleRect.x;
            float newY = handleRect.y;
            LerpVector(newX, newY, static_cast<float>(handlePosX), static_cast<float>(handlePosY), 0.15f, newX, newY);
            handleRect.x = static_cast<int>(newX);
            handleRect.y = static_cast<int>(newY);


        }

        ball->UpdateVelocity();  // Aplica la fricción a la velocidad
        ball->UpdatePosition(deltaTime); // Actualiza la posición con la velocidad
        ballRect.x = static_cast<int>(ball->x);
        ballRect.y = static_cast<int>(ball->y);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect); // Renderizar la textura
        //SDL_RenderCopy(renderer, handleTexure, NULL, &handleRect); // Renderizar la textura
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - currentTime;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Esperar el tiempo restante
        }
    }
}

int main(int argc, char* argv[]) {
    if (!Initialize()) {
        return 1;
    }

    //SDL_ShowCursor(SDL_DISABLE);




    GameLoop();

    CleanUp();

    return 0;
}
