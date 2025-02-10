//
// Created by adrian on 2/10/25.
//

#include "../Headers/Game.h"

SDL_Window *window;
SDL_Renderer *renderer;

float deltaTime;
bool Game::Initialize() {
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
                              SCREEN_WIDTH, SCREEN_HEIGHT,
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

bool DetectCollision(SDL_Rect rect1, SDL_Rect rect2) {
    // Obtener los centros de los círculos
    float pusherCenterX = rect1.x + rect1.w / 2.0f;
    float pusherCenterY = rect1.y + rect1.h / 2.0f;
    float ballCenterX = rect2.x + rect2.w / 2.0f;
    float ballCenterY = rect2.y + rect2.h / 2.0f;

    // Radio de los círculos
    float pusherRadius = rect1.w / 2.0f; // Asumimos que w == h (diámetro)
    float ballRadius = rect2.w / 2.0f;

    // Distancia entre los centros
    float distance = std::sqrt(std::pow(pusherCenterX - ballCenterX, 2) +
                               std::pow(pusherCenterY - ballCenterY, 2));

    // Verificar colisión
    if (distance <= (pusherRadius + ballRadius)) {
        return true;
    }
    return false;
}

float IncidenceAngle(SDL_Rect rect1, SDL_Rect rect2) {
    float rect1CenterX = rect1.x + rect1.w / 2.0f;
    float rect1CenterY = rect1.y + rect1.h / 2.0f;
    float rect2CenterX = rect2.x + rect2.w / 2.0f;
    float rect2CenterY = rect2.y + rect2.h / 2.0f;
    float angle = atan2(rect1CenterY - rect2CenterY, rect1CenterX - rect2CenterX);
    return angle;
}


void Game::CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void Game::GameLoop() {

    disk = new Disk(renderer);
    pusher = new Pusher(renderer);
    TextureRenderer *bg = new TextureRenderer(renderer, "../images/map.png");
    bg->SetPosition(0, 0);
    bg->SetSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    int handlePosX, handlePosY;

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
            }
        }
        pusher->UpdatePusherPosition(deltaTime);
        disk->UpdateVelocity(); // Aplica la fricción a la velocidad
        disk->UpdatePosition(deltaTime); // Actualiza la posición con la velocidad

        SDL_Rect pusherRect = pusher->GetTexture()->GetRect();
        SDL_Rect diskRect = disk->GetTexture()->GetRect();
        bool collision = DetectCollision(pusherRect, diskRect);
        if (collision) {
            disk->OnDiskMalletCollision(IncidenceAngle(diskRect, pusherRect), pusher->GetDiameter() / 2);
            disk->HitDisk(IncidenceAngle(diskRect, pusherRect));
            disk->ApplyImpulse(pusher->GetVelX(), pusher->GetVelY());
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        bg->RenderTexture();
        disk->RenderDisk();
        pusher->RenderPusher();
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - currentTime;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Esperar el tiempo restante
        }
    }
}

Game::~Game() {
    CleanUp();
}
