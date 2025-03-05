//
// Created by OMGiT on 03/03/2025.
//

#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "fichiers.h"
#include "affichage.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"


int main() {
    printf("Conteeeeeent\n");

    char* filename = "assets/FichiersLog/log1/log1.dat";

    // Initialisation Extraction
    circular_buffer* cb_origine = generate_circular_buffer(50);

    // Initialisation Filtrage
    absorp* currentFir = NULL;
    absorp* lastFir= NULL;

    absorp* currentIir = NULL;
    absorp* lastIir = NULL;

    // Initialisation Calculs
    onde* onde = malloc(sizeof(onde));
    // On met la première valeur comme valeur par défaut.
    absorp *data = generate_absorp(filename, 0);
    currentFir = fir(cb_origine);
    currentIir = iir(lastIir, currentFir, lastFir);
    add_to_circular_buffer(cb_origine, data);

    onde->Xmin = currentIir;
    onde->Xmax = currentIir;

    int spo2 = 0;            //Valeur qui seras écrite dans le .data
    int bpm = 0;             //Valeur qui seras écrite dans le .data

    for(int i = 1; i < 5000; i++){
        /* Extraction */
        absorp *data = generate_absorp(filename, i);

        /* On garde en mémoire la dernière valeur */
        lastFir = currentFir;
        lastIir = currentIir;

        /* Filtre */
        add_to_circular_buffer(cb_origine, data);
        currentFir = fir(cb_origine);
        currentIir = iir(lastIir, currentFir, lastFir);

        /* Données retournées] */

        /* Calcuuuuuuuls */
        if (maj_onde(onde, currentIir, lastIir) == 1) {
            calculs(onde, &spo2, &bpm);

            // Remise à zéro.
            onde->time = 0;
            onde->Xmin = currentIir;
            onde->Xmax = currentIir;
        }
//        print_onde(onde);§§ULL){
//            printf("onde OK !\n");
//            print_onde(onde);
//        }
    }

    /* expérimentation des firtest et irrtest */
    /* Log1 */
//    firTest("assets/FichiersLog/log1/log1.dat");
//    iirTest("assets/FichiersLog/log1/log1_fir.dat");
    /*Log2*/
//    firTest("assets/FichiersLog/log2/log2.dat");
//    iirTest("assets/FichiersLog/log2/log2_fir.dat");
    return 0;
}