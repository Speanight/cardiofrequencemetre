//
// Created by OMGiT on 03/03/2025.
//

#include "define.h"
#include "affichage.h"

absorp* generate_absorp(const char *filename, int n) {
  /*
    Objectif     +> générer la structure absorp a partir du numéro de la ligne d'un fichier source
    *filename    +> nom du fichier contenant les données
    n            +> numéro de ligne
   */
  /* Ouverture du fichier et gestion erreur s'il n'apparait pas*/
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier");
        return NULL;
    }

    /* Allocation de la mémoire pour la structure */
    absorp *data = (absorp*)malloc(sizeof(absorp));
    if (!data) {
        printf("Erreur allocation mémoire");
        fclose(file);
        return NULL;
    }


    char buffer[256];
    int current_line = 0;

    /* Récupération des infos contenues dans la fichier a la bonne ligne*/
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line == n) {
            sscanf(buffer, "%f,%f,%f,%f", &data->acr, &data->dcr, &data->acir, &data->dcir);
            fclose(file);
            return data;
        }
        current_line++;
    }

    fclose(file);
    free(data);
    return NULL; // Ligne non trouvée
}

int main() {
    printf("Conteeeeeent\n");
    int ligne = 2; // Exemple : lire la ligne 2
    absorp *data = generate_absorp("assets/Fichiers log/log1/log1.dat", ligne);

    if (data) {
        printf("Ligne %d : acr = %.2f, dcr = %.2f, acir = %.2f, dcir = %.2f\n",
               ligne, data->acr, data->dcr, data->acir, data->dcir);
        free(data);
    } else {
        printf("Erreur : impossible de générer la structure absorp\n");
    }

    printf("Test de l'affichage :\n");
    oxy myOxy = {97, 104};
    affichage(myOxy);

    return 0;
}