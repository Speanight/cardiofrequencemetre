cmake_minimum_required(VERSION 3.22)
project(cardiofrequencemetre C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories("assets/Tests automatiques")

add_executable(cardiofrequencemetre
        "assets/Tests automatiques/autotests.c"
        "assets/Tests automatiques/autotests.h"
        affichage.c
        affichage.h
        define.h
        fichiers.c
        fichiers.h
        fir.c
        fir.h
        iir.c
        iir.h
        main_sim.c
        mesure.c
        mesure.h
        test.c
        main_sim.c
        define.h
)
