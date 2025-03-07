#include "lecture.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
* Objectif :
+> créer un absorp a partir des données de sorties du GPIO
    @param buffer +> Les données qui sortent du GPIO sous forme d'un buffer avec les différentes données dedant
    @return +> un absorp
*/
absorp* create_absorp_from_bits(unsigned char* buffer[]){
    //TODO: faire cette fonction avec les données de sortie du GPIO
    /*
     * buffer[0] = acr-part1
     * buffer[1] = acr-part2
     * buffer[2] = acr-part3
     * buffer[3] = acr-part4
     * buffer[4] = virgule
     * buffer[5] = dcr-part1
     * buffer[6] = dcr-part2
     * buffer[7] = dcr-part3
     * buffer[8] = dcr-part4
     * buffer[9] = virgule
     * buffer[10] = acir-part1
     * buffer[11] = acir-part2
     * buffer[12] = acir-part3
     * buffer[13] = acir-part4
     * buffer[14] = virgule
     * buffer[15] = dcir-part1
     * buffer[16] = dcir-part2
     * buffer[17] = dcir-part3
     * buffer[18] = dcir-part4
     * buffer[19] = virgule
     */

    absorp* absorp = malloc(sizeof(absorp));

    //conversion des données et ajout de celle-ci dans le absorp

    // absorp->acr = (int)strtol(&buffer[0],NULL,0) + buffer[1]%30 + buffer[2]%30 + buffer[3]%30;
    // absorp->dcr = buffer[5]%30 + buffer[6]%30 + buffer[7]%30 + buffer[8]%30;

//    print_absorp(absorp);

    return absorp;
}