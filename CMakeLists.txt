cmake_minimum_required(VERSION 3.22)
project(cardiofrequencemetre C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories("assets/TestsAutomatiques")

add_executable(cardiofrequencemetre
        "autotests.c"
        "autotests.h"
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
        main_sim.c
        define.h
        autotests.c
        lecture.c
        lecture.h
        main_usb.c
        main_usb.c
        main_sim.c
        main_usb.c
        define.c
)
