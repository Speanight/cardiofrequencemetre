#include "affichage.h"

void affichage(oxy myOxy){
    // On vérifie si .verrouData est présent.
    if (access(".verrouData", F_OK) != -1) {
        // Si oui, on quitte la fonction (on ne peut pas écrire et lire en même temps)
        printf(".verrouData already exists! Not writing in data.txt...\n");
        return;
    }
    FILE* verrou;
    // Sinon, on crée le fichier pour éviter la lecture côté front.
    verrou = fopen(".verrouData", "w");

    // Puis on ouvre le fichier data.txt
    FILE *data;
    data = fopen("data.txt", "w");

    // On écrit dans le fichier (les anciennes données seront supprimées si besoin)
    fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls);

    // On supprime le verrou pour autoriser la lecture des données.
    remove(".verrouData");
}

