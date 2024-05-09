cmake_minimum_required(VERSION 3.10)
project(EScooked C)

set(CMAKE_C_STANDARD 99)

add_executable(EScooked main.c
        menu.h
        commandes.c
        commandes.h
        menu.c
        varmenu.h
        jeu.c
        jeu.h
        general.h
        sons.c
        sons.h
        sons.c)

IF(WIN32)
    target_link_libraries(EScooked -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.9.1/include)
    LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.9.1/lib)
    file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.9.1/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(EScooked ${LIBRARIES})
ENDIF(WIN32)
