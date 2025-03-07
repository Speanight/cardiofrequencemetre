#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "fichiers.h"
#include "affichage.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "autotests.h"
#include "lecture.h"

int main() {

    //Initialisation fichier source
    char* filename = "assets/FichiersLog/log1/log1.dat";

    //Initialisation Extraction
    char fBuffer[256];
    int ligne = 0;
    circular_buffer* cb_origine = generate_circular_buffer(50);

    // Initialisation Filtrage
    absorp* currentFir = malloc(sizeof(absorp));
    absorp* lastFir= malloc(sizeof(absorp));

    absorp* currentIir = malloc(sizeof(absorp));
    absorp* lastIir = malloc(sizeof(absorp));

    // Initialisation Calculs
    onde* onde = malloc(sizeof(onde));

    // Initialisation Envoi des données
    oxy* myOxy = malloc(sizeof(oxy));

    //Ouverture du fichier
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier (firTest)\n");
        return 0;
    }

    // for(int i=0; i < 500; i++) {
    while (fgets(fBuffer, sizeof(fBuffer), file)) {
        // Extraction
        absorp *data = generate_absorp(filename, ligne);
        add_to_circular_buffer(cb_origine, data);

        // Filtrage
        currentFir = fir(cb_origine);
        currentIir = iir(lastIir, currentFir, lastFir);

        // Cas du premier élément
        if(ligne == 0) {
            onde->time = 0;
            onde->Xmax = currentIir;
            onde->Xmin = currentIir;
        }
        else {
            if (maj_onde(onde, currentIir, lastIir) == 1) {
                // Calculs
                calculs(onde, myOxy);
                affichage(*myOxy);

                // Remise à zéro.
                onde->time = 0;
                onde->Xmin = currentIir;
                onde->Xmax = currentIir;
            }
        }
        ligne++;

        // free(lastIir);
        free(lastFir);

        lastIir = currentIir;
        lastFir = currentFir;

        free(data);
    }

    free(cb_origine);

    free(lastIir);
    free(lastFir);

    fclose(file);
     free(onde);
     free(myOxy);

    return 0;
}