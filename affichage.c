#include "affichage.h"
#include "define.h"

/**
 * Permet l'envoi des données de myOxy dans un document situé à la racine.
 * Si le fichier .verrouData existe, alors on ne modifiera pas le fichier pour éviter une écriture lors de la lecture
 * par le programme de front-end. Sinon, on génère un fichier .verrouData pour empêcher la lecture du fichier le temps
 * de l'écriture.
 *
 * @param myOxy Structure oxy contenant les valeurs pouls et SpO2 à écrire dans le fichier.
 */
void affichage(oxy myOxy){
    // Initialisation des paths pour les fichiers.
    char* verrouPath = ".verrouData";
    char* dataPath = "data.txt";

    // On vérifie si .verrouData est présent.
    if (access(verrouPath, F_OK) != -1) {
        // Si oui, on quitte la fonction (on ne peut pas écrire et lire en même temps)
        printf(".verrouData already exists! Not writing in data.txt...\n");
        return;
    }

    // Sinon, on crée le fichier pour éviter la lecture côté front.
    FILE* verrou;
    verrou = fopen(verrouPath, "w");

    // Puis on ouvre le fichier data.txt
    FILE *data;
    data = fopen(dataPath, "w");

    // On écrit dans le fichier (les anciennes données seront supprimées)
    fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls);

    // On supprime le verrou pour autoriser la lecture des données.
    fclose(data);
    remove(verrouPath);
}
