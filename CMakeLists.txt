cmake_minimum_required(VERSION 3.10)
project(Air_Hockey)

set(CMAKE_CXX_STANDARD 20)

# Detección del sistema operativo
if (WIN32)
    message(STATUS "Compilando en Windows")

    set(SDL2_INCLUDE_DIR "C:/SDL2/SDL2-devel-2.30.12-mingw/SDL2-2.30.12/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_LIB_DIR "C:/SDL2/SDL2-devel-2.30.12-mingw/SDL2-2.30.12/x86_64-w64-mingw32/lib")

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")  # Para evitar error de WinMain

    add_executable(Air_Hockey main.cpp)
    target_link_libraries(Air_Hockey mingw32 SDL2main SDL2)

elseif (UNIX)
    message(STATUS "Compilando en Linux")

    find_package(SDL2 REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS})
    add_executable(Air_Hockey main.cpp)
    target_link_libraries(Air_Hockey ${SDL2_LIBRARIES})
endif()
