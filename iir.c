#include "iir.h"
#include "define.h"
#include "fichiers.h"
#include <stdlib.h>

/**
 * Effectue un test du filtrage iir sur toutes les valeurs et renvoie la dernière enregistrée.
 *
 * @param filename Path vers le fichier contenant données de sortie du filtre iir.
 * @return Renvoie du dernier résultat obtenu via le filtre.
 */
absorp iirTest(char* filename){
	absorp myAbsorp;

    // Ouverture du fichier.
	FILE *file = fopen(filename, "r");
	if (!file) {
        // En cas d'échec, on renvoie une structure null.
		printf("Erreur ouverture fichier (iirTest)\n");
		return myAbsorp;
	}

    // Attribution de mémoire pour les valeurs nécessaires.
	absorp* currentFir  = malloc(sizeof(absorp));
	absorp* lastFir     = malloc(sizeof(absorp));
    absorp* currentIir  = malloc(sizeof(absorp));
    absorp* lastIir     = malloc(sizeof(absorp));

	char fBuffer[256];

    // Initialisation de la première variable avant la boucle pour éviter valeurs null.
    fgets(fBuffer, sizeof(fBuffer), file);
    sscanf(fBuffer, "%f,%f,%f,%f", &currentFir->acr, &currentFir->dcr, &currentFir->acir, &currentFir->dcir);

    currentIir->acr = currentFir->acr - lastFir->acr;
    currentIir->dcr = currentFir->dcr;
    currentIir->acir = currentFir->acir - lastFir->acir;
    currentIir->dcir = currentFir->dcir;

    // Boucle générale, s'effectuant sur l'ensemble du fichier.
	while (fgets(fBuffer, sizeof(fBuffer), file)) {
        // On copie les attributs (copier directement entraine un copiage d'adresse, donc une erreur)
        lastIir->acr = currentIir->acr;
        lastIir->acir = currentIir->acir;
        lastIir->dcr = currentIir->dcr;
        lastIir->dcir = currentIir->dcir;

        lastFir->acr = currentFir->acr;
        lastFir->acir = currentFir->acir;
        lastFir->dcr = currentFir->dcr;
        lastFir->dcir = currentFir->dcir;

        sscanf(fBuffer, "%f,%f,%f,%f", &currentFir->acr, &currentFir->dcr, &currentFir->acir, &currentFir->dcir);

        free(currentIir);
        currentIir = iir(lastIir, currentFir, lastFir);
	}

    // On copie les attributs un à un pour éviter fuites de mémoire.
    myAbsorp.acir = currentIir->acir;
    myAbsorp.acr = currentIir->acr;
    myAbsorp.dcir = currentIir->dcir;
    myAbsorp.dcr = currentIir->dcr;

    // Fermeture du fichier et free de la mémoire.
    fclose(file);
    free(currentFir);
    free(lastFir);
    free(lastIir);

	return myAbsorp;
}

/**
 * Effectue le filre iir sur des valeurs absorp données en paramètre. Le filtre iir permet de supprimer la composante
 * continue résultante.
 *
 * @param lastIir valeurs du dernier filtrage iir sous forme d'absorp.
 * @param currentFir valeurs de fir actuel sous forme d'absorp.
 * @param lastFir dernier filtrage fir effectué sous forme d'absorp.
 * @return Renvoie le nouvel absorp, avec les valeurs modifiées par le filtrage.
 */
absorp* iir(absorp* lastIir, absorp* currentFir, absorp* lastFir){
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
    else {
        currentIir = currentFir;
    }

    return currentIir;
}

