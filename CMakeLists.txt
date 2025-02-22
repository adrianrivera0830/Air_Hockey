cmake_minimum_required(VERSION 3.10)
project(Air_Hockey)

# Configurar estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detección del sistema operativo
if (WIN32)
    message(STATUS "Compilando en Windows")

    # Definir _WIN32_WINNT para compatibilidad con inet_pton
    add_definitions(-D_WIN32_WINNT=0x0601)

    # Incluir Winsock en el linker para evitar errores de funciones de red
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole -lws2_32")

    # Rutas de SDL2
    set(SDL2_INCLUDE_DIR "C:/SDL2/SDL2-devel-2.30.12-mingw/SDL2-2.30.12/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_LIB_DIR "C:/SDL2/SDL2-devel-2.30.12-mingw/SDL2-2.30.12/x86_64-w64-mingw32/lib")

    # Rutas de SDL2_image
    set(SDL2_IMAGE_INCLUDE_DIR "C:/SDL2/SDL2_image-devel-2.8.4-mingw/SDL2_image-2.8.4/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_IMAGE_LIB_DIR "C:/SDL2/SDL2_image-devel-2.8.4-mingw/SDL2_image-2.8.4/x86_64-w64-mingw32/lib")

    # Rutas de SDL2_ttf
    set(SDL2_TTF_INCLUDE_DIR "C:/SDL2/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_TTF_LIB_DIR "C:/SDL2/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib")

    # Incluir directorios
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

    # Incluir librerías
    link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB_DIR} ${SDL2_TTF_LIB_DIR})

    # Definir el ejecutable
    add_executable(Air_Hockey
            Source/main.cpp
            Source/Peer.cpp
            Headers/Peer.h
            Headers/NetworkHeaders.h
            Source/PacketManager.cpp
            Headers/PacketManager.h
            Source/TextureRenderer.cpp
            Headers/TextureRenderer.h
            Source/Disk.cpp
            Headers/Disk.h
            Source/Pusher.cpp
            Headers/Pusher.h
            Source/NetworkManager.cpp
            Headers/NetworkManager.h
            Source/Game.cpp
            Headers/Game.h
            Headers/Structs.h
    )

    # Vincular bibliotecas necesarias
    target_link_libraries(Air_Hockey mingw32 SDL2main SDL2 SDL2_image SDL2_ttf ws2_32)

elseif (UNIX)
    message(STATUS "Compilando en Linux")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

    add_executable(Air_Hockey
            Source/main.cpp
            Source/Peer.cpp
            Headers/Peer.h
            Headers/NetworkHeaders.h
            Source/PacketManager.cpp
            Headers/PacketManager.h
            Source/TextureRenderer.cpp
            Headers/TextureRenderer.h
            Source/Disk.cpp
            Headers/Disk.h
            Source/Pusher.cpp
            Headers/Pusher.h
            Source/NetworkManager.cpp
            Headers/NetworkManager.h
            Source/Game.cpp
            Headers/Game.h
            Headers/Structs.h
    )

    target_link_libraries(Air_Hockey ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()
