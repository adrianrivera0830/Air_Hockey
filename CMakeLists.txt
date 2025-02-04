cmake_minimum_required(VERSION 3.10)
project(Air_Hockey)

set(CMAKE_CXX_STANDARD 20)

# Detección del sistema operativo
if (WIN32)
    message(STATUS "Compilando en Windows")

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

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")  # Para evitar error de WinMain

    add_executable(Air_Hockey main.cpp)

    # Vincular bibliotecas necesarias
    target_link_libraries(Air_Hockey mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)

elseif (UNIX)
    message(STATUS "Compilando en Linux")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

    add_executable(Air_Hockey main.cpp)

    target_link_libraries(Air_Hockey ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()
