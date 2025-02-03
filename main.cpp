#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::cout << "SDL2 inicializado correctamente." << std::endl;

    // Limpiar y cerrar SDL antes de salir
    SDL_Quit();

    return 0;
}
