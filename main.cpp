#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm> // Para std::min y std::max
#include <cassert>
#include <vector>
#include <cmath> // Para sqrt y pow
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000

const int FPS = 1000;
const int FRAME_DELAY = 1000 / FPS;

const int HANDLE_RADIUS = 56;
const int BALL_RADIUS = 36;

float deltaTime = 0.0f;


SDL_Window *window;
SDL_Renderer *renderer;

class TextureRenderer {
public:
    TextureRenderer(SDL_Renderer* renderer, char* path) : m_renderer(renderer){
        LoadTexture(path);
    }

    void LoadTexture(char * path) {
        SDL_Surface* surface = IMG_Load(path);
        if (!surface) {
            std::cerr << "Error cargando la imagen: " << path << " - " << IMG_GetError() << "\n";
            return;
        }

        m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (!m_texture) {
            std::cerr << "La textura de " << path << "no se pudo crear\n";
        }

        SDL_FreeSurface(surface);

        assert(m_texture);
    }

    void SetPosition(int x,int y) {
        m_rect.x = x;
        m_rect.y = y;
    }

    void SetSize(int width, int height) {
        m_rect.w = width;
        m_rect.h = height;
    }

    void RenderTexture() {
        SDL_RenderCopy(m_renderer,m_texture,NULL,&m_rect);
    }

    ~TextureRenderer() {
        UnloadTexture();
    }

    void UnloadTexture() {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }

    SDL_Texture* GetTexture() { return m_texture; }
    SDL_Rect GetRect() { return m_rect; }


private:
    SDL_Rect m_rect;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;
};

class Disk {
public:

    Disk(SDL_Renderer* m_renderer) {
        diskTexture = new TextureRenderer(m_renderer,"../images/ball.png");
        diskTexture->SetPosition(400,400);
        diskTexture->SetSize(BALL_DIAMETER,BALL_DIAMETER);
    }

    void HitDisk(float radians) {
        float speed = sqrt(velX * velX + velY * velY);

        // Calculamos la nueva velocidad en X e Y
        velX = speed * cos(radians);
        velY = speed * sin(radians);
    }
    void UpdateVelocity() {
        velX *= (1 - friction);
        velY *= (1 - friction);
    }

    void UpdatePosition(float deltaTime) {
        x += (velX * deltaTime);
        y += (velY * deltaTime);
        OnDiskEdgeCollission();
        diskTexture->SetPosition(x,y);
    }

    void RenderDisk() {
        diskTexture->RenderTexture();
    }

    void ApplyImpulse(float pusherMass,float pusherVelX,float pusherVelY) {
        velX = ((mass - pusherMass) * velX + 2 * pusherMass * pusherVelX) / (mass + pusherMass);
        velY = ((mass - pusherMass) * velY + 2 * pusherMass * pusherVelY) / (mass + pusherMass);
    }

    void OnDiskEdgeCollission() {
        if (x + BALL_DIAMETER > SCREEN_WIDTH || x < 0) {
            velX = -velX;
        }

         if (y + BALL_DIAMETER > SCREEN_HEIGHT || y  < 0) {
             velY = -velY;
            //y = SCREEN_HEIGHT - (BALL_DIAMETER);
        }

    }

    TextureRenderer* GetTexture() {
        return diskTexture;
    }



private:
    TextureRenderer* diskTexture;

    float friction = 0.003f;
    const int BALL_DIAMETER = 36;
    float x = SCREEN_WIDTH / 2;
    float y = SCREEN_HEIGHT / 2;
    float velX = 0;
    float velY = 0;
    float mass = 0.02;
};

class Pusher {
public:

    Pusher(SDL_Renderer* m_renderer) {
        pusher_texture = new TextureRenderer(m_renderer,"../images/handle.png");
        pusher_texture->SetPosition(400,600);
        pusher_texture->SetSize(PUSHER_DIAMETER,PUSHER_DIAMETER);
    }

    void UpdatePusherPosition(float deltaTime) {
        previusX = x;
        previusY = y;
        SDL_GetMouseState(&x, &y);
        velX = (x - previusX)/deltaTime;
        velY= (y - previusY)/deltaTime;
        if (velX > 0) {
            std::cout << velX << std::endl;

        }

        //y = std::max(SCREEN_HEIGHT / 2, y);
        pusher_texture->SetPosition(x,y);
        RenderPusher();

        // float newX = pusher_texture.set
        // float newY = handleRect.y;
        // LerpVector(newX, newY, static_cast<float>(handlePosX), static_cast<float>(handlePosY), 0.15f, newX, newY);
        // handleRect.x = static_cast<int>(newX);
        // handleRect.y = static_cast<int>(newY);
    }

    void RenderPusher() {
        pusher_texture->RenderTexture();
    }

    TextureRenderer* GetTexture() {
        return pusher_texture;
    }

    float GetMass() {return  mass;}
    float GetVelX() {
        return  velX;
    }
    float GetVelY() {
        return velY;
    }

private:
    TextureRenderer* pusher_texture;
    const int PUSHER_DIAMETER = 56;
    int x;
    int y;
    int previusX = 0;
    int previusY = 0;
    float velX = 0;
    float velY = 0;
    float mass = 0.15;
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

void LerpVector(float x1, float y1, float x2, float y2, float alpha, float &outX, float &outY) {
    outX = (1.0f - alpha) * x1 + alpha * x2;
    outY = (1.0f - alpha) * y1 + alpha * y2;
}

void Lerp(float x, float target, float alpha, float &out) {
    out = (1 - alpha) * x + alpha * target;
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
        return  true;
    }
    return false;
}

float IncidenceAngle(SDL_Rect rect1, SDL_Rect rect2) {
    float rect1CenterX = rect1.x + rect1.w / 2.0f;
    float rect1CenterY = rect1.y + rect1.h / 2.0f;
    float rect2CenterX = rect2.x + rect2.w / 2.0f;
    float rect2CenterY = rect2.y + rect2.h / 2.0f;
    float angle = atan2(rect1CenterY - rect2CenterY,rect1CenterX - rect2CenterX);
    return angle;
}



void CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void GameLoop() {


    Disk *disk = new Disk(renderer);
    Pusher *pusher = new Pusher(renderer);

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
                // if (event.key.keysym.sym == SDLK_a) {
                //     // Si se presiona la tecla "A"
                //     ball->HitBall(); // Llamar a HitBall()
                // }
            }



        }
        pusher->UpdatePusherPosition(deltaTime);
        disk->UpdateVelocity(); // Aplica la fricción a la velocidad
        disk->UpdatePosition(deltaTime); // Actualiza la posición con la velocidad

        SDL_Rect pusherRect = pusher->GetTexture()->GetRect();
        SDL_Rect diskRect = disk->GetTexture()->GetRect();
        bool collision = DetectCollision(pusherRect,diskRect);
        if (collision) {
            disk->HitDisk(IncidenceAngle(diskRect,pusherRect));
            disk->ApplyImpulse(pusher->GetMass(),pusher->GetVelX(),pusher->GetVelY());
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        disk->RenderDisk();
        pusher->RenderPusher();
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - currentTime;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Esperar el tiempo restante
        }
    }
}

int main(int argc, char *argv[]) {
    if (!Initialize()) {
        return 1;
    }

    SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetWindowGrab(window, SDL_TRUE);


    GameLoop();

    CleanUp();

    return 0;
}
