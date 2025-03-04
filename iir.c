#include "iir.h"
#include "define.h"
#include <stdlib.h>

absorp iirTest(char* filename){
  /*
	Objectif :
		+> faire le iir test pour toutes les valeur et revoyer la dernière enregistrée
	Entrée :
		+> le filename "log1_fir.dat" avec les données de sorties du filtre fir
	SSortie :
		+> on affiche tous les résultats du filtre
		+> on return le dernier résultat obtenu
   */
	absorp	myAbsorp;

	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Erreur ouverture fichier (firTest)\n");
		return myAbsorp;
	}

    printf("============== TEST IIR =============\n");

	absorp* currentFir;
	absorp* lastFir;

    absorp* currentIir;
    absorp* lastIir;

	char fBuffer[256];
	float alpha = 0.992;

    int counter = 0;

	while (fgets(fBuffer, sizeof(fBuffer), file)) {
        absorp* currentIir = malloc(sizeof(absorp));
        absorp* currentFir = malloc(sizeof(absorp));

        sscanf(fBuffer, "%f,%f,%f,%f", &currentFir->acr, &currentFir->dcr, &currentFir->acir, &currentFir->dcir);

        if(lastFir!=NULL){
            if(lastIir!=NULL){
            	currentIir->acr = currentFir->acr - lastFir->acr + alpha * lastIir->acr;
            	currentIir->dcr = currentFir->dcr;
            	currentIir->acir = currentFir->acir - lastFir->acir + alpha * lastIir->acir;
            	currentIir->dcir = currentFir->dcir;
            }
            else{
            	currentIir->acr = currentFir->acr - lastFir->acr;
            	currentIir->dcr = currentFir->dcr;
            	currentIir->acir = currentFir->acir - lastFir->acir;
            	currentIir->dcir = currentFir->dcir;
			}
          	print_absorp(currentIir);
        }

        free(lastIir);
        lastIir = currentIir;
        //TODO: le truc en dessous, faire un freeeeeeee
//        free(lastFir);
        lastFir = currentFir;
	}
	free(lastIir);
    myAbsorp = *currentIir;

    fclose(file);
	return myAbsorp;

}

absorp* iir(absorp* lastIir, absorp* currentFir, absorp* lastFir){
	/*
	Objectif :
		+> filtrer par iir les données de sorties enregistrées dans le cb_fir
	Entrée :
		+> cb_fir 	=> données filtrées par le fir
		+> cb_irr	=> données filtré actuel et précédemeent par le iir
	Sortie :
		+> absorp 	=> dernière valeur filtrée
		+> mise a jour du circular buffer cb_cir avec les valeurs actuels
	 */

    float alpha = 0.992;

    absorp* currentIir = malloc(sizeof(absorp));
	if(lastFir!=NULL){
		if(lastIir!=NULL){
			currentIir->acr = currentFir->acr - lastFir->acr + alpha * lastIir->acr;
			currentIir->dcr = currentFir->dcr;
			currentIir->acir = currentFir->acir - lastFir->acir + alpha * lastIir->acir;
			currentIir->dcir = currentFir->dcir;
		}
		else{
			currentIir->acr = currentFir->acr - lastFir->acr;
			currentIir->dcr = currentFir->dcr;
			currentIir->acir = currentFir->acir - lastFir->acir;
			currentIir->dcir = currentFir->dcir;
		}

	}
    else{
          currentIir = currentFir;
	}
    print_absorp(currentIir);

    return currentIir;
}

