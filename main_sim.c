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
    /*
     //Initialisation fichier source
     char* filename = "assets/FichiersLog/log1/log1.dat";

     //Initialisation Extraction
     char fBuffer[256];
     int ligne = 0;
     circular_buffer* cb_origine = generate_circular_buffer(50);

     // Initialisation Filtrage
     absorp* currentFir;
     absorp* lastFir= malloc(sizeof(absorp));

     absorp* currentIir;
     absorp* lastIir = malloc(sizeof(absorp));

     // Initialisation Calculs
     onde* myOnde = malloc(sizeof(onde));

    // Initialisation Envoi des données
    oxy* myOxy = malloc(sizeof(oxy));

    //Ouverture du fichier
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier (firTest)\n");
        return 0;
    }

    while (fgets(fBuffer, sizeof(fBuffer), file)) {
        // Extraction
        absorp *data = generate_absorp(filename, ligne);
        add_to_circular_buffer(cb_origine, data);

        // Filtrage
        currentFir = fir(cb_origine);
        currentIir = iir(lastIir, currentFir, lastFir);

        // Cas du premier élément
        if(ligne == 0) {
            myOnde->time = 0;
            myOnde->Xmax = currentIir;
            myOnde->Xmin = currentIir;
        }
        else {
            if (maj_onde(myOnde, currentIir, lastIir) == 1) {
               // Calculs
                calculs(myOnde, myOxy);
                affichage(*myOxy);

                // Remise à zéro.
                myOnde->time = 0;
                myOnde->Xmin = currentIir;
                myOnde->Xmax = currentIir;
            }
        }
        ligne++;

        free(lastIir);
        free(lastFir);

        lastIir = currentIir;
        lastFir = currentFir;

        free(data);
    }

    free(cb_origine);

    free(lastIir);
    free(lastFir);
    free(myOnde);
    fclose(file);
    free(myOxy);
*/
    // Zone de tests
    testBlocFIR();
    testBlocIIR();
    testBlocMesure();
    testBlocAffichage();

    return 0;
}